/*
 * Global (or Universal) Unique Identifier (GUID/UUID) functions
 *
 * Copyright (c) 2010-2013, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFGUID_INTERNAL_IDENTIFIER_H )
#define _LIBFGUID_INTERNAL_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libfguid_extern.h"
#include "libfguid_libcerror.h"
#include "libfguid_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfguid_internal_identifier libfguid_internal_identifier_t;

/* The GUID is stored as:
 * uint32 - uint16 - uint16 - 8 byte array
 */
struct libfguid_internal_identifier
{
	/* The 4 MSB of the time upper contain the version
	 */
	struct
	{
		uint32_t lower;
		uint16_t middle;
		uint16_t upper;
	} time;

	/* The clock sequence upper also contains the reserved
	 */
	struct
	{
		uint8_t upper;
		uint8_t lower;
	}
	clock_sequence;

	uint8_t node[ 6 ];
};

LIBFGUID_EXTERN \
int libfguid_identifier_initialize(
     libfguid_identifier_t **identifier,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_free(
     libfguid_identifier_t **identifier,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_byte_stream(
     libfguid_identifier_t *identifier,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_byte_stream(
     libfguid_identifier_t *identifier,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_get_string_size(
     libfguid_identifier_t *identifier,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_utf8_string(
     libfguid_identifier_t *identifier,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_utf8_string_with_index(
     libfguid_identifier_t *identifier,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     size_t *utf8_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_utf8_string(
     libfguid_identifier_t *identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_utf8_string_with_index(
     libfguid_identifier_t *identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_utf16_string(
     libfguid_identifier_t *identifier,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_utf16_string_with_index(
     libfguid_identifier_t *identifier,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     size_t *utf16_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_utf16_string(
     libfguid_identifier_t *identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_utf16_string_with_index(
     libfguid_identifier_t *identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_utf32_string(
     libfguid_identifier_t *identifier,
     const uint32_t *utf32_string,
     size_t utf32_string_length,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_from_utf32_string_with_index(
     libfguid_identifier_t *identifier,
     const uint32_t *utf32_string,
     size_t utf32_string_length,
     size_t *utf32_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_utf32_string(
     libfguid_identifier_t *identifier,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBFGUID_EXTERN \
int libfguid_identifier_copy_to_utf32_string_with_index(
     libfguid_identifier_t *identifier,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

