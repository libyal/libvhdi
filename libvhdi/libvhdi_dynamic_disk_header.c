/*
 * Dynamic disk header functions
 *
 * Copyright (C) 2012-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvhdi_debug.h"
#include "libvhdi_definitions.h"
#include "libvhdi_dynamic_disk_header.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfguid.h"
#include "libvhdi_libuna.h"

#include "vhdi_dynamic_disk_header.h"

/* Creates dynamic disk header
 * Make sure the value dynamic_disk_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_dynamic_disk_header_initialize(
     libvhdi_dynamic_disk_header_t **dynamic_disk_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_initialize";

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( *dynamic_disk_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid dynamic disk header value already set.",
		 function );

		return( -1 );
	}
	*dynamic_disk_header = memory_allocate_structure(
	                        libvhdi_dynamic_disk_header_t );

	if( *dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create dynamic disk header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *dynamic_disk_header,
	     0,
	     sizeof( libvhdi_dynamic_disk_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear dynamic disk header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *dynamic_disk_header != NULL )
	{
		memory_free(
		 *dynamic_disk_header );

		*dynamic_disk_header = NULL;
	}
	return( -1 );
}

/* Frees dynamic disk header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_dynamic_disk_header_free(
     libvhdi_dynamic_disk_header_t **dynamic_disk_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_free";

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( *dynamic_disk_header != NULL )
	{
		if( ( *dynamic_disk_header )->parent_filename != NULL )
		{
			memory_free(
			 ( *dynamic_disk_header )->parent_filename );
		}
		memory_free(
		 *dynamic_disk_header );

		*dynamic_disk_header = NULL;
	}
	return( 1 );
}

/* Reads the dynamic disk header data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_dynamic_disk_header_read_data(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function            = "libvhdi_dynamic_disk_header_read_data";
	size_t parent_filename_size      = 0;
	uint64_t safe_block_table_offset = 0;
	uint64_t safe_next_offset        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit             = 0;
#endif

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( dynamic_disk_header->parent_filename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid dynamic disk header - parent filename already set.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( vhdi_dynamic_disk_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: dynamic disk header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_dynamic_disk_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_dynamic_disk_header_t *) data )->signature,
	     "cxsparse",
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
	 ( (vhdi_dynamic_disk_header_t *) data )->format_version,
	 dynamic_disk_header->format_version );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) data )->block_table_offset,
	 safe_block_table_offset );

	dynamic_disk_header->block_table_offset = (off64_t) safe_block_table_offset;

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) data )->next_offset,
	 safe_next_offset );

	dynamic_disk_header->next_offset = (off64_t) safe_next_offset;

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) data )->block_size,
	 dynamic_disk_header->block_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_dynamic_disk_header_t *) data )->number_of_blocks,
	 dynamic_disk_header->number_of_blocks );

	if( memory_copy(
	     dynamic_disk_header->parent_identifier,
	     ( (vhdi_dynamic_disk_header_t *) data )->parent_identifier,
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
		if( ( ( (vhdi_dynamic_disk_header_t *) data )->parent_filename[ parent_filename_size ] == 0 )
		 && ( ( (vhdi_dynamic_disk_header_t *) data )->parent_filename[ parent_filename_size + 1 ] == 0 ) )
		{
			break;
		}
		parent_filename_size += 2;
	}
	if( parent_filename_size > 0 )
	{
		if( parent_filename_size > (size_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 2 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent filename size value exceeds maximum allocation size.",
			 function );

			goto on_error;
		}
		parent_filename_size += 2;

		dynamic_disk_header->parent_filename = (uint8_t *) memory_allocate(
		                                                    sizeof( uint8_t ) * parent_filename_size );

		if( dynamic_disk_header->parent_filename == NULL )
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
		     dynamic_disk_header->parent_filename,
		     ( (vhdi_dynamic_disk_header_t *) data )->parent_filename,
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
	dynamic_disk_header->parent_filename_size = parent_filename_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 0 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 1 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 2 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 3 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 4 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 5 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 6 ],
		 ( (vhdi_dynamic_disk_header_t *) data )->signature[ 7 ] );

		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 dynamic_disk_header->format_version >> 16,
		 dynamic_disk_header->format_version & 0x0000ffffUL );

		libcnotify_printf(
		 "%s: block table offset\t\t: 0x%08" PRIx64 "\n",
		 function,
		 safe_block_table_offset );

		libcnotify_printf(
		 "%s: next offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 safe_next_offset );

		libcnotify_printf(
		 "%s: block size\t\t\t: %" PRIu64 "\n",
		 function,
		 dynamic_disk_header->block_size );

		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu64 "\n",
		 function,
		 dynamic_disk_header->number_of_blocks );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_dynamic_disk_header_t *) data )->checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libvhdi_debug_print_guid_value(
		     function,
		     "parent identifier\t\t",
		     ( (vhdi_dynamic_disk_header_t *) data )->parent_identifier,
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
		 ( (vhdi_dynamic_disk_header_t *) data )->parent_modification_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: parent modification time\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: parent filename data:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_dynamic_disk_header_t *) data )->parent_filename,
		 512,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( dynamic_disk_header->parent_filename_size > 0 )
		{
			if( libvhdi_debug_print_utf16_string_value(
			     function,
			     "parent filename\t\t\t",
			     dynamic_disk_header->parent_filename,
			     dynamic_disk_header->parent_filename_size,
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
		 ( (vhdi_dynamic_disk_header_t *) data )->parent_locator_entries,
		 192,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "%s: unknown2:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_dynamic_disk_header_t *) data )->unknown2,
		 256,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( dynamic_disk_header->format_version != 0x00010000UL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: 0x%08" PRIx32 ".",
		 function,
		 dynamic_disk_header->format_version );

		goto on_error;
	}
	if( dynamic_disk_header->block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block size value out of bounds.",
		 function );

		goto on_error;
	}
/* TODO check if block size is power of 2 */
	if( ( dynamic_disk_header->block_size % 512 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported block size: %" PRIu32 ".",
		 function,
		 dynamic_disk_header->block_size );

		goto on_error;
	}
	return( 1 );

