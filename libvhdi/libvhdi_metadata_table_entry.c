/*
 * Metadata table entry functions
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
#include "libvhdi_metadata_item_identifier.h"
#include "libvhdi_metadata_table_entry.h"

#include "vhdi_metadata_table.h"

/* Creates metadata table entry
 * Make sure the value metadata_table_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_entry_initialize(
     libvhdi_metadata_table_entry_t **metadata_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_entry_initialize";

	if( metadata_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table entry.",
		 function );

		return( -1 );
	}
	if( *metadata_table_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata table entry value already set.",
		 function );

		return( -1 );
	}
	*metadata_table_entry = memory_allocate_structure(
	                         libvhdi_metadata_table_entry_t );

	if( *metadata_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create metadata table entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *metadata_table_entry,
	     0,
	     sizeof( libvhdi_metadata_table_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear metadata table entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *metadata_table_entry != NULL )
	{
		memory_free(
		 *metadata_table_entry );

		*metadata_table_entry = NULL;
	}
	return( -1 );
}

/* Frees metadata table entry
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_entry_free(
     libvhdi_metadata_table_entry_t **metadata_table_entry,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_entry_free";

	if( metadata_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table entry.",
		 function );

		return( -1 );
	}
	if( *metadata_table_entry != NULL )
	{
		memory_free(
		 *metadata_table_entry );

		*metadata_table_entry = NULL;
	}
	return( 1 );
}

/* Reads the metadata table entry data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_table_entry_read_data(
     libvhdi_metadata_table_entry_t *metadata_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_table_entry_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit  = 0;
#endif

	if( metadata_table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata table entry.",
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
	if( ( data_size < sizeof( vhdi_metadata_table_entry_t ) )
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
		 "%s: metadata table entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_metadata_table_entry_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_copy(
	     metadata_table_entry->item_identifier,
	     ( (vhdi_metadata_table_entry_t *) data )->item_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy item identifier.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_metadata_table_entry_t *) data )->item_offset,
	 metadata_table_entry->item_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_metadata_table_entry_t *) data )->item_size,
	 metadata_table_entry->item_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libvhdi_debug_print_guid_value(
		     function,
		     "item identifier\t\t\t",
		     ( (vhdi_metadata_table_entry_t *) data )->item_identifier,
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
		 "%s: item description\t\t: %s\n",
		 function,
		 libvhdi_metadata_item_identifier_get_description(
		  ( (vhdi_metadata_table_entry_t *) data )->item_identifier ) );

		libcnotify_printf(
		 "%s: item offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 metadata_table_entry->item_offset );

		libcnotify_printf(
		 "%s: item size\t\t\t: %" PRIu32 "\n",
		 function,
		 metadata_table_entry->item_size );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vhdi_metadata_table_entry_t *) data )->unknown1,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( ( value_64bit & 0x00000001UL ) != 0 )
		{
			libcnotify_printf(
			 "\t(IsUser)\n" );
		}
		if( ( value_64bit & 0x00000002UL ) != 0 )
		{
			libcnotify_printf(
			 "\t(IsVirtualDisk)\n" );
		}
		if( ( value_64bit & 0x00000004UL ) != 0 )
		{
			libcnotify_printf(
			 "\t(IsRequired)\n" );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( metadata_table_entry->item_offset < ( 64 * 1024 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid item offset value out of bounds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

