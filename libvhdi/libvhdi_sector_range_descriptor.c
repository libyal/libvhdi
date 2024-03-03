/*
 * Sector range descriptor functions
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

#include "libvhdi_libcerror.h"
#include "libvhdi_sector_range_descriptor.h"

/* Creates a sector range descriptor
 * Make sure the value sector_range_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvhdi_sector_range_descriptor_initialize(
     libvhdi_sector_range_descriptor_t **sector_range_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_sector_range_descriptor_initialize";

	if( sector_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector range descriptor.",
		 function );

		return( -1 );
	}
	if( *sector_range_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sector range descriptor value already set.",
		 function );

		return( -1 );
	}
	*sector_range_descriptor = memory_allocate_structure(
	                            libvhdi_sector_range_descriptor_t );

	if( *sector_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sector range descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *sector_range_descriptor,
	     0,
	     sizeof( libvhdi_sector_range_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear sector range descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *sector_range_descriptor != NULL )
	{
		memory_free(
		 *sector_range_descriptor );

		*sector_range_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a sector range descriptor
 * Returns 1 if successful or -1 on error
 */
int libvhdi_sector_range_descriptor_free(
     libvhdi_sector_range_descriptor_t **sector_range_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvhdi_sector_range_descriptor_free";

	if( sector_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector range descriptor.",
		 function );

		return( -1 );
	}
	if( *sector_range_descriptor != NULL )
	{
		memory_free(
		 *sector_range_descriptor );

		*sector_range_descriptor = NULL;
	}
	return( 1 );
}

