/*
 * OSS-Fuzz target for libvhdi block descriptor type
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

/* Determines if a file contains a VHD file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVHDI_EXTERN \
int libvhdi_check_file_signature_file_io_handle(
      libbfio_handle_t *file_io_handle,
      libvhdi_error_t **error );

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

#define BLOCK_DESCRIPTOR_FUZZER_MAXIMUM_READ_ITERATIONS 128

#define BLOCK_DESCRIPTOR_FUZZER_MAXIMUM_READ_SIZE       4096

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	uint8_t buffer[ BLOCK_DESCRIPTOR_FUZZER_MAXIMUM_READ_SIZE ];
	uint8_t guid[ 16 ];

	libbfio_handle_t *parent_file_io_handle = NULL;
	libbfio_handle_t *file_io_handle        = NULL;
	libvhdi_file_t *parent_file             = NULL;
	libvhdi_file_t *file                    = NULL;
	off64_t media_offset                    = 0;
	off64_t read_offset                     = 0;
	size64_t media_size                      = 0;
	size_t read_size                         = 0;
	int file_type                            = 0;
	int parent_ready                         = 0;
	int read_iterator                        = 0;
	uint32_t value_32bit                     = 0;
	uint16_t major_version                   = 0;
	uint16_t minor_version                   = 0;

	if( size == 0 )
	{
		return( 0 );
	}
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
	if( libvhdi_check_file_signature_file_io_handle(
	     file_io_handle,
	     NULL ) == -1 )
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
	if( libvhdi_file_get_media_size(
	     file,
	     &media_size,
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
	if( ( data[ 0 ] & 0x01 ) != 0 )
	{
		size_t parent_data_offset = size / 2;
		size_t parent_data_length = size - parent_data_offset;

		if( libbfio_memory_range_initialize(
		     &parent_file_io_handle,
		     NULL ) == 1
		 && libbfio_memory_range_set(
	                 parent_file_io_handle,
	                 (uint8_t * ) ( data + parent_data_offset ),
	                 parent_data_length,
	                 NULL ) == 1
		 && libvhdi_file_initialize(
	                 &parent_file,
	                 NULL ) == 1
		 && libvhdi_file_open_file_io_handle(
	                 parent_file,
	                 parent_file_io_handle,
	                 LIBVHDI_OPEN_READ,
	                 NULL ) == 1 )
		{
			/* A 0 result from set_parent_file means the parent does not match
			 * a -1 result indicates an error
			 */
			if( libvhdi_file_set_parent_file(
			     file,
			     parent_file,
			     NULL ) == 1 )
			{
				parent_ready = 1;
			}
		}
		if( parent_ready == 0 )
		{
			if( parent_file != NULL )
			{
				libvhdi_file_free(
				 &parent_file,
				 NULL );

				parent_file = NULL;
			}
			if( parent_file_io_handle != NULL )
			{
				libbfio_handle_free(
				 &parent_file_io_handle,
				 NULL );

				parent_file_io_handle = NULL;
			}
		}
	}
	if( media_size > 0 )
	{
		/* Bounded read of the media to exercise the block descriptor
		 * sector bitmap read path
		 */
		for( read_iterator = 0;
		    read_iterator < BLOCK_DESCRIPTOR_FUZZER_MAXIMUM_READ_ITERATIONS
		    && media_offset < ( off64_t ) media_size;
		    read_iterator++ )
		{
			if( ( data[ 0 ] & 0x02 ) != 0
			 && ( read_iterator % 4 ) == 3 )
			{
				libvhdi_file_signal_abort(
				 file,
				 NULL );
			}
			read_size = ( size_t ) ( ( read_iterator % 7 ) + 1 ) * 511;

			if( read_size > BLOCK_DESCRIPTOR_FUZZER_MAXIMUM_READ_SIZE )
			{
				read_size = BLOCK_DESCRIPTOR_FUZZER_MAXIMUM_READ_SIZE;
			}
			if( ( read_iterator % 2 ) == 0 )
			{
				if( media_offset + ( off64_t ) read_size > ( off64_t ) media_size )
				{
					break;
				}
				if( libvhdi_file_read_buffer_at_offset(
				     file,
				     buffer,
				     read_size,
				     media_offset,
				     NULL ) == -1 )
				{
					break;
				}
			}
			else
			{
				if( libvhdi_file_read_buffer(
				     file,
				     buffer,
				     read_size,
				     NULL ) == -1 )
				{
					break;
				}
				if( libvhdi_file_get_offset(
				     file,
				     &read_offset,
				     NULL ) == -1 )
				{
					break;
				}
			}
			media_offset += 4097;
		}
	}
	libvhdi_file_close(
	 file,
	 NULL );

on_error_libvhdi:
	libvhdi_file_free(
	 &file,
	 NULL );

	if( parent_file != NULL )
	{
		libvhdi_file_free(
		 &parent_file,
		 NULL );

		parent_file = NULL;
	}
on_error_libbfio:
	if( parent_file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &parent_file_io_handle,
		 NULL );

		parent_file_io_handle = NULL;
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );

		file_io_handle = NULL;
	}
	return( 0 );
}

} /* extern "C" */
