/*
 * Region table header functions
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

#include "libvhdi_libcerror.h"
#include "libvhdi_libcnotify.h"
#include "libvhdi_region_table_header.h"

#include "vhdi_region_table.h"

/* Creates region table header
 * Make sure the value region_table_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_header_initialize(
     libvhdi_region_table_header_t **region_table_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_header_initialize";

	if( region_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table header.",
		 function );

		return( -1 );
	}
	if( *region_table_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid region table header value already set.",
		 function );

		return( -1 );
	}
	*region_table_header = memory_allocate_structure(
	                        libvhdi_region_table_header_t );

	if( *region_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create region table header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *region_table_header,
	     0,
	     sizeof( libvhdi_region_table_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear region table header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *region_table_header != NULL )
	{
		memory_free(
		 *region_table_header );

		*region_table_header = NULL;
	}
	return( -1 );
}

/* Frees region table header
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_header_free(
     libvhdi_region_table_header_t **region_table_header,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_header_free";

	if( region_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table header.",
		 function );

		return( -1 );
	}
	if( *region_table_header != NULL )
	{
		memory_free(
		 *region_table_header );

		*region_table_header = NULL;
	}
	return( 1 );
}

/* Reads the region table header data
 * Returns 1 if successful or -1 on error
 */
int libvhdi_region_table_header_read_data(
     libvhdi_region_table_header_t *region_table_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_region_table_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( region_table_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid region table header.",
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
	if( ( data_size < sizeof( vhdi_region_table_header_t ) )
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
		 "%s: region table header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vhdi_region_table_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vhdi_region_table_header_t *) data )->signature,
	     "regi",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_region_table_header_t *) data )->checksum,
	 region_table_header->checksum );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vhdi_region_table_header_t *) data )->number_of_entries,
	 region_table_header->number_of_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c\n",
		 function,
		 ( (vhdi_region_table_header_t *) data )->signature[ 0 ],
		 ( (vhdi_region_table_header_t *) data )->signature[ 1 ],
		 ( (vhdi_region_table_header_t *) data )->signature[ 2 ],
		 ( (vhdi_region_table_header_t *) data )->signature[ 3 ] );

		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 region_table_header->checksum );

		libcnotify_printf(
		 "%s: number of entries\t\t: %" PRIu32 "\n",
		 function,
		 region_table_header->number_of_entries );

		byte_stream_copy_to_uint32_little_endian(
		 ( (vhdi_region_table_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( region_table_header->number_of_entries > 2047 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of entries: %" PRIu16 ".",
		 function,
		 region_table_header->number_of_entries );

		return( -1 );
	}
	return( 1 );
}

