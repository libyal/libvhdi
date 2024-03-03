/*
 * Block descriptor functions
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

#include "libvhdi_block_descriptor.h"
#include "libvhdi_debug.h"
#include "libvhdi_definitions.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_sector_range_descriptor.h"

/* Creates a block descriptor
 * Make sure the value block_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_descriptor_initialize(
     libvhdi_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_descriptor_initialize";

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( *block_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block descriptor value already set.",
		 function );

		return( -1 );
	}
	*block_descriptor = memory_allocate_structure(
	                     libvhdi_block_descriptor_t );

	if( *block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_descriptor,
	     0,
	     sizeof( libvhdi_block_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block descriptor.",
		 function );

		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *block_descriptor )->sector_ranges_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector ranges array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block_descriptor != NULL )
	{
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a block descriptor
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_descriptor_free(
     libvhdi_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_descriptor_free";
	int result            = 1;

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( *block_descriptor != NULL )
	{
		if( libcdata_array_free(
		     &( ( *block_descriptor )->sector_ranges_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_sector_range_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sector ranges array.",
			 function );

			result = -1;
		}
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( result );
}

/* Reads a block allocation table entry
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_descriptor_read_table_entry_data(
     libvhdi_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     int file_type,
     uint32_t sector_bitmap_size,
     libcerror_error_t **error )
{
	static char *function   = "libvhdi_block_descriptor_read_table_entry_data";
	size_t table_entry_size = 0;
	uint64_t table_entry    = 0;

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
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
	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		table_entry_size = 4;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		table_entry_size = 8;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file type.",
		 function );

		return( -1 );
	}
	if( data_size != table_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block allocation table entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		byte_stream_copy_to_uint32_big_endian(
		 data,
		 table_entry );
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		byte_stream_copy_to_uint64_little_endian(
		 data,
		 table_entry );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: entry\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 table_entry );
	}
#endif
	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		if( table_entry == 0xffffffffUL )
		{
			block_descriptor->file_offset = -1;
		}
		else
		{
			block_descriptor->file_offset = ( table_entry * 512 ) + sector_bitmap_size;
		}
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		block_descriptor->block_state = (uint8_t) ( table_entry & 0x7 );
		block_descriptor->file_offset = ( table_entry >> 20 ) * 1024 * 1024;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block state\t\t: %" PRIu64 " (%s)\n",
			 function,
			 block_descriptor->block_state,
			 libvhdi_debug_print_block_state(
			  block_descriptor->block_state ) );

			libcnotify_printf(
			 "%s: unknown1\t\t: 0x%04" PRIx64 "\n",
			 function,
			 ( table_entry >> 3 ) & 0x1ffff );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: offset\t\t\t: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 block_descriptor->file_offset,
		 block_descriptor->file_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads a block allocation table entry
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_descriptor_read_table_entry_file_io_handle(
     libvhdi_block_descriptor_t *block_descriptor,
     libbfio_handle_t *file_io_handle,
     int file_type,
     off64_t file_offset,
     uint32_t sector_bitmap_size,
     libcerror_error_t **error )
{
	uint8_t table_entry_data[ 8 ];

	static char *function   = "libvhdi_block_descriptor_read_table_entry_file_io_handle";
	size_t table_entry_size = 0;
	ssize_t read_count      = 0;

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		table_entry_size = 4;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		table_entry_size = 8;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file type.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading block allocation table entry at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              table_entry_data,
	              table_entry_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) table_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block allocation table entry data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libvhdi_block_descriptor_read_table_entry_data(
	     block_descriptor,
	     table_entry_data,
	     table_entry_size,
	     file_type,
	     sector_bitmap_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation table entry.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the sector bitmap
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_descriptor_read_sector_bitmap_data(
     libvhdi_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     int file_type,
     uint32_t bytes_per_sector,
     libcerror_error_t **error )
{
	libvhdi_sector_range_descriptor_t *sector_range_descriptor = NULL;
	static char *function                                      = "libvhdi_block_descriptor_read_sector_bitmap_data";
	size64_t range_size                                        = 0;
	size_t data_offset                                         = 0;
	off64_t range_offset                                       = 0;
	uint8_t bit_index                                          = 0;
	uint8_t byte_value                                         = 0;
	uint8_t element_value                                      = 0;
	uint8_t first_element_value                                = 0;
	int element_index                                          = 0;
	int entry_index                                            = 0;
	int first_element_index                                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	char *range_type                                           = NULL;
#endif

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
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
	if( ( data_size < 1 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( file_type != LIBVHDI_FILE_TYPE_VHD )
	 && ( file_type != LIBVHDI_FILE_TYPE_VHDX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file type.",
		 function );

		return( -1 );
	}
	if( ( bytes_per_sector != 512 )
	 && ( bytes_per_sector != 4096 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported bytes per sector.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sector bitmap data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		first_element_value = data[ data_offset ] >> 7;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		first_element_value = data[ data_offset ] & 0x01;
	}
	while( data_offset < data_size )
	{
		byte_value = data[ data_offset ];

		data_offset++;

		for( bit_index = 0;
		     bit_index < 8;
		     bit_index++ )
		{
			if( file_type == LIBVHDI_FILE_TYPE_VHD )
			{
				element_value = byte_value >> ( 7 - bit_index );
			}
			else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
			{
				element_value = byte_value & 0x01;
				byte_value  >>= 1;
			}
			if( element_value != first_element_value )
			{
				range_offset = (off64_t) first_element_index * bytes_per_sector;
				range_size   = ( (size64_t) element_index - first_element_index ) * bytes_per_sector;

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					if( first_element_value == 0 )
					{
						range_type = "unallocated";
					}
					else
					{
						range_type = "allocated";
					}
					libcnotify_printf(
					 "%s: %s sector range\t: 0x%08" PRIx64 " - 0x%08" PRIx64 " (%" PRIu64 ")\n",
					 function,
					 range_type,
					 range_offset,
					 range_offset + range_size,
					 range_size );
				}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

				if( libvhdi_sector_range_descriptor_initialize(
				     &sector_range_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create sector range descriptor.",
					 function );

					goto on_error;
				}
				sector_range_descriptor->start_offset = range_offset;
				sector_range_descriptor->end_offset   = range_offset + range_size;

				if( first_element_value == 0 )
				{
					sector_range_descriptor->flags = LIBFDATA_SECTOR_RANGE_FLAG_IS_UNALLOCATED;
				}
				if( libcdata_array_append_entry(
				     block_descriptor->sector_ranges_array,
				     &entry_index,
				     (intptr_t *) sector_range_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append sector range to array.",
					 function );

					goto on_error;
				}
				sector_range_descriptor = NULL;

				first_element_value = element_value;
				first_element_index = element_index;
			}
			element_index++;
		}
	}
	range_offset = (off64_t) first_element_index * bytes_per_sector;
	range_size   = ( (size64_t) element_index - first_element_index ) * bytes_per_sector;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( first_element_value == 0 )
		{
			range_type = "unallocated";
		}
		else
		{
			range_type = "allocated";
		}
		libcnotify_printf(
		 "%s: %s sector range\t: 0x%08" PRIx64 " - 0x%08" PRIx64 " (%" PRIu64 ")\n",
		 function,
		 range_type,
		 range_offset,
		 range_offset + range_size,
		 range_size );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( libvhdi_sector_range_descriptor_initialize(
	     &sector_range_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector range descriptor.",
		 function );

		goto on_error;
	}
	sector_range_descriptor->start_offset = range_offset;
	sector_range_descriptor->end_offset   = range_offset + range_size;

	if( first_element_value == 0 )
	{
		sector_range_descriptor->flags = LIBFDATA_SECTOR_RANGE_FLAG_IS_UNALLOCATED;
	}
	if( libcdata_array_append_entry(
	     block_descriptor->sector_ranges_array,
	     &entry_index,
	     (intptr_t *) sector_range_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append sector range to array.",
		 function );

		goto on_error;
	}
	sector_range_descriptor = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( sector_range_descriptor != NULL )
	{
		libvhdi_sector_range_descriptor_free(
		 &sector_range_descriptor,
		 NULL );
	}
	return( -1 );
}

/* Reads the sector bitmap
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_descriptor_read_sector_bitmap_file_io_handle(
     libvhdi_block_descriptor_t *block_descriptor,
     libbfio_handle_t *file_io_handle,
     int file_type,
     off64_t file_offset,
     uint32_t block_size,
     uint32_t sector_bitmap_size,
     uint32_t bytes_per_sector,
     libcerror_error_t **error )
{
	libvhdi_sector_range_descriptor_t *sector_range_descriptor = NULL;
	uint8_t *data                                              = NULL;
	static char *function                                      = "libvhdi_block_descriptor_read_sector_bitmap_file_io_handle";
	ssize_t read_count                                         = 0;
	int entry_index                                            = 0;

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( ( sector_bitmap_size == 0 )
	 || ( sector_bitmap_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block descriptor - invalid sector bitmap size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( file_offset == -1 )
	 || ( block_descriptor->block_state == 6 ) )
	{
		if( libvhdi_sector_range_descriptor_initialize(
		     &sector_range_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sector range descriptor.",
			 function );

			goto on_error;
		}
		sector_range_descriptor->start_offset = 0;
		sector_range_descriptor->end_offset   = block_size;

		if( ( file_type == LIBVHDI_FILE_TYPE_VHD )
		 || ( block_descriptor->block_state < 6 ) )
		{
			sector_range_descriptor->flags = LIBFDATA_SECTOR_RANGE_FLAG_IS_UNALLOCATED;
		}
		if( libcdata_array_append_entry(
		     block_descriptor->sector_ranges_array,
		     &entry_index,
		     (intptr_t *) sector_range_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append sector range to array.",
			 function );

			goto on_error;
		}
		sector_range_descriptor = NULL;
	}
	else
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading sector bitmap at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 file_offset,
			 file_offset );
		}
#endif
		data = (uint8_t *) memory_allocate(
		                    sizeof( uint8_t ) * sector_bitmap_size );

		if( data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create sector bitmap data.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer_at_offset(
		              file_io_handle,
		              data,
		              (size_t) sector_bitmap_size,
		              file_offset,
		              error );

		if( read_count != (ssize_t) sector_bitmap_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read sector bitmap data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		if( libvhdi_block_descriptor_read_sector_bitmap_data(
		     block_descriptor,
		     data,
		     (size_t) sector_bitmap_size,
		     file_type,
		     bytes_per_sector,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read sector bitmap.",
			 function );

			goto on_error;
		}
		memory_free(
		 data );
	}
	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	if( sector_range_descriptor != NULL )
	{
		libvhdi_sector_range_descriptor_free(
		 &sector_range_descriptor,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the sector range descriptor for a specific offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_block_descriptor_get_sector_range_descriptor_at_offset(
     libvhdi_block_descriptor_t *block_descriptor,
     off64_t offset,
     libvhdi_sector_range_descriptor_t **sector_range_descriptor,
     libcerror_error_t **error )
{
	libvhdi_sector_range_descriptor_t *safe_sector_range_descriptor = NULL;
	static char *function                                           = "libvhdi_block_descriptor_get_sector_range_descriptor_at_offset";
	int entry_index                                                 = 0;
	int number_of_entries                                           = 0;

/* TODO uses a sector number to sector range descriptor map for quick look up */
	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     block_descriptor->sector_ranges_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from sector ranges array.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     block_descriptor->sector_ranges_array,
		     entry_index,
		     (intptr_t **) &safe_sector_range_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve descriptor: %d from sector range array.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( safe_sector_range_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sector range descriptor: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( ( offset >= safe_sector_range_descriptor->start_offset )
		 && ( offset < safe_sector_range_descriptor->end_offset ) )
		{
			*sector_range_descriptor = safe_sector_range_descriptor;

			return( 1 );
		}
	}
	return( 0 );
}

