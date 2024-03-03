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

#if !defined( _LIBVHDI_METADATA_VALUES_H )
#define _LIBVHDI_METADATA_VALUES_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_metadata_table_entry.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_metadata_values libvhdi_metadata_values_t;

struct libvhdi_metadata_values
{
	/* The block size
	 */
	uint32_t block_size;

	/* The disk type
	 */
	uint32_t disk_type;

	/* The logical sector size
	 */
	uint32_t logical_sector_size;

	/* The parent identifier
	 */
	uint8_t parent_identifier[ 16 ];

	/* The parent filename
	 */
	uint8_t *parent_filename;

	/* The parent filename size
	 */
	size_t parent_filename_size;

	/* The physical sector size
	 */
	uint32_t physical_sector_size;

	/* The virtual disk identifier
	 */
	uint8_t virtual_disk_identifier[ 16 ];

	/* The virtual disk size
	 */
	uint64_t virtual_disk_size;
};

int libvhdi_metadata_values_initialize(
     libvhdi_metadata_values_t **metadata_values,
     libcerror_error_t **error );

int libvhdi_metadata_values_free(
     libvhdi_metadata_values_t **metadata_values,
     libcerror_error_t **error );

int libvhdi_metadata_values_read_parent_locator_item_data(
     libvhdi_metadata_values_t *metadata_values,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_read_item_data(
     libvhdi_metadata_values_t *metadata_values,
     libvhdi_metadata_table_entry_t *metadata_table_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_read_item_file_io_handle(
     libvhdi_metadata_values_t *metadata_values,
     libvhdi_metadata_table_entry_t *metadata_table_entry,
     libbfio_handle_t *file_io_handle,
     off64_t metadata_region_offset,
     libcerror_error_t **error );

int libvhdi_metadata_values_read_file_io_handle(
     libvhdi_metadata_values_t *metadata_values,
     libbfio_handle_t *file_io_handle,
     off64_t metadata_region_offset,
     libcerror_error_t **error );

int libvhdi_metadata_values_get_virtual_disk_identifier(
     libvhdi_metadata_values_t *metadata_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_get_parent_identifier(
     libvhdi_metadata_values_t *metadata_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_get_utf8_parent_filename_size(
     libvhdi_metadata_values_t *metadata_values,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_get_utf8_parent_filename(
     libvhdi_metadata_values_t *metadata_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_get_utf16_parent_filename_size(
     libvhdi_metadata_values_t *metadata_values,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libvhdi_metadata_values_get_utf16_parent_filename(
     libvhdi_metadata_values_t *metadata_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_METADATA_VALUES_H ) */

