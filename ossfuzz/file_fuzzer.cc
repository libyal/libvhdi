/*
 * OSS-Fuzz target for libvhdi file type
 *
 * Copyright (C) 2012-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libvhdi.h"

#if !defined( LIBVHDI_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_file_open_file_io_handle(
     libvhdi_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvhdi_error_t **error );

#endif /* !defined( LIBVHDI_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t buffer[ 512 ];
	uint8_t guid[ 16 ];
	uint8_t utf8_string[ 64 ];
	uint16_t utf16_string[ 64 ];

	libbfio_handle_t *file_io_handle = NULL;
	libvhdi_file_t *file             = NULL;
	off64_t media_offset             = 0;
	size64_t media_size              = 0;
	size_t string_size               = 0;
	uint32_t value_32bit             = 0;
	uint16_t major_version           = 0;
	uint16_t minor_version           = 0;
	int file_type                    = 0;
	int read_iterator                = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvhdi_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvhdi_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBVHDI_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_file_type(
	     file,
	     &file_type,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_format_version(
	     file,
	     &major_version,
	     &minor_version,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_disk_type(
	     file,
	     &value_32bit,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_bytes_per_sector(
	     file,
	     &value_32bit,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_identifier(
	     file,
	     guid,
	     16,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_parent_identifier(
	     file,
	     guid,
	     16,
	     NULL ) == -1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_utf8_parent_filename_size(
	     file,
	     &string_size,
	     NULL ) == -1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_utf8_parent_filename(
	     file,
	     utf8_string,
	     64,
	     NULL ) == -1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_utf16_parent_filename_size(
	     file,
	     &string_size,
	     NULL ) == -1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_utf16_parent_filename(
	     file,
	     utf16_string,
	     64,
	     NULL ) == -1 )
	{
		goto on_error_libvhdi;
	}
	if( libvhdi_file_get_media_size(
	     file,
	     &media_size,
	     NULL ) != 1 )
	{
		goto on_error_libvhdi;
	}
	for( read_iterator = 0;
	     read_iterator < 128;
	     read_iterator++ )
	{
		if( media_offset >= media_size )
		{
			break;
		}
		if( libvhdi_file_read_buffer_at_offset(
		     file,
		     buffer,
		     497,
		     media_offset,
		     NULL ) == -1 )
		{
			goto on_error_libvhdi;
		}
		media_offset += 497;
	}
	libvhdi_file_close(
	 file,
	 NULL );

on_error_libvhdi:
	libvhdi_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */

