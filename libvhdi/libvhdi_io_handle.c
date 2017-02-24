/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2012-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvhdi_data_block.h"
#include "libvhdi_debug.h"
#include "libvhdi_definitions.h"
#include "libvhdi_io_handle.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfcache.h"
#include "libvhdi_libfdata.h"
#include "libvhdi_libfguid.h"
#include "libvhdi_libuna.h"
#include "libvhdi_unused.h"

#include "vhdi_dynamic_disk_header.h"
#include "vhdi_file_footer.h"

const uint8_t *vhdi_file_signature         = (uint8_t *) "conectix";
const uint8_t *vhdi_dynamic_disk_signature = (uint8_t *) "cxsparse";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_initialize(
     libvhdi_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libvhdi_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libvhdi_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_free(
     libvhdi_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		if( ( *io_handle )->parent_filename != NULL )
		{
			memory_free(
			 ( *io_handle )->parent_filename );
		}
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_clear(
     libvhdi_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->parent_filename != NULL )
	{
		memory_free(
		 io_handle->parent_filename );

		io_handle->parent_filename      = NULL;
		io_handle->parent_filename_size = 0;
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libvhdi_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the file footer
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_read_file_footer(
     libvhdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t *next_offset,
     libcerror_error_t **error )
{
	uint8_t *file_footer_data = NULL;
	static char *function     = "libvhdi_io_handle_read_file_footer";
	ssize_t read_count        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit      = 0;
	uint32_t value_32bit      = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( next_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid next offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file footer at offset: -512 from the end.\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     -512,
	     SEEK_END,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file footer offset: -512 from the end.",
		 function );

		goto on_error;
	}
	file_footer_data = (uint8_t *) memory_allocate(
	                                sizeof( vhdi_file_footer_t ) );

	if( file_footer_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file footer data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_footer_data,
	              sizeof( vhdi_file_footer_t ),
	              error );

	if( read_count != (ssize_t) sizeof( vhdi_file_footer_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file footer data:\n",
		 function );
		libcnotify_print_data(
		 file_footer_data,
		 sizeof( vhdi_file_footer_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_file_footer_t *) file_footer_data )->signature,
	     vhdi_file_signature,
	     8 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_file_footer_t *) file_footer_data )->format_version,
	 io_handle->format_version );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_file_footer_t *) file_footer_data )->next_offset,
	 *next_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_file_footer_t *) file_footer_data )->disk_size,
	 io_handle->media_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_file_footer_t *) file_footer_data )->disk_type,
	 io_handle->disk_type );

	if( memory_copy(
	     io_handle->identifier,
	     ( (vhdi_file_footer_t *) file_footer_data )->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 0 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 1 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 2 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 3 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 4 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 5 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 6 ],
		 ( (vhdi_file_footer_t *) file_footer_data )->signature[ 7 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->features,
		 value_32bit );
		libcnotify_printf(
		 "%s: features\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 io_handle->format_version >> 16,
		 io_handle->format_version & 0x0000ffffUL );

		libcnotify_printf(
		 "%s: next offset\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 *next_offset );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->modification_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: modification time\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->creator_application,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators application\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->creator_version,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators version\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 value_32bit >> 16,
		 value_32bit & 0x0000ffffUL );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->creator_operating_system,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators operating system\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: disk size\t\t\t\t: %" PRIu64 "\n",
		 function,
		 io_handle->media_size );

		byte_stream_copy_to_uint64_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->data_size,
		 value_64bit );
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->disk_geometry,
		 value_32bit );
		libcnotify_printf(
		 "%s: disk geometry\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: disk type\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 io_handle->disk_type );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) file_footer_data )->checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libvhdi_debug_print_guid_value(
		     function,
		     "identifier\t\t\t\t",
		     ( (vhdi_file_footer_t *) file_footer_data )->identifier,
		     16,
		     LIBFGUID_ENDIAN_BIG,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: saved state\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 ( (vhdi_file_footer_t *) file_footer_data )->saved_state );

		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_file_footer_t *) file_footer_data )->unknown1,
		 427,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( io_handle->format_version != 0x00010000UL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: 0x%08" PRIx32 ".",
		 function,
		 io_handle->format_version );

		goto on_error;
	}
	if( ( io_handle->disk_type != LIBVHDI_DISK_TYPE_FIXED )
	 && ( io_handle->disk_type != LIBVHDI_DISK_TYPE_DYNAMIC )
	 && ( io_handle->disk_type != LIBVHDI_DISK_TYPE_DIFFERENTIAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported disk type: 0x%08" PRIx32 ".",
		 function,
		 io_handle->disk_type );

		goto on_error;
	}
	memory_free(
	 file_footer_data );

	file_footer_data = NULL;

	return( 1 );

