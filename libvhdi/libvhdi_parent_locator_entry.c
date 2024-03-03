/*
 * Parent locator entry functions
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

#include "libvhdi_debug.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfguid.h"
#include "libvhdi_libuna.h"
#include "libvhdi_parent_locator_entry.h"

#include "vhdi_parent_locator.h"

/* Creates parent locator entry
 * Make sure the value parent_locator_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_entry_initialize(
     libvhdi_parent_locator_entry_t **parent_locator_entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_entry_initialize";

	if( parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator entry.",
		 function );

		return( -1 );
	}
	if( *parent_locator_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid parent locator entry value already set.",
		 function );

		return( -1 );
	}
	*parent_locator_entry = memory_allocate_structure(
	                         libvhdi_parent_locator_entry_t );

	if( *parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create parent locator entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *parent_locator_entry,
	     0,
	     sizeof( libvhdi_parent_locator_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear parent locator entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *parent_locator_entry != NULL )
	{
		memory_free(
		 *parent_locator_entry );

		*parent_locator_entry = NULL;
	}
	return( -1 );
}

/* Frees parent locator entry
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_entry_free(
     libvhdi_parent_locator_entry_t **parent_locator_entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_entry_free";

	if( parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator entry.",
		 function );

		return( -1 );
	}
	if( *parent_locator_entry != NULL )
	{
		if( ( *parent_locator_entry )->key_data != NULL )
		{
			memory_free(
			 ( *parent_locator_entry )->key_data );
		}
		if( ( *parent_locator_entry )->value_data != NULL )
		{
			memory_free(
			 ( *parent_locator_entry )->value_data );
		}
		memory_free(
		 *parent_locator_entry );

		*parent_locator_entry = NULL;
	}
	return( 1 );
}

/* Reads the parent locator entry data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_entry_read_data(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_entry_read_data";

	if( parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator entry.",
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
	if( ( data_size < sizeof( vhdi_parent_locator_entry_t ) )
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: parent locator entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_parent_locator_entry_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_parent_locator_entry_t *) data )->key_data_offset,
	 parent_locator_entry->key_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_parent_locator_entry_t *) data )->value_data_offset,
	 parent_locator_entry->value_data_offset );

	byte_stream_copy_to_uint16_little_endian(
	 ( (vhdi_parent_locator_entry_t *) data )->key_data_size,
	 parent_locator_entry->key_data_size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (vhdi_parent_locator_entry_t *) data )->value_data_size,
	 parent_locator_entry->value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: key data offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 parent_locator_entry->key_data_offset );

		libcnotify_printf(
		 "%s: value data offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 parent_locator_entry->value_data_offset );

		libcnotify_printf(
		 "%s: key data size\t\t\t: %" PRIu16 "\n",
		 function,
		 parent_locator_entry->key_data_size );

		libcnotify_printf(
		 "%s: value data size\t\t\t: %" PRIu16 "\n",
		 function,
		 parent_locator_entry->value_data_size );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the parent locator entry key and value data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_entry_read_key_value_data(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_entry_read_key_value_data";

	if( parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator entry.",
		 function );

		return( -1 );
	}
	if( parent_locator_entry->key_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid parent locator entry - key data already set.",
		 function );

		return( -1 );
	}
	if( parent_locator_entry->value_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid parent locator entry - value data already set.",
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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( parent_locator_entry->key_data_offset < sizeof( vhdi_parent_locator_header_t ) )
	 || ( parent_locator_entry->key_data_offset > data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid parent locator entry - key data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( parent_locator_entry->key_data_size == 0 )
	 || ( (size_t) parent_locator_entry->key_data_size > ( data_size - parent_locator_entry->key_data_offset ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid parent locator entry - key data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( parent_locator_entry->value_data_offset < sizeof( vhdi_parent_locator_header_t ) )
	 || ( parent_locator_entry->value_data_offset > data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid parent locator entry - value data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( parent_locator_entry->value_data_size == 0 )
	 || ( (size_t) parent_locator_entry->value_data_size > ( data_size - parent_locator_entry->value_data_offset ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid parent locator entry - value data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: key data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ parent_locator_entry->key_data_offset ] ),
		 (size_t) parent_locator_entry->key_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( libvhdi_debug_print_utf16_string_value(
		     function,
		     "key\t\t\t",
		     &( data[ parent_locator_entry->key_data_offset ] ),
		     (size_t) parent_locator_entry->key_data_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	parent_locator_entry->key_data = (uint8_t *) memory_allocate(
	                                              sizeof( uint8_t ) * parent_locator_entry->key_data_size );

	if( parent_locator_entry->key_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create key data.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     parent_locator_entry->key_data,
	     &( data[ parent_locator_entry->key_data_offset ] ),
	     (size_t) parent_locator_entry->key_data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy key data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ parent_locator_entry->value_data_offset ] ),
		 (size_t) parent_locator_entry->value_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( libvhdi_debug_print_utf16_string_value(
		     function,
		     "value\t\t\t",
		     &( data[ parent_locator_entry->value_data_offset ] ),
		     (size_t) parent_locator_entry->value_data_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	parent_locator_entry->value_data = (uint8_t *) memory_allocate(
	                                                sizeof( uint8_t ) * parent_locator_entry->value_data_size );

	if( parent_locator_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value data.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     parent_locator_entry->value_data,
	     &( data[ parent_locator_entry->value_data_offset ] ),
	     (size_t) parent_locator_entry->value_data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy value data.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( parent_locator_entry->key_data != NULL )
	{
		memory_free(
		 parent_locator_entry->key_data );

		parent_locator_entry->key_data = NULL;
	}
	if( parent_locator_entry->value_data != NULL )
	{
		memory_free(
		 parent_locator_entry->value_data );

		parent_locator_entry->value_data = NULL;
	}
	return( -1 );
}

/* Compares an UTF-8 string with the parent locator entry key
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libvhdi_parent_locator_compare_key_with_utf8_string(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_compare_key_with_utf8_string";
	int result            = 0;

	if( parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator entry.",
		 function );

		return( -1 );
	}
	result = libuna_utf8_string_compare_with_utf16_stream(
	          utf8_string,
	          utf8_string_length,
	          parent_locator_entry->key_data,
	          parent_locator_entry->key_data_size,
	          LIBUNA_ENDIAN_LITTLE,
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
	return( result );
}

/* Retrieves the parent locator entry value as a big-endian GUID
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_get_value_as_guid(
     libvhdi_parent_locator_entry_t *parent_locator_entry,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	uint8_t guid_string[ 48 ];

	libfguid_identifier_t *identifier = NULL;
	static char *function             = "libvhdi_parent_locator_get_value_as_guid";

	if( parent_locator_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing parent locator entry.",
		 function );

		goto on_error;
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     guid_string,
	     48,
	     parent_locator_entry->value_data,
	     parent_locator_entry->value_data_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-8 string.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_initialize(
	     &identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create identifier.",
		 function );

		goto on_error;
	}
/* TODO add libfguid_identifier_copy_from_utf16_stream ? */
	if( libfguid_identifier_copy_from_utf8_string(
	     identifier,
	     guid_string,
	     38,
	     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-8 string to identifier.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_to_byte_stream(
	     identifier,
	     guid_data,
	     guid_data_size,
	     LIBFGUID_ENDIAN_BIG,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier to GUID data.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_free(
	     &identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free identifier.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( identifier != NULL )
	{
		libfguid_identifier_free(
		 &identifier,
		 NULL );
	}
	return( 1 );
}

