/*
 * Region table entry functions
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
#include "libvhdi_region_table_entry.h"
#include "libvhdi_region_type_identifier.h"

#include "vhdi_region_table.h"

/* Creates region table entry
 * Make sure the value region_table_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_entry_initialize(
     libvhdi_region_table_entry_t **region_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_entry_initialize";

	if( region_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table entry.",
		 function );

		return( -1 );
	}
	if( *region_table_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid region table entry value already set.",
		 function );

		return( -1 );
	}
	*region_table_entry = memory_allocate_structure(
	                       libvhdi_region_table_entry_t );

	if( *region_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create region table entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *region_table_entry,
	     0,
	     sizeof( libvhdi_region_table_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear region table entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *region_table_entry != NULL )
	{
		memory_free(
		 *region_table_entry );

		*region_table_entry = NULL;
	}
	return( -1 );
}

/* Frees region table entry
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_entry_free(
     libvhdi_region_table_entry_t **region_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_entry_free";

	if( region_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table entry.",
		 function );

		return( -1 );
	}
	if( *region_table_entry != NULL )
	{
		memory_free(
		 *region_table_entry );

		*region_table_entry = NULL;
	}
	return( 1 );
}

/* Reads the region table entry data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_entry_read_data(
     libvhdi_region_table_entry_t *region_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_entry_read_data";

	if( region_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table entry.",
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
	if( ( data_size < sizeof( vhdi_region_table_entry_t ) )
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
		 "%s: region table entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_region_table_entry_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_copy(
	     region_table_entry->type_identifier,
	     ( (vhdi_region_table_entry_t *) data )->type_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy type identifier.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 ( (vhdi_region_table_entry_t *) data )->data_offset,
	 region_table_entry->data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_region_table_entry_t *) data )->data_size,
	 region_table_entry->data_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_region_table_entry_t *) data )->is_required_flag,
	 region_table_entry->is_required_flag );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libvhdi_debug_print_guid_value(
		     function,
		     "type identifier\t\t\t",
		     ( (vhdi_region_table_entry_t *) data )->type_identifier,
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
		libcnotify_printf(
		 "%s: type description\t\t\t: %s\n",
		 function,
		 libvhdi_region_type_identifier_get_description(
		  ( (vhdi_region_table_entry_t *) data )->type_identifier ) );

		libcnotify_printf(
		 "%s: data offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 region_table_entry->data_offset );

		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 region_table_entry->data_size );

		libcnotify_printf(
		 "%s: is required flag\t\t\t: %" PRIu32 "\n",
		 function,
		 region_table_entry->is_required_flag );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

