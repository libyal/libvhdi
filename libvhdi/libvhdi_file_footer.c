/*
 * File footer functions
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
#include "libvhdi_file_footer.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfguid.h"

#include "vhdi_file_footer.h"

/* Creates file footer
 * Make sure the value file_footer is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_file_footer_initialize(
     libvhdi_file_footer_t **file_footer,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_file_footer_initialize";

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
	if( *file_footer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file footer value already set.",
		 function );

		return( -1 );
	}
	*file_footer = memory_allocate_structure(
	                libvhdi_file_footer_t );

	if( *file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file footer.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_footer,
	     0,
	     sizeof( libvhdi_file_footer_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file footer.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_footer != NULL )
	{
		memory_free(
		 *file_footer );

		*file_footer = NULL;
	}
	return( -1 );
}

/* Frees file footer
 * Returns 1 if successful or -1 on error
 */
int libvhdi_file_footer_free(
     libvhdi_file_footer_t **file_footer,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_file_footer_free";

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
	if( *file_footer != NULL )
	{
		memory_free(
		 *file_footer );

		*file_footer = NULL;
	}
	return( 1 );
}

/* Reads the file footer data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_file_footer_read_data(
     libvhdi_file_footer_t *file_footer,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function     = "libvhdi_file_footer_read_data";
	uint64_t safe_next_offset = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit      = 0;
	uint32_t value_32bit      = 0;
#endif

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
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
	if( ( data_size < sizeof( vhdi_file_footer_t ) )
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
		 "%s: file footer data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_file_footer_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_file_footer_t *) data )->signature,
	     "conectix",
	     8 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_file_footer_t *) data )->format_version,
	 file_footer->format_version );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_file_footer_t *) data )->next_offset,
	 safe_next_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (vhdi_file_footer_t *) data )->disk_size,
	 file_footer->media_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_file_footer_t *) data )->disk_type,
	 file_footer->disk_type );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vhdi_file_footer_t *) data )->checksum,
	 file_footer->checksum );

	if( memory_copy(
	     file_footer->identifier,
	     ( (vhdi_file_footer_t *) data )->identifier,
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 ( (vhdi_file_footer_t *) data )->signature[ 0 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 1 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 2 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 3 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 4 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 5 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 6 ],
		 ( (vhdi_file_footer_t *) data )->signature[ 7 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) data )->features,
		 value_32bit );
		libcnotify_printf(
		 "%s: features\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
		libvhdi_debug_print_feature_flags(
		 value_32bit );
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 file_footer->format_version >> 16,
		 file_footer->format_version & 0x0000ffffUL );

		libcnotify_printf(
		 "%s: next offset\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 safe_next_offset );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) data )->modification_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: modification time\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) data )->creator_application,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators application\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) data )->creator_version,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators version\t\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 value_32bit >> 16,
		 value_32bit & 0x0000ffffUL );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) data )->creator_operating_system,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators operating system\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: disk size\t\t\t\t: %" PRIu64 "\n",
		 function,
		 file_footer->media_size );

		byte_stream_copy_to_uint64_big_endian(
		 ( (vhdi_file_footer_t *) data )->data_size,
		 value_64bit );
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vhdi_file_footer_t *) data )->disk_geometry,
		 value_32bit );
		libcnotify_printf(
		 "%s: disk geometry\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: disk type\t\t\t\t: 0x%08" PRIx32 " (%s)\n",
		 function,
		 file_footer->disk_type,
		 libvhdi_debug_print_disk_type(
		  file_footer->disk_type ) );

		libcnotify_printf(
		 "%s: checksum\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_footer->checksum );

		if( libvhdi_debug_print_guid_value(
		     function,
		     "identifier\t\t\t\t",
		     ( (vhdi_file_footer_t *) data )->identifier,
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

			return( -1 );
		}
		libcnotify_printf(
		 "%s: saved state\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 ( (vhdi_file_footer_t *) data )->saved_state );

		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_file_footer_t *) data )->unknown1,
		 427,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( file_footer->format_version != 0x00010000UL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: 0x%08" PRIx32 ".",
		 function,
		 file_footer->format_version );

		return( -1 );
	}
	if( ( file_footer->disk_type != LIBVHDI_DISK_TYPE_FIXED )
	 && ( file_footer->disk_type != LIBVHDI_DISK_TYPE_DYNAMIC )
	 && ( file_footer->disk_type != LIBVHDI_DISK_TYPE_DIFFERENTIAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported disk type: 0x%08" PRIx32 ".",
		 function,
		 file_footer->disk_type );

		return( -1 );
	}
	if( file_footer->disk_type == LIBVHDI_DISK_TYPE_FIXED )
	{
		if( (off64_t) safe_next_offset != -1LL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported next offset.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( (off64_t) safe_next_offset < 512 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported next offset.",
			 function );

			return( -1 );
		}
	}
	file_footer->next_offset = (off64_t) safe_next_offset;

	return( 1 );
}

/* Reads the file footer
 * Returns 1 if successful or -1 on error
 */
int libvhdi_file_footer_read_file_io_handle(
     libvhdi_file_footer_t *file_footer,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t file_footer_data[ sizeof( vhdi_file_footer_t ) ];

	static char *function = "libvhdi_file_footer_read_file_io_handle";
	ssize_t read_count    = 0;

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file footer at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              file_footer_data,
	              sizeof( vhdi_file_footer_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( vhdi_file_footer_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libvhdi_file_footer_read_data(
	     file_footer,
	     file_footer_data,
	     sizeof( vhdi_file_footer_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
int libvhdi_file_footer_get_format_version(
     libvhdi_file_footer_t *file_footer,
     uint16_t *major_version,
     uint16_t *minor_version,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_file_footer_get_format_version";

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
	if( major_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid major version.",
		 function );

		return( -1 );
	}
	if( minor_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid minor version.",
		 function );

		return( -1 );
	}
	*major_version = ( file_footer->format_version >> 16 ) & 0x0000ffffUL;
	*minor_version = file_footer->format_version & 0x0000ffffUL;

	return( 1 );
}

/* Retrieves the identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvhdi_file_footer_get_identifier(
     libvhdi_file_footer_t *file_footer,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_file_footer_get_identifier";

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
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
	 || ( guid_data_size > SSIZE_MAX ) )
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
	     file_footer->identifier,
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

