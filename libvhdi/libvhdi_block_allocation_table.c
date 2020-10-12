/*
 * Block allocation table functions
 *
 * Copyright (C) 2012-2020, Joachim Metz <joachim.metz@gmail.com>
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
     int file_type,
     off64_t file_offset,
     uint32_t block_size,
     uint32_t number_of_entries,
     libcerror_error_t **error )
{
	static char *function       = "libvhdi_block_allocation_table_initialize";
	uint32_t sector_bitmap_size = 0;

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
	( *block_allocation_table )->file_type         = file_type;
	( *block_allocation_table )->file_offset       = file_offset;
	( *block_allocation_table )->block_size        = block_size;
	( *block_allocation_table )->number_of_entries = number_of_entries;

	if( file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		sector_bitmap_size = block_size / ( 512 * 8 );

		if( ( sector_bitmap_size % 512 ) != 0 )
		{
			sector_bitmap_size /= 512;
			sector_bitmap_size += 1;
			sector_bitmap_size *= 512;
		}
		( *block_allocation_table )->sector_bitmap_size = sector_bitmap_size;

		( *block_allocation_table )->table_entry_size = 4;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		( *block_allocation_table )->table_entry_size = 8;
	}
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
	libvhdi_block_descriptor_t *block_descriptor = NULL;
	static char *function                        = "libvhdi_block_allocation_table_read_element_data";
	off64_t table_entry_offset                   = 0;

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
	table_entry_offset = block_allocation_table->file_offset + ( element_index * block_allocation_table->table_entry_size );

	if( libvhdi_block_descriptor_read_table_entry(
	     block_descriptor,
	     file_io_handle,
	     block_allocation_table->file_type,
	     table_entry_offset,
	     block_allocation_table->block_size,
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
	if( block_descriptor != NULL )
	{
		libvhdi_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 1 );
}

