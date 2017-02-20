/*
 * Block table functions
 *
 * Copyright (C) 2012-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBVHDI_BLOCK_TABLE_H )
#define _LIBVHDI_BLOCK_TABLE_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_block_table libvhdi_block_table_t;

struct libvhdi_block_table
{
	/* The number of references
 	 */
	int number_of_references;

	/* The references
	 */
	uint32_t *references;

	/* The size
	 */
	size_t size;
};

int libvhdi_block_table_initialize(
     libvhdi_block_table_t **block_table,
     libcerror_error_t **error );

int libvhdi_block_table_free(
     libvhdi_block_table_t **block_table,
     libcerror_error_t **error );

int libvhdi_block_table_get_number_of_references(
     libvhdi_block_table_t *block_table,
     int *number_of_references,
     libcerror_error_t **error );

int libvhdi_block_table_get_reference_by_index(
     libvhdi_block_table_t *block_table,
     int reference_index,
     uint32_t *reference,
     libcerror_error_t **error );

int libvhdi_block_table_read(
     libvhdi_block_table_t *block_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint32_t number_of_blocks,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_BLOCK_TABLE_H ) */

