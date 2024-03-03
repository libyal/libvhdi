/*
 * Dynamic disk header functions
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

#if !defined( _LIBVHDI_DYNAMIC_DISK_HEADER_H )
#define _LIBVHDI_DYNAMIC_DISK_HEADER_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_dynamic_disk_header libvhdi_dynamic_disk_header_t;

struct libvhdi_dynamic_disk_header
{
	/* The format version
	 */
	uint32_t format_version;

	/* The block table offset
 	 */
	off64_t block_table_offset;

	/* The next offset
 	 */
	off64_t next_offset;

	/* The block size
	 */
	uint32_t block_size;

	/* The number of blocks
	 */
	uint32_t number_of_blocks;

	/* The parent identifier
	 */
	uint8_t parent_identifier[ 16 ];

	/* The parent filename
	 */
	uint8_t *parent_filename;

	/* The parent filename size
	 */
	size_t parent_filename_size;
};

int libvhdi_dynamic_disk_header_initialize(
     libvhdi_dynamic_disk_header_t **dynamic_disk_header,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_free(
     libvhdi_dynamic_disk_header_t **dynamic_disk_header,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_read_data(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_read_file_io_handle(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_get_parent_identifier(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_get_utf8_parent_filename_size(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_get_utf8_parent_filename(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_get_utf16_parent_filename_size(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libvhdi_dynamic_disk_header_get_utf16_parent_filename(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_DYNAMIC_DISK_HEADER_H ) */

