/*
 * File functions
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVHDI_INTERNAL_FILE_H )
#define _LIBVHDI_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libvhdi_block_table.h"
#include "libvhdi_extern.h"
#include "libvhdi_io_handle.h"
#include "libvhdi_libbfio.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_libcthreads.h"
#include "libvhdi_libfcache.h"
#include "libvhdi_libfdata.h"

#if defined( _MSC_VER ) || defined( __BORLANDC__ ) || defined( __MINGW32_VERSION ) || defined( __MINGW64_VERSION_MAJOR )

/* This inclusion is needed otherwise some linkers
 * mess up exporting the metadata functions
 */
#include "libvhdi_metadata.h"
#endif

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

	/* The block table
	 */
	libvhdi_block_table_t *block_table;

	/* The data block vector
	 */
	libfdata_vector_t *data_block_vector;

	/* The data block cache
	 */
	libfcache_cache_t *data_block_cache;

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
#endif

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

int libvhdi_file_open_read(
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

LIBVHDI_EXTERN \
ssize_t libvhdi_file_read_random(
         libvhdi_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

#ifdef TODO_WRITE_SUPPORT

ssize_t libvhdi_internal_file_write_buffer_to_file_io_handle(
         libvhdi_internal_file_t *internal_file,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVHDI_EXTERN \
ssize_t libvhdi_file_write_buffer(
         libvhdi_file_t *file,
         const void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVHDI_EXTERN \
ssize_t libvhdi_file_write_buffer_at_offset(
         libvhdi_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

#endif /* TODO_WRITE_SUPPORT */

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

#if defined( __cplusplus )
}
#endif

#endif

