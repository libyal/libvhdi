/*
 * Parent locator functions
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

#if !defined( _LIBVHDI_PARENT_LOCATOR_H )
#define _LIBVHDI_PARENT_LOCATOR_H

#include <common.h>
#include <types.h>

#include "libvhdi_libcdata.h"
#include "libvhdi_libcerror.h"
#include "libvhdi_parent_locator_entry.h"
#include "libvhdi_parent_locator_header.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvhdi_parent_locator libvhdi_parent_locator_t;

struct libvhdi_parent_locator
{
	/* The header
	 */
	libvhdi_parent_locator_header_t *header;

	/* The entries array
	 */
	libcdata_array_t *entries_array;
};

int libvhdi_parent_locator_initialize(
     libvhdi_parent_locator_t **parent_locator,
     libcerror_error_t **error );

int libvhdi_parent_locator_free(
     libvhdi_parent_locator_t **parent_locator,
     libcerror_error_t **error );

int libvhdi_parent_locator_read_data(
     libvhdi_parent_locator_t *parent_locator,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvhdi_parent_locator_get_entry_by_utf8_key(
     libvhdi_parent_locator_t *parent_locator,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libvhdi_parent_locator_entry_t **entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVHDI_PARENT_LOCATOR_H ) */

