/*
 * Image header functions
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
#include "libvhdi_image_header.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfguid.h"

#include "vhdi_image_header.h"

/* Creates image header
 * Make sure the value image_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_image_header_initialize(
     libvhdi_image_header_t **image_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_image_header_initialize";

	if( image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image header.",
		 function );

		return( -1 );
	}
	if( *image_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid image header value already set.",
		 function );

		return( -1 );
	}
	*image_header = memory_allocate_structure(
	                 libvhdi_image_header_t );

	if( *image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create image header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *image_header,
	     0,
	     sizeof( libvhdi_image_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear image header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *image_header != NULL )
	{
		memory_free(
		 *image_header );

		*image_header = NULL;
	}
	return( -1 );
}

/* Frees image header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_image_header_free(
     libvhdi_image_header_t **image_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_image_header_free";

	if( image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image header.",
		 function );

		return( -1 );
	}
	if( *image_header != NULL )
	{
		memory_free(
		 *image_header );

		*image_header = NULL;
	}
	return( 1 );
}

/* Reads the image header data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_image_header_read_data(
     libvhdi_image_header_t *image_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_image_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit  = 0;
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image header.",
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
	if( ( data_size < sizeof( vhdi_image_header_t ) )
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
		 "%s: image header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_image_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_image_header_t *) data )->signature,
	     "head",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_image_header_t *) data )->checksum,
	 image_header->checksum );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vhdi_image_header_t *) data )->sequence_number,
	 image_header->sequence_number );

	byte_stream_copy_to_uint16_little_endian(
	 ( (vhdi_image_header_t *) data )->format_version,
	 image_header->format_version );

	if( memory_copy(
	     image_header->data_write_identifier,
	     ( (vhdi_image_header_t *) data )->data_write_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data write identifier.",
		 function );

		return( -1 );
	}
	image_header->data_write_identifier[ 0 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 3 ];
	image_header->data_write_identifier[ 1 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 2 ];
	image_header->data_write_identifier[ 2 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 1 ];
	image_header->data_write_identifier[ 3 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 0 ];

	image_header->data_write_identifier[ 4 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 5 ];
	image_header->data_write_identifier[ 5 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 4 ];

	image_header->data_write_identifier[ 6 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 7 ];
	image_header->data_write_identifier[ 7 ] = ( (vhdi_image_header_t *) data )->data_write_identifier[ 6 ];

	if( memory_copy(
	     &( image_header->data_write_identifier[ 8 ] ),
	     &( ( (vhdi_image_header_t *) data )->data_write_identifier[ 8 ] ),
	     8 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data write identifier.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (vhdi_image_header_t *) data )->signature[ 0 ],
		 ( (vhdi_image_header_t *) data )->signature[ 1 ],
		 ( (vhdi_image_header_t *) data )->signature[ 2 ],
		 ( (vhdi_image_header_t *) data )->signature[ 3 ] );

		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 image_header->checksum );

		libcnotify_printf(
		 "%s: sequence number\t\t\t\t: %" PRIu64 "\n",
		 function,
		 image_header->sequence_number );

		if( libvhdi_debug_print_guid_value(
		     function,
		     "file write identifier\t\t\t",
		     ( (vhdi_image_header_t *) data )->file_write_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
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
		if( libvhdi_debug_print_guid_value(
		     function,
		     "data write identifier\t\t\t",
		     ( (vhdi_image_header_t *) data )->data_write_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
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

		if( libvhdi_debug_print_guid_value(
		     function,
		     "log identifier\t\t\t\t",
		     ( (vhdi_image_header_t *) data )->log_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
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
		byte_stream_copy_to_uint16_little_endian(
		 ( (vhdi_image_header_t *) data )->log_format_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: log format version\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu16 "\n",
		 function,
		 image_header->format_version );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vhdi_image_header_t *) data )->log_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: log size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vhdi_image_header_t *) data )->log_offset,
		 value_64bit );
		libcnotify_printf(
		 "%s: log offset\t\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 ( (vhdi_image_header_t *) data )->unknown1,
		 4016,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( image_header->format_version != 0x0001 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: 0x%04" PRIx16 ".",
		 function,
		 image_header->format_version );

		return( -1 );
	}
	return( 1 );
}

/* Reads the image header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_image_header_read_file_io_handle(
     libvhdi_image_header_t *image_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t image_header_data[ sizeof( vhdi_image_header_t ) ];

	static char *function = "libvhdi_image_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading image header at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              image_header_data,
	              sizeof( vhdi_image_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( vhdi_image_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read image header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libvhdi_image_header_read_data(
	     image_header,
	     image_header_data,
	     sizeof( vhdi_image_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read image header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
int libvhdi_image_header_get_format_version(
     libvhdi_image_header_t *image_header,
     uint16_t *major_version,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_image_header_get_format_version";

	if( image_header == NULL )
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
	*major_version = image_header->format_version;

	return( 1 );
}

/* Retrieves the data write identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvhdi_image_header_get_data_write_identifier(
     libvhdi_image_header_t *image_header,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_image_header_get_data_write_identifier";

	if( image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
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
	     image_header->data_write_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data write identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

