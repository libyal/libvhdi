/*
 * Region table functions
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

#if !defined( _LIBVHDI_REGION_TABLE_H )
#define _LIBVHDI_REGION_TABLE_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_region_table_entry.h"
#include "libvhdi_region_table_header.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_region_table libvhdi_region_table_t;

struct libvhdi_region_table
{
	/* The header
	 */
	libvhdi_region_table_header_t *header;

	/* The entries array
	 */
	libcdata_array_t *entries_array;
};

int libvhdi_region_table_initialize(
     libvhdi_region_table_t **region_table,
     libcerror_error_t **error );

int libvhdi_region_table_free(
     libvhdi_region_table_t **region_table,
     libcerror_error_t **error );

int libvhdi_region_table_read_file_io_handle(
     libvhdi_region_table_t *region_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvhdi_region_table_get_entry_by_type_identifier(
     libvhdi_region_table_t *region_table,
     const uint8_t *region_type_identifier,
     libvhdi_region_table_entry_t **entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_REGION_TABLE_H ) */

