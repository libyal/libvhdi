/*
 * Region table functions
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

#include "libvhdi_checksum.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_region_table.h"
#include "libvhdi_region_table_entry.h"
#include "libvhdi_region_table_header.h"

#include "vhdi_region_table.h"

/* Creates region table
 * Make sure the value region_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_initialize(
     libvhdi_region_table_t **region_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_initialize";

	if( region_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table.",
		 function );

		return( -1 );
	}
	if( *region_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid region table value already set.",
		 function );

		return( -1 );
	}
	*region_table = memory_allocate_structure(
	                 libvhdi_region_table_t );

	if( *region_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create region table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *region_table,
	     0,
	     sizeof( libvhdi_region_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear region table.",
		 function );

		memory_free(
		 *region_table );

		*region_table = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *region_table )->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *region_table != NULL )
	{
		memory_free(
		 *region_table );

		*region_table = NULL;
	}
	return( -1 );
}

/* Frees region table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_free(
     libvhdi_region_table_t **region_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_free";
	int result            = 1;

	if( region_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table.",
		 function );

		return( -1 );
	}
	if( *region_table != NULL )
	{
		if( ( *region_table )->header != NULL )
		{
			if( libvhdi_region_table_header_free(
			     &( ( *region_table )->header ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free header.",
				 function );

				result = -1;
			}
		}
		if( libcdata_array_free(
		     &( ( *region_table )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_region_table_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *region_table );

		*region_table = NULL;
	}
	return( result );
}

/* Reads the region table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_read_file_io_handle(
     libvhdi_region_table_t *region_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	libvhdi_region_table_entry_t *region_table_entry = NULL;
	uint8_t *data                                    = NULL;
	static char *function                            = "libvhdi_region_table_read_file_io_handle";
	size_t data_offset                               = 0;
	size_t data_size                                 = 64 * 1024;
	ssize_t read_count                               = 0;
	uint32_t calculated_checksum                     = 0;
	uint32_t region_table_entry_index                = 0;
	int entry_index                                  = 0;

	if( region_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table.",
		 function );

		return( -1 );
	}
	if( region_table->header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid region table - header already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading region table at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * data_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create region table data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              data_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read region table data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libvhdi_region_table_header_initialize(
	     &( region_table->header ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create header.",
		 function );

		goto on_error;
	}
	if( libvhdi_region_table_header_read_data(
	     region_table->header,
	     data,
	     sizeof( vhdi_region_table_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read region table header.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( vhdi_region_table_header_t );

	byte_stream_copy_from_uint32_little_endian(
	 &( data[ 4 ] ),
	 0 );

	if( libvhdi_checksum_calculate_crc32(
	     &calculated_checksum,
	     data,
	     data_size,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to calculate CRC-32.",
		 function );

		goto on_error;
	}
	if( region_table->header->checksum != calculated_checksum )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: mismatch in checksum ( 0x%08" PRIx32 " != 0x%08" PRIx32 " ).",
		 function,
		 region_table->header->checksum,
		 calculated_checksum );

		goto on_error;
	}
	for( region_table_entry_index = 0;
	     region_table_entry_index < region_table->header->number_of_entries;
	     region_table_entry_index++ )
	{
		if( libvhdi_region_table_entry_initialize(
		     &region_table_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create entry.",
			 function );

			goto on_error;
		}
		if( libvhdi_region_table_entry_read_data(
		     region_table_entry,
		     &( data[ data_offset ] ),
		     sizeof( vhdi_region_table_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read region table entry.",
			 function );

			goto on_error;
		}
		data_offset += sizeof( vhdi_region_table_entry_t );

		if( libcdata_array_append_entry(
		     region_table->entries_array,
		     &entry_index,
		     (intptr_t *) region_table_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append region table entry to entries array.",
			 function );

			goto on_error;
		}
		region_table_entry = NULL;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( region_table->header != NULL )
	{
		libvhdi_region_table_header_free(
		 &( region_table->header ),
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

/* Retrieves the entry of a specific type identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_region_table_get_entry_by_type_identifier(
     libvhdi_region_table_t *region_table,
     const uint8_t *region_type_identifier,
     libvhdi_region_table_entry_t **entry,
     libcerror_error_t **error )
{
	libvhdi_region_table_entry_t *safe_entry = NULL;
	static char *function                    = "libvhdi_region_table_get_entry_by_type_identifier";
	int entry_index                          = 0;
	int number_of_entries                    = 0;

	if( region_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table.",
		 function );

		return( -1 );
	}
	if( region_type_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region type identifier.",
		 function );

		return( -1 );
	}
	if( entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	*entry = NULL;

	if( libcdata_array_get_number_of_entries(
	     region_table->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from array.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     region_table->entries_array,
		     entry_index,
		     (intptr_t **) &safe_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from array.",
			 function,
			 entry_index );

			return( -1 );
		}
/* TODO move compare into function */
		if( safe_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( memory_compare(
		     safe_entry->type_identifier,
		     region_type_identifier,
		     16 ) == 0 )
		{
			*entry = safe_entry;

			return( 1 );
		}
	}
	return( 0 );
}

