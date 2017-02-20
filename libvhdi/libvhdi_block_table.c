/*
 * Block table functions
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

#include "libvhdi_block_table.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"

/* Creates a block table
 * Make sure the value block_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_table_initialize(
     libvhdi_block_table_t **block_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_table_initialize";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( *block_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block table value already set.",
		 function );

		return( -1 );
	}
	*block_table = memory_allocate_structure(
	                libvhdi_block_table_t );

	if( *block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_table,
	     0,
	     sizeof( libvhdi_block_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block_table != NULL )
	{
		memory_free(
		 *block_table );

		*block_table = NULL;
	}
	return( -1 );
}

/* Frees a block table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_table_free(
     libvhdi_block_table_t **block_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_table_free";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( *block_table != NULL )
	{
		if( ( *block_table )->references != NULL )
		{
			memory_free(
			 ( *block_table )->references );
		}
		memory_free(
		 *block_table );

		*block_table = NULL;
	}
	return( 1 );
}

/* Retrieves the number of references in the block table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_table_get_number_of_references(
     libvhdi_block_table_t *block_table,
     int *number_of_references,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_table_get_number_of_references";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( number_of_references == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of references.",
		 function );

		return( -1 );
	}
	*number_of_references = block_table->number_of_references;

	return( 1 );
}

/* Retrieves a specific reference from the block table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_table_get_reference_by_index(
     libvhdi_block_table_t *block_table,
     int reference_index,
     uint32_t *reference,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_block_table_get_reference_by_index";

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( block_table->references == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block table - missing references.",
		 function );

		return( -1 );
	}
	if( ( reference_index < 0 )
	 || ( reference_index >= block_table->number_of_references ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid reference index value out of bounds.",
		 function );

		return( -1 );
	}
	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	*reference = block_table->references[ reference_index ];

	return( 1 );
}

/* Reads the block table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_block_table_read(
     libvhdi_block_table_t *block_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint32_t number_of_blocks,
     libcerror_error_t **error )
{
	uint8_t *block_table_data      = NULL;
	static char *function          = "libvhdi_block_table_read";
	size_t block_table_data_offset = 0;
	ssize_t read_count             = 0;
	uint32_t block_table_reference = 0;
	int block_table_index          = 0;

	if( block_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block table.",
		 function );

		return( -1 );
	}
	if( block_table->references != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block table - references already set.",
		 function );

		return( -1 );
	}
/* TODO improve check ? */
	if( (size_t) number_of_blocks > (size_t) INT_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of blocks value exceeds maximum.",
		 function );

		return( -1 );
	}
	block_table->size = number_of_blocks * sizeof( uint32_t );

	if( block_table->size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid block table size value exceeds maximum.",
		 function );

		return( -1 );
	}
	block_table->number_of_references = (int) number_of_blocks;

	block_table->references = (uint32_t *) memory_allocate(
	                                        block_table->size );

	if( block_table->references == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create references.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading block table at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
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
		 "%s: unable to seek block table offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	block_table_data = (uint8_t *) memory_allocate(
	                                block_table->size );

	if( block_table_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block table data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              block_table_data,
	              block_table->size,
	              error );

	if( read_count != (ssize_t) block_table->size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block table.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block table data:\n",
		 function );
		libcnotify_print_data(
		 block_table_data,
		 block_table->size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	for( block_table_index = 0;
	     block_table_index < block_table->number_of_references;
	     block_table_index++ )
	{
		byte_stream_copy_to_uint32_big_endian(
		 &( block_table_data[ block_table_data_offset ] ),
		 block_table_reference );

		block_table_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block table reference: %03d\t\t: 0x%08" PRIx32 "\n",
			 function,
			 block_table_index,
			 block_table_reference );
		}
#endif
		 ( block_table->references )[ block_table_index ] = block_table_reference;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	memory_free(
	 block_table_data );

	block_table_data = NULL;

	return( 1 );

on_error:
	if( block_table_data != NULL )
	{
		memory_free(
		 block_table_data );
	}
	if( block_table->references != NULL )
	{
		memory_free(
		 block_table->references );

		block_table->references = NULL;
	}
	return( -1 );
}

