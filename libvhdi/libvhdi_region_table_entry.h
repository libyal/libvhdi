/*
 * Region table entry functions
 *
 * Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVHDI_REGION_TABLE_ENTRY_H )
#define _LIBVHDI_REGION_TABLE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_region_table_entry libvhdi_region_table_entry_t;

struct libvhdi_region_table_entry
{
	/* The type identifier
	 */
	uint8_t type_identifier[ 16 ];

	/* The data offset
	 */
	uint64_t data_offset;

	/* The data size
	 */
	uint32_t data_size;

	/* The is required flag
	 */
	uint32_t is_required_flag;
};

int libvhdi_region_table_entry_initialize(
     libvhdi_region_table_entry_t **region_table_entry,
     libcerror_error_t **error );

int libvhdi_region_table_entry_free(
     libvhdi_region_table_entry_t **region_table_entry,
     libcerror_error_t **error );

int libvhdi_region_table_entry_read_data(
     libvhdi_region_table_entry_t *region_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_REGION_TABLE_ENTRY_H ) */

