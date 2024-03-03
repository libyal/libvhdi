/*
 * Parent locator functions
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

#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libuna.h"
#include "libvhdi_parent_locator.h"
#include "libvhdi_parent_locator_entry.h"
#include "libvhdi_parent_locator_header.h"

#include "vhdi_parent_locator.h"

/* Creates parent locator
 * Make sure the value parent_locator is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_initialize(
     libvhdi_parent_locator_t **parent_locator,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_initialize";

	if( parent_locator == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator.",
		 function );

		return( -1 );
	}
	if( *parent_locator != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid parent locator value already set.",
		 function );

		return( -1 );
	}
	*parent_locator = memory_allocate_structure(
	                   libvhdi_parent_locator_t );

	if( *parent_locator == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create parent locator.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *parent_locator,
	     0,
	     sizeof( libvhdi_parent_locator_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear parent locator.",
		 function );

		memory_free(
		 *parent_locator );

		*parent_locator = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *parent_locator )->entries_array ),
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
	if( *parent_locator != NULL )
	{
		memory_free(
		 *parent_locator );

		*parent_locator = NULL;
	}
	return( -1 );
}

/* Frees parent locator
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_free(
     libvhdi_parent_locator_t **parent_locator,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_free";
	int result            = 1;

	if( parent_locator == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator.",
		 function );

		return( -1 );
	}
	if( *parent_locator != NULL )
	{
		if( ( *parent_locator )->header != NULL )
		{
			if( libvhdi_parent_locator_header_free(
			     &( ( *parent_locator )->header ),
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
		     &( ( *parent_locator )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvhdi_parent_locator_entry_free,
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
		 *parent_locator );

		*parent_locator = NULL;
	}
	return( result );
}

/* Reads the parent locator
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_read_data(
     libvhdi_parent_locator_t *parent_locator,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libvhdi_parent_locator_entry_t *parent_locator_entry = NULL;
	static char *function                                = "libvhdi_parent_locator_read_data";
	size_t data_offset                                   = 0;
	uint32_t parent_locator_entry_index                  = 0;
	int entry_index                                      = 0;

	if( parent_locator == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator.",
		 function );

		return( -1 );
	}
	if( parent_locator->header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid parent locator - header already set.",
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
	if( ( data_size < sizeof( vhdi_parent_locator_header_t ) )
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
	if( libvhdi_parent_locator_header_initialize(
	     &( parent_locator->header ),
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
	if( libvhdi_parent_locator_header_read_data(
	     parent_locator->header,
	     data,
	     sizeof( vhdi_parent_locator_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read parent locator header.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( vhdi_parent_locator_header_t );

	for( parent_locator_entry_index = 0;
	     parent_locator_entry_index < parent_locator->header->number_of_entries;
	     parent_locator_entry_index++ )
	{
		if( data_offset > ( data_size - sizeof( vhdi_parent_locator_entry_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data size value out of bounds.",
			 function );

			goto on_error;
		}
		if( libvhdi_parent_locator_entry_initialize(
		     &parent_locator_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create parent locator entry: %d.",
			 function,
			 parent_locator_entry_index );

			goto on_error;
		}
		if( libvhdi_parent_locator_entry_read_data(
		     parent_locator_entry,
		     &( data[ data_offset ] ),
		     sizeof( vhdi_parent_locator_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read parent locator entry: %d.",
			 function,
			 parent_locator_entry_index );

			goto on_error;
		}
		data_offset += sizeof( vhdi_parent_locator_entry_t );

		if( libvhdi_parent_locator_entry_read_key_value_data(
		     parent_locator_entry,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read parent locator entry: %d key and value.",
			 function,
			 parent_locator_entry_index );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     parent_locator->entries_array,
		     &entry_index,
		     (intptr_t *) parent_locator_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append parent locator entry to entries array.",
			 function );

			goto on_error;
		}
		parent_locator_entry = NULL;
	}
	return( 1 );

on_error:
	if( parent_locator_entry != NULL )
	{
		libvhdi_parent_locator_entry_free(
		 &parent_locator_entry,
		 NULL );
	}
	if( parent_locator->header != NULL )
	{
		libvhdi_parent_locator_header_free(
		 &( parent_locator->header ),
		 NULL );
	}
	return( -1 );
}

/* Retrieves the entry of a specific UTF-8 formatted key
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_parent_locator_get_entry_by_utf8_key(
     libvhdi_parent_locator_t *parent_locator,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libvhdi_parent_locator_entry_t **entry,
     libcerror_error_t **error )
{
	libvhdi_parent_locator_entry_t *safe_entry = NULL;
	static char *function                      = "libvhdi_parent_locator_get_entry_by_utf8_key";
	int entry_index                            = 0;
	int number_of_entries                      = 0;
	int result                                 = 0;

	if( parent_locator == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( ( utf8_string_length == 0 )
	 || ( utf8_string_length > (size_t) ( SSIZE_MAX - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string length value out of bounds.",
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
	     parent_locator->entries_array,
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
		     parent_locator->entries_array,
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
		result = libvhdi_parent_locator_compare_key_with_utf8_string(
		          safe_entry,
		          utf8_string,
		          utf8_string_length,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare UTF-8 string with key.",
			 function );

			return( -1 );
		}
		else if( result == LIBUNA_COMPARE_EQUAL )
		{
			*entry = safe_entry;

			return( 1 );
		}
	}
	return( 0 );
}

