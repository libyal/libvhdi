/*
 * Parent locator header functions
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
#include "libvhdi_parent_locator_header.h"

#include "vhdi_parent_locator.h"

/* Creates parent locator header
 * Make sure the value parent_locator_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_header_initialize(
     libvhdi_parent_locator_header_t **parent_locator_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_header_initialize";

	if( parent_locator_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator header.",
		 function );

		return( -1 );
	}
	if( *parent_locator_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid parent locator header value already set.",
		 function );

		return( -1 );
	}
	*parent_locator_header = memory_allocate_structure(
	                          libvhdi_parent_locator_header_t );

	if( *parent_locator_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create parent locator header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *parent_locator_header,
	     0,
	     sizeof( libvhdi_parent_locator_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear parent locator header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *parent_locator_header != NULL )
	{
		memory_free(
		 *parent_locator_header );

		*parent_locator_header = NULL;
	}
	return( -1 );
}

/* Frees parent locator header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_header_free(
     libvhdi_parent_locator_header_t **parent_locator_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_parent_locator_header_free";

	if( parent_locator_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator header.",
		 function );

		return( -1 );
	}
	if( *parent_locator_header != NULL )
	{
		memory_free(
		 *parent_locator_header );

		*parent_locator_header = NULL;
	}
	return( 1 );
}

/* Reads the parent locator header data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_parent_locator_header_read_data(
     libvhdi_parent_locator_header_t *parent_locator_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	uint8_t parent_locator_type_indicator[ 16 ] = {
		0xb7, 0xef, 0x4a, 0xb0, 0x9e, 0xd1, 0x81, 0x4a, 0xb7, 0x89, 0x25, 0xb8, 0xe9, 0x44, 0x59, 0x13 };

	static char *function = "libvhdi_parent_locator_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint16_t value_16bit  = 0;
#endif

	if( parent_locator_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent locator header.",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: parent locator header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_parent_locator_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_parent_locator_header_t *) data )->type_identifier,
	     parent_locator_type_indicator,
	     16 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type indicator.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 ( (vhdi_parent_locator_header_t *) data )->number_of_entries,
	 parent_locator_header->number_of_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libvhdi_debug_print_guid_value(
		     function,
		     "type identifier\t\t",
		     ( (vhdi_parent_locator_header_t *) data )->type_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 ( (vhdi_parent_locator_header_t *) data )->unknown1,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of entries\t\t: %" PRIu16 "\n",
		 function,
		 parent_locator_header->number_of_entries );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

