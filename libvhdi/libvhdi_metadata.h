/*
 * Metadata functions
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

#if !defined( _LIBVHDI_METADATA_H )
#define _LIBVHDI_METADATA_H

#include <common.h>
#include <types.h>

#include "libvhdi_extern.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBVHDI_EXTERN \
int libvhdi_file_get_media_size(
     libvhdi_file_t *file,
     size64_t *media_size,
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
int libvhdi_file_get_identifier(
     libvhdi_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBVHDI_EXTERN \
int libvhdi_file_get_parent_identifier(
     libvhdi_file_t *file,
     uint8_t *guid,
     size_t size,
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

#endif

