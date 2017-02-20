/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBVHDI_IO_HANDLE_H )
#define _LIBVHDI_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libfcache.h"
#include "libvhdi_libfdata.h"
#include "libvhdi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *vhdi_file_signature;

typedef struct libvhdi_io_handle libvhdi_io_handle_t;

struct libvhdi_io_handle
{
	/* The (storage) media size
	 */
	size64_t media_size;

	/* The format version
	 */
	uint32_t format_version;

	/* The disk type
	 */
	uint32_t disk_type;

	/* The block table offset
 	 */
	off64_t block_table_offset;

	/* The block data offset
 	 */
	off64_t block_data_offset;

	/* The block size
	 */
	uint32_t block_size;

	/* The block bitmap size
	 */
	uint32_t block_bitmap_size;

	/* The number of blocks
	 */
	uint32_t number_of_blocks;

	/* The identifier
	 */
	uint8_t identifier[ 16 ];

	/* The parent identifier
	 */
	uint8_t parent_identifier[ 16 ];

	/* The parent filename
	 */
	uint8_t *parent_filename;

	/* The parent filename size
	 */
	size_t parent_filename_size;

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

int libvhdi_io_handle_read_file_footer(
     libvhdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t *next_offset,
     libcerror_error_t **error );

int libvhdi_io_handle_read_dynamic_disk_header(
     libvhdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     off64_t *next_offset,
     libcerror_error_t **error );

int libvhdi_io_handle_get_identifier(
     libvhdi_io_handle_t *io_handle,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvhdi_io_handle_get_parent_identifier(
     libvhdi_io_handle_t *io_handle,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libvhdi_io_handle_get_utf8_parent_filename_size(
     libvhdi_io_handle_t *io_handle,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libvhdi_io_handle_get_utf8_parent_filename(
     libvhdi_io_handle_t *io_handle,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libvhdi_io_handle_get_utf16_parent_filename_size(
     libvhdi_io_handle_t *io_handle,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libvhdi_io_handle_get_utf16_parent_filename(
     libvhdi_io_handle_t *io_handle,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libvhdi_io_handle_read_data_block(
     libvhdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
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

#endif /* !defined( _LIBVHDI_IO_HANDLE_H ) */

