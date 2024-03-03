/*
 * File information functions
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

#if !defined( _LIBVHDI_FILE_INFORMATION_H )
#define _LIBVHDI_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_file_information libvhdi_file_information_t;

struct libvhdi_file_information
{
	/* The creator
	 */
	uint8_t creator[ 512 ];
};

int libvhdi_file_information_initialize(
     libvhdi_file_information_t **file_information,
     libcerror_error_t **error );

int libvhdi_file_information_free(
     libvhdi_file_information_t **file_information,
     libcerror_error_t **error );

int libvhdi_file_information_read_data(
     libvhdi_file_information_t *file_information,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_file_information_read_file_io_handle(
     libvhdi_file_information_t *file_information,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_FILE_INFORMATION_H ) */

