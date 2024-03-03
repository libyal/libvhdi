/*
 * File functions
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

#if !defined( _LIBVHDI_INTERNAL_FILE_H )
#define _LIBVHDI_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libvhdi_block_allocation_table.h"
#include "libvhdi_dynamic_disk_header.h"
#include "libvhdi_extern.h"
#include "libvhdi_file_footer.h"
#include "libvhdi_file_information.h"
#include "libvhdi_image_header.h"
#include "libvhdi_io_handle.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcthreads.h"
#include "libvhdi_libfcache.h"
#include "libvhdi_libfdata.h"
#include "libvhdi_metadata_values.h"
#include "libvhdi_region_table.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_internal_file libvhdi_internal_file_t;

struct libvhdi_internal_file
{
	/* The current (storage media) offset
	 */
	off64_t current_offset;

	/* The IO handle
	 */
	libvhdi_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The file footer
	 */
	libvhdi_file_footer_t *file_footer;

	/* The file information
	 */
	libvhdi_file_information_t *file_information;

	/* The dynamic disk header
	 */
	libvhdi_dynamic_disk_header_t *dynamic_disk_header;

	/* The image header
	 */
	libvhdi_image_header_t *image_header;

	/* The region table
	 */
	libvhdi_region_table_t *region_table;

	/* The metadata values
	 */
	libvhdi_metadata_values_t *metadata_values;

	/* The block allocation table
	 */
	libvhdi_block_allocation_table_t *block_allocation_table;

	/* The block descriptors vector
	 */
	libfdata_vector_t *block_descriptors_vector;

	/* The block descriptors cache
	 */
	libfcache_cache_t *block_descriptors_cache;

	/* The parent file
	 */
	libvhdi_file_t *parent_file;

#if defined( HAVE_LIBVHDI_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBVHDI_EXTERN \
int libvhdi_file_initialize(
     libvhdi_file_t **file,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_free(
     libvhdi_file_t **file,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_signal_abort(
     libvhdi_file_t *file,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_open(
     libvhdi_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVHDI_EXTERN \
int libvhdi_file_open_wide(
     libvhdi_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVHDI_EXTERN \
int libvhdi_file_open_file_io_handle(
     libvhdi_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_close(
     libvhdi_file_t *file,
     libcerror_error_t **error );

int libvhdi_internal_file_open_read(
     libvhdi_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvhdi_internal_file_open_read_dynamic_disk_header(
     libvhdi_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvhdi_internal_file_open_read_image_header(
     libvhdi_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvhdi_internal_file_open_read_region_table(
     libvhdi_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvhdi_internal_file_open_read_metadata_values(
     libvhdi_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvhdi_internal_file_open_read_block_allocation_table(
     libvhdi_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

ssize_t libvhdi_internal_file_read_buffer_from_file_io_handle(
         libvhdi_internal_file_t *internal_file,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVHDI_EXTERN \
ssize_t libvhdi_file_read_buffer(
         libvhdi_file_t *file,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVHDI_EXTERN \
ssize_t libvhdi_file_read_buffer_at_offset(
         libvhdi_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libvhdi_internal_file_seek_offset(
         libvhdi_internal_file_t *internal_file,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVHDI_EXTERN \
off64_t libvhdi_file_seek_offset(
         libvhdi_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_offset(
     libvhdi_file_t *file,
     off64_t *offset,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_set_parent_file(
     libvhdi_file_t *file,
     libvhdi_file_t *parent_file,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_file_type(
     libvhdi_file_t *file,
     int *file_type,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_format_version(
     libvhdi_file_t *file,
     uint16_t *major_version,
     uint16_t *minor_version,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_disk_type(
     libvhdi_file_t *file,
     uint32_t *disk_type,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_media_size(
     libvhdi_file_t *file,
     size64_t *media_size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_bytes_per_sector(
     libvhdi_file_t *file,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_identifier(
     libvhdi_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_parent_identifier(
     libvhdi_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_utf8_parent_filename_size(
     libvhdi_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_utf8_parent_filename(
     libvhdi_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_utf16_parent_filename_size(
     libvhdi_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_utf16_parent_filename(
     libvhdi_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_INTERNAL_FILE_H ) */

