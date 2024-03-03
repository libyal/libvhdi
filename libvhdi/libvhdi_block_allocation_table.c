/*
 * Block allocation table functions
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

#include "libvhdi_block_allocation_table.h"
#include "libvhdi_block_descriptor.h"
#include "libvhdi_definitions.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfdata.h"
#include "libvhdi_unused.h"

/* Creates a block allocation table
 * Make sure the value block_allocation_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_allocation_table_initialize(
     libvhdi_block_allocation_table_t **block_allocation_table,
     uint32_t number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_allocation_table_initialize";

	if( block_allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block allocation table.",
		 function );

		return( -1 );
	}
	if( *block_allocation_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block allocation table value already set.",
		 function );

		return( -1 );
	}
	if( number_of_entries == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of entries: %" PRIu32 " value out of bounds.",
		 function,
		 number_of_entries );

		return( -1 );
	}
	*block_allocation_table = memory_allocate_structure(
	                           libvhdi_block_allocation_table_t );

	if( *block_allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block allocation table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_allocation_table,
	     0,
	     sizeof( libvhdi_block_allocation_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block allocation table.",
		 function );

		memory_free(
		 *block_allocation_table );

		*block_allocation_table = NULL;

		return( -1 );
	}
	( *block_allocation_table )->number_of_entries = number_of_entries;

	return( 1 );

on_error:
	if( *block_allocation_table != NULL )
	{
		memory_free(
		 *block_allocation_table );

		*block_allocation_table = NULL;
	}
	return( -1 );
}

/* Frees a block allocation table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_allocation_table_free(
     libvhdi_block_allocation_table_t **block_allocation_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_allocation_table_free";

	if( block_allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block allocation table.",
		 function );

		return( -1 );
	}
	if( *block_allocation_table != NULL )
	{
		memory_free(
		 *block_allocation_table );

		*block_allocation_table = NULL;
	}
	return( 1 );
}

/* Reads the block allocation table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_allocation_table_read_file_io_handle(
     libvhdi_block_allocation_table_t *block_allocation_table,
     libbfio_handle_t *file_io_handle,
     int file_type,
     uint32_t disk_type,
     off64_t file_offset,
     uint32_t block_size,
     uint32_t bytes_per_sector,
     libcerror_error_t **error )
{
	static char *function                        = "libvhdi_block_allocation_table_read_file_io_handle";
	uint64_t entries_per_chunk                   = 0;
	uint32_t sector_bitmap_size                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint8_t empty_table_entry_data[ 8 ] = {
		0, 0, 0, 0, 0, 0, 0, 0 };

	libvhdi_block_descriptor_t *block_descriptor = NULL;
	uint8_t *data                                = NULL;
	size_t data_offset                           = 0;
	size_t read_size                             = 0;
	ssize_t read_count                           = 0;
	uint64_t table_entries_size                  = 0;
#endif

	if( block_allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block allocation table.",
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
	if( block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of block size: %" PRIu32 " value out of bounds.",
		 function,
		 block_size );

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
	block_allocation_table->file_type        = file_type;
	block_allocation_table->disk_type        = disk_type;
	block_allocation_table->file_offset      = file_offset;
	block_allocation_table->block_size       = block_size;
	block_allocation_table->bytes_per_sector = bytes_per_sector;

	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		sector_bitmap_size = block_size / ( 512 * 8 );

		if( ( sector_bitmap_size % 512 ) != 0 )
		{
			sector_bitmap_size /= 512;
			sector_bitmap_size += 1;
			sector_bitmap_size *= 512;
		}
		block_allocation_table->sector_bitmap_size = sector_bitmap_size;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		entries_per_chunk = ( ( (uint64_t) 1UL << 23 ) * bytes_per_sector ) / block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: bytes per sector\t: %" PRIu32 "\n",
			 function,
			 bytes_per_sector );

			libcnotify_printf(
			 "%s: entries per chunk\t: %" PRIu64 "\n",
			 function,
			 entries_per_chunk );
		}
#endif
		if( ( 1048576 % entries_per_chunk ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported entries per chunk.",
			 function );

			return( -1 );
		}
		block_allocation_table->entries_per_chunk  = (uint32_t) entries_per_chunk;
		block_allocation_table->sector_bitmap_size = 1048576 / entries_per_chunk;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sector bitmap size\t: %" PRIu32 "\n",
		 function,
		 block_allocation_table->sector_bitmap_size );
	}
#endif
	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		block_allocation_table->table_entry_size = 4;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		block_allocation_table->table_entry_size = 8;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: table entry size\t: %" PRIzd "\n",
		 function,
		 block_allocation_table->table_entry_size );

		libcnotify_printf(
		 "\n" );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( file_type == LIBVHDI_FILE_TYPE_VHDX )
		 && ( disk_type != LIBVHDI_DISK_TYPE_FIXED ) )
		{
			table_entries_size = block_allocation_table->number_of_entries / entries_per_chunk;

			if( ( block_allocation_table->number_of_entries % entries_per_chunk ) != 0 )
			{
				table_entries_size += 1;
			}
			table_entries_size *= entries_per_chunk + 1;
		}
		else
		{
			table_entries_size = block_allocation_table->number_of_entries;
		}
		table_entries_size *= block_allocation_table->table_entry_size;

		libcnotify_printf(
		 "%s: table entries size\t: %" PRIu64 "\n",
		 function,
		 table_entries_size );

		file_offset += sector_bitmap_size;

		libcnotify_printf(
		 "%s: reading block allocation table at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );

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
			 "%s: unable to block allocation table at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		data = (uint8_t *) memory_allocate(
		                    sizeof( uint8_t ) * 64 * 1024 );

		if( data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create block allocation table entries data.",
			 function );

			goto on_error;
		}
		if( libvhdi_block_descriptor_initialize(
		     &block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create block descriptor.",
			 function );

			goto on_error;
		}
		while( table_entries_size > 0 )
		{
			read_size = 64 * 1024;

			if( read_size > table_entries_size )
			{
				read_size = table_entries_size;
			}
			read_count = libbfio_handle_read_buffer(
			              file_io_handle,
			              data,
			              read_size,
			              error );

			if( read_count != (ssize_t) read_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read block allocation table entries data.",
				 function );

				goto on_error;
			}
			libcnotify_print_data(
			 data,
			 read_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

			data_offset = 0;

			while( data_offset < read_size )
			{
				if( memory_compare(
				     &( data[ data_offset ] ),
				     empty_table_entry_data,
				     block_allocation_table->table_entry_size ) != 0 )
				{
					if( libvhdi_block_descriptor_read_table_entry_data(
					     block_descriptor,
					     &( data[ data_offset ] ),
					     block_allocation_table->table_entry_size,
					     file_type,
					     block_allocation_table->sector_bitmap_size,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_IO,
						 LIBCERROR_IO_ERROR_READ_FAILED,
						 "%s: unable to read allocation table entry.",
						 function );

						goto on_error;
					}
				}
				data_offset += block_allocation_table->table_entry_size;
			}
			table_entries_size -= read_size;
		}
		if( libvhdi_block_descriptor_free(
		     &block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free block descriptor.",
			 function );

			goto on_error;
		}
		memory_free(
		 data );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

#if defined( HAVE_DEBUG_OUTPUT )

on_error:
	if( block_descriptor != NULL )
	{
		libvhdi_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );

#endif
}

/* Reads a block allocation table entry
 * Callback function for the data block vector
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_allocation_table_read_element_data(
     libvhdi_block_allocation_table_t *block_allocation_table,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index LIBVHDI_ATTRIBUTE_UNUSED,
     off64_t element_data_offset LIBVHDI_ATTRIBUTE_UNUSED,
     size64_t element_data_size LIBVHDI_ATTRIBUTE_UNUSED,
     uint32_t element_data_flags LIBVHDI_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBVHDI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvhdi_block_descriptor_t *block_descriptor               = NULL;
	libvhdi_block_descriptor_t *sector_bitmap_block_descriptor = NULL;
	static char *function                                      = "libvhdi_block_allocation_table_read_element_data";
	off64_t sector_bitmap_offset                               = 0;
	off64_t table_entry_offset                                 = 0;

	LIBVHDI_UNREFERENCED_PARAMETER( element_data_file_index );
	LIBVHDI_UNREFERENCED_PARAMETER( element_data_offset );
	LIBVHDI_UNREFERENCED_PARAMETER( element_data_size );
	LIBVHDI_UNREFERENCED_PARAMETER( element_data_flags );
	LIBVHDI_UNREFERENCED_PARAMETER( read_flags );

	if( block_allocation_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block allocation table.",
		 function );

		return( -1 );
	}
	if( libvhdi_block_descriptor_initialize(
	     &block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block descriptor.",
		 function );

		goto on_error;
	}
	table_entry_offset = element_index;

	if( ( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHDX )
	 && ( block_allocation_table->disk_type != LIBVHDI_DISK_TYPE_FIXED ) )
	{
		table_entry_offset /= block_allocation_table->entries_per_chunk;
		table_entry_offset *= block_allocation_table->entries_per_chunk + 1;
		table_entry_offset += element_index % block_allocation_table->entries_per_chunk;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: table entry index\t: %" PRIi64 "\n",
		 function,
		 table_entry_offset );
	}
#endif
	table_entry_offset *= block_allocation_table->table_entry_size;
	table_entry_offset += block_allocation_table->file_offset;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: table entry offset\t: %" PRIi64 "\n",
		 function,
		 table_entry_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( libvhdi_block_descriptor_read_table_entry_file_io_handle(
	     block_descriptor,
	     file_io_handle,
	     block_allocation_table->file_type,
	     table_entry_offset,
	     block_allocation_table->sector_bitmap_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block allocation table entry: %d.",
		 function,
		 element_index );

		goto on_error;
	}
	if( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		sector_bitmap_offset = block_descriptor->file_offset;

		if( sector_bitmap_offset != -1 )
		{
			sector_bitmap_offset -= block_allocation_table->sector_bitmap_size;
		}
	}
	else if( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		if( block_allocation_table->disk_type != LIBVHDI_DISK_TYPE_DIFFERENTIAL )
		{
			sector_bitmap_offset = -1;
		}
		else
		{
			if( block_allocation_table->entries_per_chunk == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid block allocation table - missing entries per chunk.",
				 function );

				goto on_error;
			}
			if( libvhdi_block_descriptor_initialize(
			     &sector_bitmap_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create sector bitmap block descriptor.",
				 function );

				goto on_error;
			}
			table_entry_offset  = 1 + ( element_index / block_allocation_table->entries_per_chunk );
			table_entry_offset *= block_allocation_table->entries_per_chunk + 1;
			table_entry_offset -= 1;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: bitmap entry index\t: %" PRIi64 "\n",
				 function,
				 table_entry_offset );
			}
#endif
			table_entry_offset *= block_allocation_table->table_entry_size;
			table_entry_offset += block_allocation_table->file_offset;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: bitmap entry offset\t: %" PRIi64 "\n",
				 function,
				 table_entry_offset );

				libcnotify_printf(
				 "\n" );
			}
#endif
			if( libvhdi_block_descriptor_read_table_entry_file_io_handle(
			     sector_bitmap_block_descriptor,
			     file_io_handle,
			     block_allocation_table->file_type,
			     table_entry_offset,
			     block_allocation_table->sector_bitmap_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read sector bitmap block allocation table entry.",
				 function );

				goto on_error;
			}
			sector_bitmap_offset  = sector_bitmap_block_descriptor->file_offset;
			sector_bitmap_offset += ( element_index % block_allocation_table->entries_per_chunk ) * block_allocation_table->sector_bitmap_size;

			if( libvhdi_block_descriptor_free(
			     &sector_bitmap_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free sector bitmap block descriptor.",
				 function );

				goto on_error;
			}
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sector bitmap offset\t: %" PRIi64 "\n",
		 function,
		 sector_bitmap_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( libvhdi_block_descriptor_read_sector_bitmap_file_io_handle(
	     block_descriptor,
	     file_io_handle,
	     block_allocation_table->file_type,
	     sector_bitmap_offset,
	     block_allocation_table->block_size,
	     block_allocation_table->sector_bitmap_size,
	     block_allocation_table->bytes_per_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block: %d sector bitmap.",
		 function,
		 element_index );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) block_descriptor,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_block_descriptor_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set block descriptor as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sector_bitmap_block_descriptor != NULL )
	{
		libvhdi_block_descriptor_free(
		 &sector_bitmap_block_descriptor,
		 NULL );
	}
	if( block_descriptor != NULL )
	{
		libvhdi_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 1 );
}

