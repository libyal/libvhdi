/*
 * Block descriptor functions
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

#if !defined( _LIBVHDI_BLOCK_DESCRIPTOR_H )
#define _LIBVHDI_BLOCK_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_sector_range_descriptor.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_block_descriptor libvhdi_block_descriptor_t;

struct libvhdi_block_descriptor
{
	/* The file offset
	 */
	off64_t file_offset;

	/* The block state
	 */
	uint8_t block_state;

	/* The sector ranges array
	 */
	libcdata_array_t *sector_ranges_array;
};

int libvhdi_block_descriptor_initialize(
     libvhdi_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libvhdi_block_descriptor_free(
     libvhdi_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libvhdi_block_descriptor_read_table_entry_data(
     libvhdi_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     int file_type,
     uint32_t sector_bitmap_size,
     libcerror_error_t **error );

int libvhdi_block_descriptor_read_table_entry_file_io_handle(
     libvhdi_block_descriptor_t *block_descriptor,
     libbfio_handle_t *file_io_handle,
     int file_type,
     off64_t file_offset,
     uint32_t sector_bitmap_size,
     libcerror_error_t **error );

int libvhdi_block_descriptor_read_sector_bitmap_data(
     libvhdi_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     int file_type,
     uint32_t byte_per_sector,
     libcerror_error_t **error );

int libvhdi_block_descriptor_read_sector_bitmap_file_io_handle(
     libvhdi_block_descriptor_t *block_descriptor,
     libbfio_handle_t *file_io_handle,
     int file_type,
     off64_t file_offset,
     uint32_t block_size,
     uint32_t sector_bitmap_size,
     uint32_t byte_per_sector,
     libcerror_error_t **error );

int libvhdi_block_descriptor_get_sector_range_descriptor_at_offset(
     libvhdi_block_descriptor_t *block_descriptor,
     off64_t offset,
     libvhdi_sector_range_descriptor_t **sector_range_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_BLOCK_DESCRIPTOR_H ) */

