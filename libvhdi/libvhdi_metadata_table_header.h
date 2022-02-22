/*
 * Metadata table header functions
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

#if !defined( _LIBVHDI_METADATA_TABLE_HEADER_H )
#define _LIBVHDI_METADATA_TABLE_HEADER_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_metadata_table_header libvhdi_metadata_table_header_t;

struct libvhdi_metadata_table_header
{
	/* The number of entries
	 */
	uint16_t number_of_entries;
};

int libvhdi_metadata_table_header_initialize(
     libvhdi_metadata_table_header_t **metadata_table_header,
     libcerror_error_t **error );

int libvhdi_metadata_table_header_free(
     libvhdi_metadata_table_header_t **metadata_table_header,
     libcerror_error_t **error );

int libvhdi_metadata_table_header_read_data(
     libvhdi_metadata_table_header_t *metadata_table_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_METADATA_TABLE_HEADER_H ) */

