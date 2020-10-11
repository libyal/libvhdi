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
#include "libvhdi_definitions.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"

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
		( *block_allocation_table )->table_entry_size   = 4;
	}
	else if( file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		( *block_allocation_table )->table_entry_size   = 8;
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

/* Retrieves the values of a specific block
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_allocation_table_get_block_values(
     libvhdi_block_allocation_table_t *block_allocation_table,
     libbfio_handle_t *file_io_handle,
     uint64_t block_number,
     off64_t *block_file_offset,
     uint32_t *block_flags,
     libcerror_error_t **error )
{
	uint8_t table_entry_data[ 8 ];

	static char *function          = "libvhdi_block_allocation_table_get_block_values";
	ssize_t read_count             = 0;
	off64_t file_offset            = 0;
	off64_t safe_block_file_offset = 0;
	uint64_t table_entry           = 0;
	uint32_t safe_block_flags      = 0;

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
	if( block_number >= (uint64_t) block_allocation_table->number_of_entries )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block number value out of bounds.",
		 function );

		return( -1 );
	}
	if( block_file_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block file offset.",
		 function );

		return( -1 );
	}
	if( block_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block flags.",
		 function );

		return( -1 );
	}
/* TODO read table entries 64 at a time ? */

	file_offset = block_allocation_table->file_offset + ( (off64_t) block_number * (off64_t) block_allocation_table->table_entry_size );

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
		 "%s: unable to seek block allocation table entry: %" PRIu64 " offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 block_number,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              table_entry_data,
	              block_allocation_table->table_entry_size,
	              error );

	if( read_count != (ssize_t) block_allocation_table->table_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block allocation table entry: %" PRIu64 ".",
		 function,
		 block_number );

		return( -1 );
	}
	if( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		byte_stream_copy_to_uint32_big_endian(
		 table_entry_data,
		 table_entry );
	}
	else if( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
		byte_stream_copy_to_uint64_little_endian(
		 table_entry_data,
		 table_entry );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block number\t\t\t: %" PRIu64 "\n",
		 function,
		 block_number );

		libcnotify_printf(
		 "%s: entry\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 table_entry );
	}
#endif
	if( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHD )
	{
		if( table_entry == 0xffffffffUL )
		{
			safe_block_file_offset = -1;
			safe_block_flags       = LIBFDATA_BLOCK_FLAG_IS_SPARSE;
		}
		else
		{
			safe_block_file_offset = table_entry * 512 + block_allocation_table->sector_bitmap_size;
		}
	}
	else if( block_allocation_table->file_type == LIBVHDI_FILE_TYPE_VHDX )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block state\t\t\t: %" PRIu64 "\n",
			 function,
			 table_entry & 0x7 );

			libcnotify_printf(
			 "%s: unknown1\t\t\t: 0x%04" PRIx64 "\n",
			 function,
			 ( table_entry >> 3 ) & 0x1ffff );
		}
#endif
/* TODO check for supported block states
 */
		if( ( table_entry & 0x7 ) <= 3 )
		{
			safe_block_flags = LIBFDATA_BLOCK_FLAG_IS_SPARSE;
		}
		safe_block_file_offset = ( table_entry >> 20 ) * 1024 * 1024;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( safe_block_flags & LIBFDATA_BLOCK_FLAG_IS_SPARSE ) != 0 )
		{
			libcnotify_printf(
			 "%s: is sparse or stored in parent.\n",
			 function );
		}
		else
		{
			libcnotify_printf(
			 "%s: block offset\t\t\t: 0x%08" PRIx64 ".\n",
			 function,
			 safe_block_file_offset );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	*block_file_offset = safe_block_file_offset;
	*block_flags       = safe_block_flags;

	return( 1 );
}

