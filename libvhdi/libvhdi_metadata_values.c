/*
 * Metadata values functions
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
#include "libvhdi_definitions.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_libfguid.h"
#include "libvhdi_libuna.h"
#include "libvhdi_metadata_item_identifier.h"
#include "libvhdi_metadata_table.h"
#include "libvhdi_metadata_table_entry.h"
#include "libvhdi_metadata_values.h"
#include "libvhdi_parent_locator.h"

/* Creates metadata values
 * Make sure the value metadata_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_initialize(
     libvhdi_metadata_values_t **metadata_values,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_initialize";

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
	if( *metadata_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata values value already set.",
		 function );

		return( -1 );
	}
	*metadata_values = memory_allocate_structure(
	                   libvhdi_metadata_values_t );

	if( *metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create metadata values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *metadata_values,
	     0,
	     sizeof( libvhdi_metadata_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear metadata values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *metadata_values != NULL )
	{
		memory_free(
		 *metadata_values );

		*metadata_values = NULL;
	}
	return( -1 );
}

/* Frees metadata values
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_free(
     libvhdi_metadata_values_t **metadata_values,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_free";

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
	if( *metadata_values != NULL )
	{
		if( ( *metadata_values )->parent_filename != NULL )
		{
			memory_free(
			 ( *metadata_values )->parent_filename );
		}
		memory_free(
		 *metadata_values );

		*metadata_values = NULL;
	}
	return( 1 );
}

/* Reads a parent locator metadata item
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_read_parent_locator_item_data(
     libvhdi_metadata_values_t *metadata_values,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libvhdi_parent_locator_t *parent_locator             = NULL;
	libvhdi_parent_locator_entry_t *parent_locator_entry = NULL;
	static char *function                                = "libvhdi_metadata_values_read_parent_locator_item_data";
	int result                                           = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
	if( metadata_values->parent_filename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata values - parent filename value already set.",
		 function );

		return( -1 );
	}
	if( libvhdi_parent_locator_initialize(
	     &parent_locator,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create parent locator.",
		 function );

		goto on_error;
	}
	if( libvhdi_parent_locator_read_data(
	     parent_locator,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read parent locator.",
		 function );

		goto on_error;
	}
	result = libvhdi_parent_locator_get_entry_by_utf8_key(
	          parent_locator,
	          (uint8_t *) "parent_linkage",
	          14,
	          &parent_locator_entry,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve parent linkage entry.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libvhdi_parent_locator_get_value_as_guid(
		     parent_locator_entry,
		     metadata_values->parent_identifier,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve parent linkage value as big-endian GUID.",
			 function );

			goto on_error;
		}
	}
	result = libvhdi_parent_locator_get_entry_by_utf8_key(
	          parent_locator,
	          (uint8_t *) "absolute_win32_path",
	          19,
	          &parent_locator_entry,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve absolute WIN32 path entry.",
		 function );

		goto on_error;
	}
	if( result == 0 )
	{
		result = libvhdi_parent_locator_get_entry_by_utf8_key(
		          parent_locator,
		          (uint8_t *) "volume_path",
		          11,
		          &parent_locator_entry,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve volume path entry.",
			 function );

			goto on_error;
		}
	}
	if( result == 0 )
	{
		result = libvhdi_parent_locator_get_entry_by_utf8_key(
		          parent_locator,
		          (uint8_t *) "relative_path",
		          12,
		          &parent_locator_entry,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve volume path entry.",
			 function );

			goto on_error;
		}
	}
	if( result != 0 )
	{
		if( parent_locator_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing path entry.",
			 function );

			goto on_error;
		}
		metadata_values->parent_filename      = parent_locator_entry->value_data;
		metadata_values->parent_filename_size = parent_locator_entry->value_data_size;

		parent_locator_entry->value_data      = NULL;
		parent_locator_entry->value_data_size = 0;
	}
	if( libvhdi_parent_locator_free(
	     &parent_locator,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free parent locator.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( parent_locator != NULL )
	{
		libvhdi_parent_locator_free(
		 &parent_locator,
		 NULL );
	}
	if( metadata_values->parent_filename != NULL )
	{
		memory_free(
		 metadata_values->parent_filename );

		metadata_values->parent_filename = NULL;
	}
	metadata_values->parent_filename_size = 0;

	return( -1 );
}

/* Reads a metadata item
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_read_item_data(
     libvhdi_metadata_values_t *metadata_values,
     libvhdi_metadata_table_entry_t *metadata_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function          = "libvhdi_metadata_values_read_item_data";
	uint32_t file_parameters_flags = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
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
	if( ( data_size == 0 )
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
		if( libvhdi_debug_print_guid_value(
		     function,
		     "metadata item identifier\t",
		     metadata_table_entry->item_identifier,
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

			goto on_error;
		}
		libcnotify_printf(
		 "%s: metadata item description\t: %s\n",
		 function,
		 libvhdi_metadata_item_identifier_get_description(
		  metadata_table_entry->item_identifier ) );

		libcnotify_printf(
		 "%s: metadata item data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 (size_t) metadata_table_entry->item_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( memory_compare(
	     metadata_table_entry->item_identifier,
	     libvhdi_metadata_item_identifier_file_parameters,
	     16 ) == 0 )
	{
		if( metadata_table_entry->item_size != 8 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported file parameters size item data size.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 data,
		 metadata_values->block_size );

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ 4 ] ),
		 file_parameters_flags );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block size\t\t\t: %" PRIu32 "\n",
			 function,
			 metadata_values->block_size );

			libcnotify_printf(
			 "%s: flags\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 file_parameters_flags );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( ( metadata_values->block_size < ( 1024 * 1024 ) )
		 || ( metadata_values->block_size > ( 256 * 1024 * 1024 ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid block size value out of bounds.",
			 function );

			goto on_error;
		}
/* TODO check if block size is power of 2 */
		if( ( metadata_values->block_size % 512 ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported block size: %" PRIu32 ".",
			 function,
			 metadata_values->block_size );

			goto on_error;
		}
		file_parameters_flags &= 0x00000003UL;

		switch( file_parameters_flags )
		{
			case 0:
				metadata_values->disk_type = LIBVHDI_DISK_TYPE_DYNAMIC;
				break;

			case 1:
				metadata_values->disk_type = LIBVHDI_DISK_TYPE_FIXED;
				break;

			case 2:
				metadata_values->disk_type = LIBVHDI_DISK_TYPE_DIFFERENTIAL;
				break;

			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported file parameters flags: 0x%02" PRIx32 ".",
				 function,
				 file_parameters_flags );

				goto on_error;
		}
	}
	else if( memory_compare(
	          metadata_table_entry->item_identifier,
	          libvhdi_metadata_item_identifier_logical_sector_size,
	          16 ) == 0 )
	{
		if( metadata_table_entry->item_size != 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported logical sector size item data size.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 data,
		 metadata_values->logical_sector_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: logical sector size\t\t: %" PRIu32 "\n",
			 function,
			 metadata_values->logical_sector_size );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( ( metadata_values->logical_sector_size != 512 )
		 && ( metadata_values->logical_sector_size != 4096 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid logical sector size value out of bounds.",
			 function );

			goto on_error;
		}
	}
	else if( memory_compare(
	          metadata_table_entry->item_identifier,
	          libvhdi_metadata_item_identifier_parent_locator,
	          16 ) == 0 )
	{
		if( libvhdi_metadata_values_read_parent_locator_item_data(
		     metadata_values,
		     data,
		     (size_t) metadata_table_entry->item_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read parent locator metadata item.",
			 function );

			goto on_error;
		}
	}
	else if( memory_compare(
	          metadata_table_entry->item_identifier,
	          libvhdi_metadata_item_identifier_physical_sector_size,
	          16 ) == 0 )
	{
		if( metadata_table_entry->item_size != 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported physical sector size item data size.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 data,
		 metadata_values->physical_sector_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: physical sector size\t\t: %" PRIu32 "\n",
			 function,
			 metadata_values->physical_sector_size );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( ( metadata_values->physical_sector_size != 512 )
		 && ( metadata_values->physical_sector_size != 4096 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid physical sector size value out of bounds.",
			 function );

			goto on_error;
		}
	}
	else if( memory_compare(
	          metadata_table_entry->item_identifier,
	          libvhdi_metadata_item_identifier_virtual_disk_identifier,
	          16 ) == 0 )
	{
		if( metadata_table_entry->item_size != 16 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported virtual disk identifier item data size.",
			 function );

			goto on_error;
		}
		metadata_values->virtual_disk_identifier[ 0 ] = data[ 3 ];
		metadata_values->virtual_disk_identifier[ 1 ] = data[ 2 ];
		metadata_values->virtual_disk_identifier[ 2 ] = data[ 1 ];
		metadata_values->virtual_disk_identifier[ 3 ] = data[ 0 ];

		metadata_values->virtual_disk_identifier[ 4 ] = data[ 5 ];
		metadata_values->virtual_disk_identifier[ 5 ] = data[ 4 ];

		metadata_values->virtual_disk_identifier[ 6 ] = data[ 7 ];
		metadata_values->virtual_disk_identifier[ 7 ] = data[ 6 ];

		if( memory_copy(
		     &( metadata_values->virtual_disk_identifier[ 8 ] ),
		     &( data[ 8 ] ),
		     8 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy virtual disk identifier.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libvhdi_debug_print_guid_value(
			     function,
			     "virtual disk identifier\t\t",
			     metadata_values->virtual_disk_identifier,
			     16,
			     LIBFGUID_ENDIAN_BIG,
			     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print GUID value.",
				 function );

				goto on_error;
			}
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	else if( memory_compare(
	          metadata_table_entry->item_identifier,
	          libvhdi_metadata_item_identifier_virtual_disk_size,
	          16 ) == 0 )
	{
		if( metadata_table_entry->item_size != 8 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported virtual disk size item data size.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint64_little_endian(
		 data,
		 metadata_values->virtual_disk_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: virtual disk size\t\t: %" PRIu64 "\n",
			 function,
			 metadata_values->virtual_disk_size );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

on_error:
	if( metadata_values->parent_filename != NULL )
	{
		memory_free(
		 metadata_values->parent_filename );

		metadata_values->parent_filename = NULL;
	}
	metadata_values->parent_filename_size = 0;

	return( -1 );
}

/* Reads a metadata item
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_read_item_file_io_handle(
     libvhdi_metadata_values_t *metadata_values,
     libvhdi_metadata_table_entry_t *metadata_table_entry,
     libbfio_handle_t *file_io_handle,
     off64_t metadata_region_offset,
     libcerror_error_t **error )
{
	uint8_t *data                = NULL;
	static char *function        = "libvhdi_metadata_values_read_item_file_io_handle";
	ssize_t read_count           = 0;
	off64_t metadata_item_offset = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
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
	metadata_item_offset = metadata_region_offset + metadata_table_entry->item_offset;

	if( ( metadata_table_entry->item_size == 0 )
	 || ( metadata_table_entry->item_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid metadate table entry - item data size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading metadata item at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 metadata_item_offset,
		 metadata_item_offset );
	}
#endif
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * metadata_table_entry->item_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create metadata item data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              (size_t) metadata_table_entry->item_size,
	              metadata_item_offset,
	              error );

	if( read_count != (ssize_t) (size_t) metadata_table_entry->item_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata item data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 metadata_item_offset,
		 metadata_item_offset );

		goto on_error;
	}
	if( libvhdi_metadata_values_read_item_data(
	     metadata_values,
	     metadata_table_entry,
	     data,
	     (size_t) metadata_table_entry->item_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata item.",
		 function );

		goto on_error;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

/* Reads the metadata values
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_read_file_io_handle(
     libvhdi_metadata_values_t *metadata_values,
     libbfio_handle_t *file_io_handle,
     off64_t metadata_region_offset,
     libcerror_error_t **error )
{
	libvhdi_metadata_table_t *metadata_table = NULL;
	libvhdi_metadata_table_entry_t *entry    = NULL;
	static char *function                    = "libvhdi_metadata_values_read_file_io_handle";
	int entry_index                          = 0;
	int number_of_entries                    = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
	if( libvhdi_metadata_table_initialize(
	     &metadata_table,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create metadata table.",
		 function );

		goto on_error;
	}
	if( libvhdi_metadata_table_read_file_io_handle(
	     metadata_table,
	     file_io_handle,
	     metadata_region_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata table.",
		 function );

		goto on_error;
	}
	if( libvhdi_metadata_table_get_number_of_entries(
	     metadata_table,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from metadata table.",
		 function );

		goto on_error;
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libvhdi_metadata_table_get_entry_by_index(
		     metadata_table,
		     entry_index,
		     &entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from metadata table.",
			 function,
			 entry_index );

			goto on_error;
		}
		if( entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing entry: %d.",
			 function,
			 entry_index );

			goto on_error;
		}
		if( libvhdi_metadata_values_read_item_file_io_handle(
		     metadata_values,
		     entry,
		     file_io_handle,
		     metadata_region_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read metadata item: %d.",
			 function,
			 entry_index );

			goto on_error;
		}
	}
	if( libvhdi_metadata_table_free(
	     &metadata_table,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free metadata table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( metadata_table != NULL )
	{
		libvhdi_metadata_table_free(
		 &metadata_table,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the virtual disk identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_get_virtual_disk_identifier(
     libvhdi_metadata_values_t *metadata_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_get_virtual_disk_identifier";

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     metadata_values->virtual_disk_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy virtual disk identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the parent identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libvhdi_metadata_values_get_parent_identifier(
     libvhdi_metadata_values_t *metadata_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_get_parent_identifier";

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata values.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     metadata_values->parent_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy parent identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_metadata_values_get_utf8_parent_filename_size(
     libvhdi_metadata_values_t *metadata_values,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_get_utf8_parent_filename_size";
	int result            = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( metadata_values->parent_filename != NULL )
	 && ( metadata_values->parent_filename_size > 0 ) )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
		          metadata_values->parent_filename,
		          metadata_values->parent_filename_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf8_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-8 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_metadata_values_get_utf8_parent_filename(
     libvhdi_metadata_values_t *metadata_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_get_utf8_parent_filename";
	int result            = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( metadata_values->parent_filename != NULL )
	 && ( metadata_values->parent_filename_size > 0 ) )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
		          utf8_string,
		          utf8_string_size,
		          metadata_values->parent_filename,
		          metadata_values->parent_filename_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy parent filename to UTF-8 string.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the size of the UTF-16 encoded parent filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_metadata_values_get_utf16_parent_filename_size(
     libvhdi_metadata_values_t *metadata_values,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_get_utf16_parent_filename_size";
	int result            = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( metadata_values->parent_filename != NULL )
	 && ( metadata_values->parent_filename_size > 0 ) )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
		          metadata_values->parent_filename,
		          metadata_values->parent_filename_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf16_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-16 encoded parent filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvhdi_metadata_values_get_utf16_parent_filename(
     libvhdi_metadata_values_t *metadata_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_metadata_values_get_utf16_parent_filename";
	int result            = 0;

	if( metadata_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid dynamic disk header.",
		 function );

		return( -1 );
	}
	if( ( metadata_values->parent_filename != NULL )
	 && ( metadata_values->parent_filename_size > 0 ) )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
		          utf16_string,
		          utf16_string_size,
		          metadata_values->parent_filename,
		          metadata_values->parent_filename_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy parent filename to UTF-16 string.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

