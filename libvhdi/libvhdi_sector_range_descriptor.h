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

#if !defined( _LIBVHDI_SECTOR_RANGE_DESCRIPTOR_H )
#define _LIBVHDI_SECTOR_RANGE_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_sector_range_descriptor libvhdi_sector_range_descriptor_t;

struct libvhdi_sector_range_descriptor
{
	/* The start offset
	 */
	off64_t start_offset;

	/* The end offset
	 */
	off64_t end_offset;

	/* The flags
	 */
	uint32_t flags;
};

int libvhdi_sector_range_descriptor_initialize(
     libvhdi_sector_range_descriptor_t **sector_range_descriptor,
     libcerror_error_t **error );

int libvhdi_sector_range_descriptor_free(
     libvhdi_sector_range_descriptor_t **sector_range_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_SECTOR_RANGE_DESCRIPTOR_H ) */

