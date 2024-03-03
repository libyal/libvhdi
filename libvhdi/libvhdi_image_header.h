/*
 * Image header functions
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

#if !defined( _LIBVHDI_IMAGE_HEADER_H )
#define _LIBVHDI_IMAGE_HEADER_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_image_header libvhdi_image_header_t;

struct libvhdi_image_header
{
	/* The checksum
	 */
	uint32_t checksum;

	/* The sequence number
	 */
	uint64_t sequence_number;

	/* The format version
	 */
	uint16_t format_version;

	/* The data write identifier
	 */
	uint8_t data_write_identifier[ 16 ];
};

int libvhdi_image_header_initialize(
     libvhdi_image_header_t **image_header,
     libcerror_error_t **error );

int libvhdi_image_header_free(
     libvhdi_image_header_t **image_header,
     libcerror_error_t **error );

int libvhdi_image_header_read_data(
     libvhdi_image_header_t *image_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_image_header_read_file_io_handle(
     libvhdi_image_header_t *image_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvhdi_image_header_get_format_version(
     libvhdi_image_header_t *image_header,
     uint16_t *major_version,
     libcerror_error_t **error );

int libvhdi_image_header_get_data_write_identifier(
     libvhdi_image_header_t *image_header,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_IMAGE_HEADER_H ) */

