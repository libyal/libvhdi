/*
 * Metadata table functions
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
#include <memory.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_metadata_table.h"
#include "libvhdi_metadata_table_entry.h"
#include "libvhdi_metadata_table_header.h"

#include "vhdi_metadata_table.h"

/* Creates metadata table
 * Make sure the value metadata_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_initialize(
     libvhdi_metadata_table_t **metadata_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_initialize";

	if( metadata_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table.",
		 function );

		return( -1 );
	}
	if( *metadata_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata table value already set.",
		 function );

		return( -1 );
	}
	*metadata_table = memory_allocate_structure(
	                   libvhdi_metadata_table_t );

	if( *metadata_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create metadata table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *metadata_table,
	     0,
	     sizeof( libvhdi_metadata_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear metadata table.",
		 function );

		memory_free(
		 *metadata_table );

		*metadata_table = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *metadata_table )->entries_array ),
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
	if( *metadata_table != NULL )
	{
		memory_free(
		 *metadata_table );

		*metadata_table = NULL;
	}
	return( -1 );
}

/* Frees metadata table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_free(
     libvhdi_metadata_table_t **metadata_table,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_free";
	int result            = 1;

	if( metadata_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table.",
		 function );

		return( -1 );
	}
	if( *metadata_table != NULL )
	{
		if( ( *metadata_table )->header != NULL )
		{
			if( libvhdi_metadata_table_header_free(
			     &( ( *metadata_table )->header ),
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
		     &( ( *metadata_table )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_metadata_table_entry_free,
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
		 *metadata_table );

		*metadata_table = NULL;
	}
	return( result );
}

/* Reads the metadata table
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_read_file_io_handle(
     libvhdi_metadata_table_t *metadata_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	libvhdi_metadata_table_entry_t *metadata_table_entry = NULL;
	uint8_t *data                                        = NULL;
	static char *function                                = "libvhdi_metadata_table_read_file_io_handle";
	size_t data_offset                                   = 0;
	size_t data_size                                     = 64 * 1024;
	ssize_t read_count                                   = 0;
	uint32_t metadata_table_entry_index                  = 0;
	int entry_index                                      = 0;

	if( metadata_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table.",
		 function );

		return( -1 );
	}
	if( metadata_table->header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata table - header already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading metadata table at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
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
		 "%s: unable to create metadata table data.",
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
		 "%s: unable to read metadata table data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libvhdi_metadata_table_header_initialize(
	     &( metadata_table->header ),
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
	if( libvhdi_metadata_table_header_read_data(
	     metadata_table->header,
	     data,
	     sizeof( vhdi_metadata_table_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata table header.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( vhdi_metadata_table_header_t );

	for( metadata_table_entry_index = 0;
	     metadata_table_entry_index < metadata_table->header->number_of_entries;
	     metadata_table_entry_index++ )
	{
		if( libvhdi_metadata_table_entry_initialize(
		     &metadata_table_entry,
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
		if( libvhdi_metadata_table_entry_read_data(
		     metadata_table_entry,
		     &( data[ data_offset ] ),
		     sizeof( vhdi_metadata_table_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read metadata table entry.",
			 function );

			goto on_error;
		}
		data_offset += sizeof( vhdi_metadata_table_entry_t );

		if( libcdata_array_append_entry(
		     metadata_table->entries_array,
		     &entry_index,
		     (intptr_t *) metadata_table_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append metadata table entry to entries array.",
			 function );

			goto on_error;
		}
		metadata_table_entry = NULL;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( metadata_table_entry != NULL )
	{
		libvhdi_metadata_table_entry_free(
		 &metadata_table_entry,
		 NULL );
	}
	if( metadata_table->header != NULL )
	{
		libvhdi_metadata_table_header_free(
		 &( metadata_table->header ),
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	libcdata_array_empty(
	 metadata_table->entries_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_metadata_table_entry_free,
	 NULL );

	return( -1 );
}

/* Retrieves the number of entries
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_get_number_of_entries(
     libvhdi_metadata_table_t *metadata_table,
     int *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_get_number_of_entries";

	if( metadata_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     metadata_table->entries_array,
	     number_of_entries,
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
	return( 1 );
}

/* Retrieves a specific entry
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_get_entry_by_index(
     libvhdi_metadata_table_t *metadata_table,
     int entry_index,
     libvhdi_metadata_table_entry_t **entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_get_entry_by_index";

	if( metadata_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     metadata_table->entries_array,
	     entry_index,
	     (intptr_t **) entry,
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
	return( 1 );
}