on_error:
	if( dynamic_disk_header->parent_filename != NULL )
	{
		memory_free(
		 dynamic_disk_header->parent_filename );

		dynamic_disk_header->parent_filename = NULL;
	}
	dynamic_disk_header->parent_filename_size = 0;

	return( -1 );
}

/* Reads the dynamic disk header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_dynamic_disk_header_read_file_io_handle(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t dynamic_disk_header_data[ sizeof( vhdi_dynamic_disk_header_t ) ];

	static char *function = "libvhdi_dynamic_disk_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
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
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              dynamic_disk_header_data,
	              sizeof( vhdi_dynamic_disk_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( vhdi_dynamic_disk_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read dynamic disk header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libvhdi_dynamic_disk_header_read_data(
	     dynamic_disk_header,
	     dynamic_disk_header_data,
	     sizeof( vhdi_dynamic_disk_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read dynamic disk header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the parent identifier
 * Returns 1 if successful or -1 on error
 */
int libvhdi_dynamic_disk_header_get_parent_identifier(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_get_parent_identifier";

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
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
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     dynamic_disk_header->parent_identifier,
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
int libvhdi_dynamic_disk_header_get_utf8_parent_filename_size(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_get_utf8_parent_filename_size";
	int result            = 0;

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( dynamic_disk_header->parent_filename != NULL )
	 && ( dynamic_disk_header->parent_filename_size > 0 ) )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
		          dynamic_disk_header->parent_filename,
		          dynamic_disk_header->parent_filename_size,
		          LIBUNA_ENDIAN_BIG,
		          utf8_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-8 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_dynamic_disk_header_get_utf8_parent_filename(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_get_utf8_parent_filename";
	int result            = 0;

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( dynamic_disk_header->parent_filename != NULL )
	 && ( dynamic_disk_header->parent_filename_size > 0 ) )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
		          utf8_string,
		          utf8_string_size,
		          dynamic_disk_header->parent_filename,
		          dynamic_disk_header->parent_filename_size,
		          LIBUNA_ENDIAN_BIG,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy parent filename to UTF-8 string.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the size of the UTF-16 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_dynamic_disk_header_get_utf16_parent_filename_size(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_get_utf16_parent_filename_size";
	int result            = 0;

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( dynamic_disk_header->parent_filename != NULL )
	 && ( dynamic_disk_header->parent_filename_size > 0 ) )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
		          dynamic_disk_header->parent_filename,
		          dynamic_disk_header->parent_filename_size,
		          LIBUNA_ENDIAN_BIG,
		          utf16_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-16 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_dynamic_disk_header_get_utf16_parent_filename(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_dynamic_disk_header_get_utf16_parent_filename";
	int result            = 0;

	if( dynamic_disk_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( dynamic_disk_header->parent_filename != NULL )
	 && ( dynamic_disk_header->parent_filename_size > 0 ) )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
		          utf16_string,
		          utf16_string_size,
		          dynamic_disk_header->parent_filename,
		          dynamic_disk_header->parent_filename_size,
		          LIBUNA_ENDIAN_BIG,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy parent filename to UTF-16 string.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