on_error:
	if( file_footer_data != NULL )
	{
		memory_free(
		 file_footer_data );
	}
	return( -1 );
}

/* Reads the file dynamic disk header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_read_dynamic_disk_header(
     libvhdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     off64_t *next_offset,
     libcerror_error_t **error )
{
	uint8_t *dynamic_disk_header_data = NULL;
	static char *function             = "libvhdi_io_handle_read_dynamic_disk_header";
	size_t parent_filename_size       = 0;
	ssize_t read_count                = 0;
	uint32_t format_version           = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit              = 0;
	uint32_t value_32bit              = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->parent_filename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle - parent filename value already set.",
		 function );

		return( -1 );
	}
	if( next_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid next offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading dynamic disk header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek dynamic disk header offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	dynamic_disk_header_data = (uint8_t *) memory_allocate(
	                                        sizeof( vhdi_dynamic_disk_header_t ) );

	if( dynamic_disk_header_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create dynamic disk header data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              dynamic_disk_header_data,
	              sizeof( vhdi_dynamic_disk_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( vhdi_dynamic_disk_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read dynamic disk header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: dynamic disk header data:\n",
		 function );
		libcnotify_print_data(
		 dynamic_disk_header_data,
		 sizeof( vhdi_dynamic_disk_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature,
	     vhdi_dynamic_disk_signature,
	     8 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->format_version,
	 format_version );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->block_table_offset,
	 io_handle->block_table_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->next_offset,
	 *next_offset );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->block_size,
	 io_handle->block_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->number_of_blocks,
	 io_handle->number_of_blocks );

	if( memory_copy(
	     io_handle->parent_identifier,
	     ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy parent identifier.",
		 function );

		goto on_error;
	}
	parent_filename_size = 0;

	while( parent_filename_size < ( 512 - 1 ) )
	{
		if( ( ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_filename[ parent_filename_size ] == 0 )
		 && ( ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_filename[ parent_filename_size + 1 ] == 0 ) )
		{
			break;
		}
		parent_filename_size += 2;
	}
	if( parent_filename_size > 0 )
	{
		parent_filename_size += 2;

		io_handle->parent_filename = (uint8_t *) memory_allocate(
		                                          sizeof( uint8_t ) * parent_filename_size );

		if( io_handle->parent_filename == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create parent filename.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     io_handle->parent_filename,
		     ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_filename,
		     parent_filename_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy parent filename.",
			 function );

			goto on_error;
		}
	}
	io_handle->parent_filename_size = parent_filename_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 0 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 1 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 2 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 3 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 4 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 5 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 6 ],
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->signature[ 7 ] );

		libcnotify_printf(
		 "%s: format version\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 io_handle->format_version >> 16,
		 io_handle->format_version & 0x0000ffffUL );

		libcnotify_printf(
		 "%s: block table offset\t\t: 0x%08" PRIx64 "\n",
		 function,
		 io_handle->block_table_offset );

		libcnotify_printf(
		 "%s: next offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 *next_offset );

		libcnotify_printf(
		 "%s: block size\t\t\t: %" PRIu64 "\n",
		 function,
		 io_handle->block_size );

		libcnotify_printf(
		 "%s: number of blocks\t\t: %" PRIu64 "\n",
		 function,
		 io_handle->number_of_blocks );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libvhdi_debug_print_guid_value(
		     function,
		     "parent identifier\t\t",
		     ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_identifier,
		     16,
		     LIBFGUID_ENDIAN_BIG,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_modification_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: parent modification time\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: parent filename data:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_filename,
		 512,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( io_handle->parent_filename_size > 0 )
		{
			if( libvhdi_debug_print_utf16_string_value(
			     function,
			     "parent filename\t\t",
			     io_handle->parent_filename,
			     io_handle->parent_filename_size,
			     LIBUNA_ENDIAN_BIG,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print UTF-16 string value.",
				 function );

				goto on_error;
			}
		}
		libcnotify_printf(
		 "%s: parent locator entries data:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->parent_locator_entries,
		 192,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "%s: unknown2:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_dynamic_disk_header_t *) dynamic_disk_header_data )->unknown2,
		 256,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	memory_free(
	 dynamic_disk_header_data );

	dynamic_disk_header_data = NULL;

	if( format_version != 0x00010000UL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: 0x%08" PRIx32 ".",
		 function,
		 format_version );

		goto on_error;
	}
	if( ( io_handle->block_size % 512 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported block size: %" PRIu32 ".",
		 function,
		 io_handle->block_size );

		goto on_error;
	}
	io_handle->block_bitmap_size = io_handle->block_size / ( 512 * 8 );

	if( ( io_handle->block_bitmap_size % 512 ) != 0 )
	{
		io_handle->block_bitmap_size /= 512;
		io_handle->block_bitmap_size += 1;
		io_handle->block_bitmap_size *= 512;
	}
	return( 1 );

on_error:
	if( io_handle->parent_filename != NULL )
	{
		memory_free(
		 io_handle->parent_filename );

		io_handle->parent_filename      = NULL;
		io_handle->parent_filename_size = 0;
	}
	if( dynamic_disk_header_data != NULL )
	{
		memory_free(
		 dynamic_disk_header_data );
	}
	return( -1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_get_identifier(
     libvhdi_io_handle_t *io_handle,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_get_identifier";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     io_handle->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the parent identifier
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_get_parent_identifier(
     libvhdi_io_handle_t *io_handle,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_get_parent_identifier";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     io_handle->parent_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy parent identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_io_handle_get_utf8_parent_filename_size(
     libvhdi_io_handle_t *io_handle,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_get_utf8_parent_filename_size";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->parent_filename == NULL )
	 || ( io_handle->parent_filename_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     io_handle->parent_filename,
	     io_handle->parent_filename_size,
	     LIBUNA_ENDIAN_BIG,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_io_handle_get_utf8_parent_filename(
     libvhdi_io_handle_t *io_handle,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_get_utf8_parent_filename";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->parent_filename == NULL )
	 || ( io_handle->parent_filename_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     io_handle->parent_filename,
	     io_handle->parent_filename_size,
	     LIBUNA_ENDIAN_BIG,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy parent filename to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_io_handle_get_utf16_parent_filename_size(
     libvhdi_io_handle_t *io_handle,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_get_utf16_parent_filename_size";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->parent_filename == NULL )
	 || ( io_handle->parent_filename_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     io_handle->parent_filename,
	     io_handle->parent_filename_size,
	     LIBUNA_ENDIAN_BIG,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_io_handle_get_utf16_parent_filename(
     libvhdi_io_handle_t *io_handle,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_io_handle_get_utf16_parent_filename";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->parent_filename == NULL )
	 || ( io_handle->parent_filename_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     io_handle->parent_filename,
	     io_handle->parent_filename_size,
	     LIBUNA_ENDIAN_BIG,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy parent filename to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads a data block
 * Callback function for the data block vector
 * Returns 1 if successful or -1 on error
 */
int libvhdi_io_handle_read_data_block(
     libvhdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBVHDI_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBVHDI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvhdi_data_block_t *data_block = NULL;
	static char *function            = "libvhdi_io_handle_read_data_block";

	LIBVHDI_UNREFERENCED_PARAMETER( element_data_flags );
	LIBVHDI_UNREFERENCED_PARAMETER( read_flags );

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( element_data_file_index != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data file index value out of bounds.",
		 function );

		return( -1 );
	}
	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libvhdi_data_block_initialize(
	     &data_block,
	     (size_t) element_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data block.",
		 function );

		goto on_error;
	}
	if( libvhdi_data_block_read(
	     data_block,
	     file_io_handle,
             element_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data block.",
		 function );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) data_block,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_data_block_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data block as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_block != NULL )
	{
		libvhdi_data_block_free(
		 &data_block,
		 NULL );
	}
	return( -1 );
}

