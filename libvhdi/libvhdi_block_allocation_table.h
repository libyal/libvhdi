/*
 * Block allocation table functions
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

#if !defined( _LIBVHDI_BLOCK_ALLOCATION_TABLE_H )
#define _LIBVHDI_BLOCK_ALLOCATION_TABLE_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_block_allocation_table libvhdi_block_allocation_table_t;

struct libvhdi_block_allocation_table
{
	/* The number of entries
	 */
	uint32_t number_of_entries;

	/* The file type
	 */
	int file_type;

	/* The disk type
	 */
	uint32_t disk_type;

	/* The file offset
	 */
	off64_t file_offset;

	/* The block size
	 */
	uint32_t block_size;

	/* The table entry size
	 */
	size_t table_entry_size;

	/* The sector bitmap size
	 */
	uint32_t sector_bitmap_size;

	/* The number of bytes per sector
	 */
	uint32_t bytes_per_sector;

	/* The number of entries per chunk
	 */
	uint32_t entries_per_chunk;
};

int libvhdi_block_allocation_table_initialize(
     libvhdi_block_allocation_table_t **block_allocation_table,
     uint32_t number_of_entries,
     libcerror_error_t **error );

int libvhdi_block_allocation_table_free(
     libvhdi_block_allocation_table_t **block_allocation_table,
     libcerror_error_t **error );

int libvhdi_block_allocation_table_read_file_io_handle(
     libvhdi_block_allocation_table_t *block_allocation_table,
     libbfio_handle_t *file_io_handle,
     int file_type,
     uint32_t disk_type,
     off64_t file_offset,
     uint32_t block_size,
     uint32_t bytes_per_sector,
     libcerror_error_t **error );

int libvhdi_block_allocation_table_read_element_data(
     libvhdi_block_allocation_table_t *block_allocation_table,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_BLOCK_ALLOCATION_TABLE_H ) */

