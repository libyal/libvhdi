/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBVHDI_IO_HANDLE_H )
#define _LIBVHDI_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_io_handle libvhdi_io_handle_t;

struct libvhdi_io_handle
{
	/* The file type
 	 */
	int file_type;

	/* The disk type
	 */
	uint32_t disk_type;

	/* The (storage) media size
	 */
	size64_t media_size;

	/* The (logical) number of bytes per sector
	 */
	uint32_t bytes_per_sector;

	/* The block size
	 */
	uint32_t block_size;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libvhdi_io_handle_initialize(
     libvhdi_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvhdi_io_handle_free(
     libvhdi_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvhdi_io_handle_clear(
     libvhdi_io_handle_t *io_handle,
     libcerror_error_t **error );

int libvhdi_io_handle_get_disk_type(
     libvhdi_io_handle_t *io_handle,
     uint32_t *disk_type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_IO_HANDLE_H ) */

