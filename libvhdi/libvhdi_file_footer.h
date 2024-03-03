/*
 * File footer functions
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

#if !defined( _LIBVHDI_FILE_FOOTER_H )
#define _LIBVHDI_FILE_FOOTER_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_file_footer libvhdi_file_footer_t;

struct libvhdi_file_footer
{
	/* The format version
	 */
	uint32_t format_version;

	/* The next offset
	 */
	off64_t next_offset;

	/* The (storage) media size
	 */
	size64_t media_size;

	/* The disk type
	 */
	uint32_t disk_type;

	/* The checksum
	 */
	uint32_t checksum;

	/* The identifier
	 */
	uint8_t identifier[ 16 ];
};

int libvhdi_file_footer_initialize(
     libvhdi_file_footer_t **file_footer,
     libcerror_error_t **error );

int libvhdi_file_footer_free(
     libvhdi_file_footer_t **file_footer,
     libcerror_error_t **error );

int libvhdi_file_footer_read_data(
     libvhdi_file_footer_t *file_footer,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_file_footer_read_file_io_handle(
     libvhdi_file_footer_t *file_footer,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvhdi_file_footer_get_format_version(
     libvhdi_file_footer_t *file_footer,
     uint16_t *major_version,
     uint16_t *minor_version,
     libcerror_error_t **error );

int libvhdi_file_footer_get_identifier(
     libvhdi_file_footer_t *file_footer,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_FILE_FOOTER_H ) */

