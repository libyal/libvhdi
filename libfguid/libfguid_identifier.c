/*
 * GUID functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfguid_definitions.h"
#include "libfguid_identifier.h"
#include "libfguid_libcerror.h"
#include "libfguid_types.h"

/* Creates an identifier
 * Make sure the value identifier is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_initialize(
     libfguid_identifier_t **identifier,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_initialize";

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( *identifier != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid identifier value already set.",
		 function );

		return( -1 );
	}
	internal_identifier = memory_allocate_structure(
	                       libfguid_internal_identifier_t );

	if( internal_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create identifier.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_identifier,
	     0,
	     sizeof( libfguid_internal_identifier_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear identifier.",
		 function );

		goto on_error;
	}
	*identifier = (libfguid_identifier_t *) internal_identifier;

	return( 1 );

on_error:
	if( internal_identifier != NULL )
	{
		memory_free(
		 internal_identifier );
	}
	return( -1 );
}

/* Frees an identifier
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_free(
     libfguid_identifier_t **identifier,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_free";

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( *identifier != NULL )
	{
		internal_identifier = (libfguid_internal_identifier_t *) *identifier;
		*identifier         = NULL;

		memory_free(
		 internal_identifier );
	}
	return( 1 );
}

/* Copies the identifier from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_byte_stream(
     libfguid_identifier_t *identifier,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_from_byte_stream";

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: byte stream size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBFGUID_ENDIAN_BIG )
	 && ( byte_order != LIBFGUID_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBFGUID_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint32_little_endian(
		 byte_stream,
		 internal_identifier->time.lower );

		byte_stream += 4;

		byte_stream_copy_to_uint16_little_endian(
		 byte_stream,
		 internal_identifier->time.middle );

		byte_stream += 2;

		byte_stream_copy_to_uint16_little_endian(
		 byte_stream,
		 internal_identifier->time.upper );

		byte_stream += 2;
	}
	else if( byte_order == LIBFGUID_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint32_big_endian(
		 byte_stream,
		 internal_identifier->time.lower );

		byte_stream += 4;

		byte_stream_copy_to_uint16_big_endian(
		 byte_stream,
		 internal_identifier->time.middle );

		byte_stream += 2;

		byte_stream_copy_to_uint16_big_endian(
		 byte_stream,
		 internal_identifier->time.upper );

		byte_stream += 2;
	}
	internal_identifier->clock_sequence.upper = byte_stream[ 0 ];
	internal_identifier->clock_sequence.lower = byte_stream[ 1 ];
	internal_identifier->node[ 0 ]            = byte_stream[ 2 ];
	internal_identifier->node[ 1 ]            = byte_stream[ 3 ];
	internal_identifier->node[ 2 ]            = byte_stream[ 4 ];
	internal_identifier->node[ 3 ]            = byte_stream[ 5 ];
	internal_identifier->node[ 4 ]            = byte_stream[ 6 ];
	internal_identifier->node[ 5 ]            = byte_stream[ 7 ];

	return( 1 );
}

/* Copies the identifier to a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_byte_stream(
     libfguid_identifier_t *identifier,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_to_byte_stream";

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: byte stream size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBFGUID_ENDIAN_BIG )
	 && ( byte_order != LIBFGUID_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBFGUID_ENDIAN_LITTLE )
	{
		byte_stream_copy_from_uint32_little_endian(
		 byte_stream,
		 internal_identifier->time.lower );

		byte_stream += 4;

		byte_stream_copy_from_uint16_little_endian(
		 byte_stream,
		 internal_identifier->time.middle );

		byte_stream += 2;

		byte_stream_copy_from_uint16_little_endian(
		 byte_stream,
		 internal_identifier->time.upper );

		byte_stream += 2;
	}
	else if( byte_order == LIBFGUID_ENDIAN_BIG )
	{
		byte_stream_copy_from_uint32_big_endian(
		 byte_stream,
		 internal_identifier->time.lower );

		byte_stream += 4;

		byte_stream_copy_from_uint16_big_endian(
		 byte_stream,
		 internal_identifier->time.middle );

		byte_stream += 2;

		byte_stream_copy_from_uint16_big_endian(
		 byte_stream,
		 internal_identifier->time.upper );

		byte_stream += 2;
	}
	byte_stream[ 0 ] = internal_identifier->clock_sequence.upper;
	byte_stream[ 1 ] = internal_identifier->clock_sequence.lower;
	byte_stream[ 2 ] = internal_identifier->node[ 0 ];
	byte_stream[ 3 ] = internal_identifier->node[ 1 ];
	byte_stream[ 4 ] = internal_identifier->node[ 2 ];
	byte_stream[ 5 ] = internal_identifier->node[ 3 ];
	byte_stream[ 6 ] = internal_identifier->node[ 4 ];
	byte_stream[ 7 ] = internal_identifier->node[ 5 ];

	return( 1 );
}

/* Retrieves the size of an UTF-8 encoded string of the identifier
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_get_string_size(
     libfguid_identifier_t *identifier,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function    = "libfguid_identifier_get_string_size";
	uint32_t supported_flags = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & supported_flags ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	*string_size = 37;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		*string_size += 2;
	}
	return( 1 );
}

/* Copies the identifier from an UTF-8 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_utf8_string(
     libfguid_identifier_t *identifier,
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function    = "libfguid_identifier_copy_from_utf8_string";
	size_t utf8_string_index = 0;

	if( libfguid_identifier_copy_from_utf8_string_with_index(
	     identifier,
	     utf8_string,
	     utf8_string_size,
	     &utf8_string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier from UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the identifier from an UTF-8 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_utf8_string_with_index(
     libfguid_identifier_t *identifier,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     size_t *utf8_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_from_utf8_string_with_index";
	size_t byte_index                                   = 0;
	size_t node_index                                   = 0;
	size_t string_length                                = 0;
	size_t string_index                                 = 0;
	uint32_t supported_flags                            = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 index.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_length = 36;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		string_length += 2;
	}
	string_index = *utf8_string_index;

	if( ( string_index + string_length ) > utf8_string_length )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string is too small.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		if( utf8_string[ string_index ] != (uint8_t) '{' )
		{
			goto on_error;
		}
		string_index++;
	}
	for( byte_index = 0;
	     byte_index < 8;
	     byte_index++ )
	{
		internal_identifier->time.lower <<= 4;

		if( ( utf8_string[ string_index ] >= (uint8_t) '0' )
		 && ( utf8_string[ string_index ] <= (uint8_t) '9' ) )
		{
			internal_identifier->time.lower |= utf8_string[ string_index ] - (uint8_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'a' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'f' ) )
		{
			internal_identifier->time.lower |= utf8_string[ string_index ] - (uint8_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'A' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'F' ) )
		{
			internal_identifier->time.lower |= utf8_string[ string_index ] - (uint8_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf8_string[ string_index ] != (uint8_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 4;
	     byte_index++ )
	{
		internal_identifier->time.middle <<= 4;

		if( ( utf8_string[ string_index ] >= (uint8_t) '0' )
		 && ( utf8_string[ string_index ] <= (uint8_t) '9' ) )
		{
			internal_identifier->time.middle |= utf8_string[ string_index ] - (uint8_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'a' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'f' ) )
		{
			internal_identifier->time.middle |= utf8_string[ string_index ] - (uint8_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'A' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'F' ) )
		{
			internal_identifier->time.middle |= utf8_string[ string_index ] - (uint8_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf8_string[ string_index ] != (uint8_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 4;
	     byte_index++ )
	{
		internal_identifier->time.upper <<= 4;

		if( ( utf8_string[ string_index ] >= (uint8_t) '0' )
		 && ( utf8_string[ string_index ] <= (uint8_t) '9' ) )
		{
			internal_identifier->time.upper |= utf8_string[ string_index ] - (uint8_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'a' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'f' ) )
		{
			internal_identifier->time.upper |= utf8_string[ string_index ] - (uint8_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'A' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'F' ) )
		{
			internal_identifier->time.upper |= utf8_string[ string_index ] - (uint8_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf8_string[ string_index ] != (uint8_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 2;
	     byte_index++ )
	{
		internal_identifier->clock_sequence.upper <<= 4;

		if( ( utf8_string[ string_index ] >= (uint8_t) '0' )
		 && ( utf8_string[ string_index ] <= (uint8_t) '9' ) )
		{
			internal_identifier->clock_sequence.upper |= utf8_string[ string_index ] - (uint8_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'a' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'f' ) )
		{
			internal_identifier->clock_sequence.upper |= utf8_string[ string_index ] - (uint8_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'A' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'F' ) )
		{
			internal_identifier->clock_sequence.upper |= utf8_string[ string_index ] - (uint8_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	for( byte_index = 0;
	     byte_index < 2;
	     byte_index++ )
	{
		internal_identifier->clock_sequence.lower <<= 4;

		if( ( utf8_string[ string_index ] >= (uint8_t) '0' )
		 && ( utf8_string[ string_index ] <= (uint8_t) '9' ) )
		{
			internal_identifier->clock_sequence.lower |= utf8_string[ string_index ] - (uint8_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'a' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'f' ) )
		{
			internal_identifier->clock_sequence.lower |= utf8_string[ string_index ] - (uint8_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'A' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'F' ) )
		{
			internal_identifier->clock_sequence.lower |= utf8_string[ string_index ] - (uint8_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf8_string[ string_index ] != (uint8_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 12;
	     byte_index++ )
	{
		node_index = byte_index / 2;

		internal_identifier->node[ node_index ] <<= 4;

		if( ( utf8_string[ string_index ] >= (uint8_t) '0' )
		 && ( utf8_string[ string_index ] <= (uint8_t) '9' ) )
		{
			internal_identifier->node[ node_index ] |= utf8_string[ string_index ] - (uint8_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'a' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'f' ) )
		{
			internal_identifier->node[ node_index ] |= utf8_string[ string_index ] - (uint8_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf8_string[ string_index ] >= (uint8_t) 'A' )
		      && ( utf8_string[ string_index ] <= (uint8_t) 'F' ) )
		{
			internal_identifier->node[ node_index ] |= utf8_string[ string_index ] - (uint8_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		if( utf8_string[ string_index ] != (uint8_t) '}' )
		{
			goto on_error;
		}
		string_index++;
	}
	*utf8_string_index = string_index;

	return( 1 );

on_error:
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
	 "%s: unsupported character value: 0x%02" PRIx8 " at index: %d.",
	 function,
	 utf8_string[ string_index ],
	 string_index );

	return( -1 );
}

/* Copies the identifier to an UTF-8 encoded string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_utf8_string(
     libfguid_identifier_t *identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function    = "libfguid_identifier_copy_to_utf8_string";
	size_t utf8_string_index = 0;

	if( libfguid_identifier_copy_to_utf8_string_with_index(
	     identifier,
	     utf8_string,
	     utf8_string_size,
	     &utf8_string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the identifier to an UTF-8 encoded string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_utf8_string_with_index(
     libfguid_identifier_t *identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_to_utf8_string_with_index";
	size_t string_index                                 = 0;
	size_t string_size                                  = 0;
	uint32_t supported_flags                            = 0;
	uint8_t byte_value                                  = 0;
	uint8_t node_index                                  = 0;
	int8_t byte_shift                                   = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: UTF-8 string size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 index.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & supported_flags ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_size = 37;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		string_size += 2;
	}
	string_index = *utf8_string_index;

	if( ( string_index + string_size ) > utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string is too small.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		utf8_string[ string_index++ ] = (uint8_t) '{';
	}
	byte_shift = 28;

	do
	{
		byte_value = ( internal_identifier->time.lower >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf8_string[ string_index++ ] = (uint8_t) 'A' + byte_value - 10;
		}
		else
		{
			utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf8_string[ string_index++ ] = (uint8_t) '-';

	byte_shift = 12;

	do
	{
		byte_value = ( internal_identifier->time.middle >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf8_string[ string_index++ ] = (uint8_t) 'A' + byte_value - 10;
		}
		else
		{
			utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf8_string[ string_index++ ] = (uint8_t) '-';

	byte_shift = 12;

	do
	{
		byte_value = ( internal_identifier->time.upper >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf8_string[ string_index++ ] = (uint8_t) 'A' + byte_value - 10;
		}
		else
		{
			utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf8_string[ string_index++ ] = (uint8_t) '-';

	byte_shift = 4;

	do
	{
		byte_value = ( internal_identifier->clock_sequence.upper >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf8_string[ string_index++ ] = (uint8_t) 'A' + byte_value - 10;
		}
		else
		{
			utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	byte_shift = 4;

	do
	{
		byte_value = ( internal_identifier->clock_sequence.lower >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf8_string[ string_index++ ] = (uint8_t) 'A' + byte_value - 10;
		}
		else
		{
			utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf8_string[ string_index++ ] = (uint8_t) '-';

	for( node_index = 0;
	     node_index < 6;
	     node_index++ )
	{
		byte_shift = 4;

		do
		{
			byte_value = ( internal_identifier->node[ node_index ] >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf8_string[ string_index++ ] = (uint8_t) '0' + byte_value;
			}
			else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
			{
				utf8_string[ string_index++ ] = (uint8_t) 'A' + byte_value - 10;
			}
			else
			{
				utf8_string[ string_index++ ] = (uint8_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift >= 0 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		utf8_string[ string_index++ ] = (uint8_t) '}';
	}
	utf8_string[ string_index++ ] = 0;

	*utf8_string_index = string_index;

	return( 1 );
}

/* Copies the identifier from an UTF-16 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_utf16_string(
     libfguid_identifier_t *identifier,
     const uint16_t *utf16_string,
     size_t utf16_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function     = "libfguid_identifier_copy_from_utf16_string";
	size_t utf16_string_index = 0;

	if( libfguid_identifier_copy_from_utf16_string_with_index(
	     identifier,
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier from UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the identifier from an UTF-16 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_utf16_string_with_index(
     libfguid_identifier_t *identifier,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     size_t *utf16_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_from_utf16_string_with_index";
	size_t byte_index                                   = 0;
	size_t node_index                                   = 0;
	size_t string_length                                = 0;
	size_t string_index                                 = 0;
	uint32_t supported_flags                            = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 index.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_length = 36;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		string_length += 2;
	}
	string_index = *utf16_string_index;

	if( ( string_index + string_length ) > utf16_string_length )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string is too small.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		if( utf16_string[ string_index ] != (uint16_t) '{' )
		{
			goto on_error;
		}
		string_index++;
	}
	for( byte_index = 0;
	     byte_index < 8;
	     byte_index++ )
	{
		internal_identifier->time.lower <<= 4;

		if( ( utf16_string[ string_index ] >= (uint16_t) '0' )
		 && ( utf16_string[ string_index ] <= (uint16_t) '9' ) )
		{
			internal_identifier->time.lower |= utf16_string[ string_index ] - (uint16_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'a' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'f' ) )
		{
			internal_identifier->time.lower |= utf16_string[ string_index ] - (uint16_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'A' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'F' ) )
		{
			internal_identifier->time.lower |= utf16_string[ string_index ] - (uint16_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf16_string[ string_index ] != (uint16_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 4;
	     byte_index++ )
	{
		internal_identifier->time.middle <<= 4;

		if( ( utf16_string[ string_index ] >= (uint16_t) '0' )
		 && ( utf16_string[ string_index ] <= (uint16_t) '9' ) )
		{
			internal_identifier->time.middle |= utf16_string[ string_index ] - (uint16_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'a' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'f' ) )
		{
			internal_identifier->time.middle |= utf16_string[ string_index ] - (uint16_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'A' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'F' ) )
		{
			internal_identifier->time.middle |= utf16_string[ string_index ] - (uint16_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf16_string[ string_index ] != (uint16_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 4;
	     byte_index++ )
	{
		internal_identifier->time.upper <<= 4;

		if( ( utf16_string[ string_index ] >= (uint16_t) '0' )
		 && ( utf16_string[ string_index ] <= (uint16_t) '9' ) )
		{
			internal_identifier->time.upper |= utf16_string[ string_index ] - (uint16_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'a' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'f' ) )
		{
			internal_identifier->time.upper |= utf16_string[ string_index ] - (uint16_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'A' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'F' ) )
		{
			internal_identifier->time.upper |= utf16_string[ string_index ] - (uint16_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf16_string[ string_index ] != (uint16_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 2;
	     byte_index++ )
	{
		internal_identifier->clock_sequence.upper <<= 4;

		if( ( utf16_string[ string_index ] >= (uint16_t) '0' )
		 && ( utf16_string[ string_index ] <= (uint16_t) '9' ) )
		{
			internal_identifier->clock_sequence.upper |= utf16_string[ string_index ] - (uint16_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'a' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'f' ) )
		{
			internal_identifier->clock_sequence.upper |= utf16_string[ string_index ] - (uint16_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'A' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'F' ) )
		{
			internal_identifier->clock_sequence.upper |= utf16_string[ string_index ] - (uint16_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	for( byte_index = 0;
	     byte_index < 2;
	     byte_index++ )
	{
		internal_identifier->clock_sequence.lower <<= 4;

		if( ( utf16_string[ string_index ] >= (uint16_t) '0' )
		 && ( utf16_string[ string_index ] <= (uint16_t) '9' ) )
		{
			internal_identifier->clock_sequence.lower |= utf16_string[ string_index ] - (uint16_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'a' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'f' ) )
		{
			internal_identifier->clock_sequence.lower |= utf16_string[ string_index ] - (uint16_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'A' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'F' ) )
		{
			internal_identifier->clock_sequence.lower |= utf16_string[ string_index ] - (uint16_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf16_string[ string_index ] != (uint16_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 12;
	     byte_index++ )
	{
		node_index = byte_index / 2;

		internal_identifier->node[ node_index ] <<= 4;

		if( ( utf16_string[ string_index ] >= (uint16_t) '0' )
		 && ( utf16_string[ string_index ] <= (uint16_t) '9' ) )
		{
			internal_identifier->node[ node_index ] |= utf16_string[ string_index ] - (uint16_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'a' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'f' ) )
		{
			internal_identifier->node[ node_index ] |= utf16_string[ string_index ] - (uint16_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf16_string[ string_index ] >= (uint16_t) 'A' )
		      && ( utf16_string[ string_index ] <= (uint16_t) 'F' ) )
		{
			internal_identifier->node[ node_index ] |= utf16_string[ string_index ] - (uint16_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		if( utf16_string[ string_index ] != (uint16_t) '}' )
		{
			goto on_error;
		}
		string_index++;
	}
	*utf16_string_index = string_index;

	return( 1 );

on_error:
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
	 "%s: unsupported character value: 0x%04" PRIx16 " at index: %d.",
	 function,
	 utf16_string[ string_index ],
	 string_index );

	return( -1 );
}

/* Copies the identifier to an UTF-16 encoded string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_utf16_string(
     libfguid_identifier_t *identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function     = "libfguid_identifier_copy_to_utf16_string";
	size_t utf16_string_index = 0;

	if( libfguid_identifier_copy_to_utf16_string_with_index(
	     identifier,
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the identifier to an UTF-16 encoded string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_utf16_string_with_index(
     libfguid_identifier_t *identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_to_utf16_string_with_index";
	size_t string_index                                 = 0;
	size_t string_size                                  = 0;
	uint32_t supported_flags                            = 0;
	uint8_t byte_value                                  = 0;
	uint8_t node_index                                  = 0;
	int8_t byte_shift                                   = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: UTF-16 string size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 index.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & supported_flags ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_size = 37;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		string_size += 2;
	}
	string_index = *utf16_string_index;

	if( ( string_index + string_size ) > utf16_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string is too small.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		utf16_string[ string_index++ ] = (uint16_t) '{';
	}
	string_index = *utf16_string_index;

	byte_shift = 28;

	do
	{
		byte_value = ( internal_identifier->time.lower >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf16_string[ string_index++ ] = (uint16_t) 'A' + byte_value - 10;
		}
		else
		{
			utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf16_string[ string_index++ ] = (uint16_t) '-';

	byte_shift = 12;

	do
	{
		byte_value = ( internal_identifier->time.middle >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf16_string[ string_index++ ] = (uint16_t) 'A' + byte_value - 10;
		}
		else
		{
			utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf16_string[ string_index++ ] = (uint16_t) '-';

	byte_shift = 12;

	do
	{
		byte_value = ( internal_identifier->time.upper >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf16_string[ string_index++ ] = (uint16_t) 'A' + byte_value - 10;
		}
		else
		{
			utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf16_string[ string_index++ ] = (uint16_t) '-';

	byte_shift = 4;

	do
	{
		byte_value = ( internal_identifier->clock_sequence.upper >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf16_string[ string_index++ ] = (uint16_t) 'A' + byte_value - 10;
		}
		else
		{
			utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	byte_shift = 4;

	do
	{
		byte_value = ( internal_identifier->clock_sequence.lower >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf16_string[ string_index++ ] = (uint16_t) 'A' + byte_value - 10;
		}
		else
		{
			utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf16_string[ string_index++ ] = (uint16_t) '-';

	for( node_index = 0;
	     node_index < 6;
	     node_index++ )
	{
		byte_shift = 4;

		do
		{
			byte_value = ( internal_identifier->node[ node_index ] >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf16_string[ string_index++ ] = (uint16_t) '0' + byte_value;
			}
			else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
			{
				utf16_string[ string_index++ ] = (uint16_t) 'A' + byte_value - 10;
			}
			else
			{
				utf16_string[ string_index++ ] = (uint16_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift >= 0 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		utf16_string[ string_index++ ] = (uint16_t) '}';
	}
	utf16_string[ string_index++ ] = 0;

	*utf16_string_index = string_index;

	return( 1 );
}

/* Copies the identifier from an UTF-32 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_utf32_string(
     libfguid_identifier_t *identifier,
     const uint32_t *utf32_string,
     size_t utf32_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function     = "libfguid_identifier_copy_from_utf32_string";
	size_t utf32_string_index = 0;

	if( libfguid_identifier_copy_from_utf32_string_with_index(
	     identifier,
	     utf32_string,
	     utf32_string_size,
	     &utf32_string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier from UTF-32 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the identifier from an UTF-32 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_from_utf32_string_with_index(
     libfguid_identifier_t *identifier,
     const uint32_t *utf32_string,
     size_t utf32_string_length,
     size_t *utf32_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_from_utf32_string_with_index";
	size_t byte_index                                   = 0;
	size_t node_index                                   = 0;
	size_t string_length                                = 0;
	size_t string_index                                 = 0;
	uint32_t supported_flags                            = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 index.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_length = 36;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		string_length += 2;
	}
	string_index = *utf32_string_index;

	if( ( string_index + string_length ) > utf32_string_length )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string is too small.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		if( utf32_string[ string_index ] != (uint32_t) '{' )
		{
			goto on_error;
		}
		string_index++;
	}
	for( byte_index = 0;
	     byte_index < 8;
	     byte_index++ )
	{
		internal_identifier->time.lower <<= 4;

		if( ( utf32_string[ string_index ] >= (uint32_t) '0' )
		 && ( utf32_string[ string_index ] <= (uint32_t) '9' ) )
		{
			internal_identifier->time.lower |= utf32_string[ string_index ] - (uint32_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'a' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'f' ) )
		{
			internal_identifier->time.lower |= utf32_string[ string_index ] - (uint32_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'A' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'F' ) )
		{
			internal_identifier->time.lower |= utf32_string[ string_index ] - (uint32_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf32_string[ string_index ] != (uint32_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 4;
	     byte_index++ )
	{
		internal_identifier->time.middle <<= 4;

		if( ( utf32_string[ string_index ] >= (uint32_t) '0' )
		 && ( utf32_string[ string_index ] <= (uint32_t) '9' ) )
		{
			internal_identifier->time.middle |= utf32_string[ string_index ] - (uint32_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'a' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'f' ) )
		{
			internal_identifier->time.middle |= utf32_string[ string_index ] - (uint32_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'A' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'F' ) )
		{
			internal_identifier->time.middle |= utf32_string[ string_index ] - (uint32_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf32_string[ string_index ] != (uint32_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 4;
	     byte_index++ )
	{
		internal_identifier->time.upper <<= 4;

		if( ( utf32_string[ string_index ] >= (uint32_t) '0' )
		 && ( utf32_string[ string_index ] <= (uint32_t) '9' ) )
		{
			internal_identifier->time.upper |= utf32_string[ string_index ] - (uint32_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'a' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'f' ) )
		{
			internal_identifier->time.upper |= utf32_string[ string_index ] - (uint32_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'A' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'F' ) )
		{
			internal_identifier->time.upper |= utf32_string[ string_index ] - (uint32_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf32_string[ string_index ] != (uint32_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 2;
	     byte_index++ )
	{
		internal_identifier->clock_sequence.upper <<= 4;

		if( ( utf32_string[ string_index ] >= (uint32_t) '0' )
		 && ( utf32_string[ string_index ] <= (uint32_t) '9' ) )
		{
			internal_identifier->clock_sequence.upper |= utf32_string[ string_index ] - (uint32_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'a' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'f' ) )
		{
			internal_identifier->clock_sequence.upper |= utf32_string[ string_index ] - (uint32_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'A' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'F' ) )
		{
			internal_identifier->clock_sequence.upper |= utf32_string[ string_index ] - (uint32_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	for( byte_index = 0;
	     byte_index < 2;
	     byte_index++ )
	{
		internal_identifier->clock_sequence.lower <<= 4;

		if( ( utf32_string[ string_index ] >= (uint32_t) '0' )
		 && ( utf32_string[ string_index ] <= (uint32_t) '9' ) )
		{
			internal_identifier->clock_sequence.lower |= utf32_string[ string_index ] - (uint32_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'a' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'f' ) )
		{
			internal_identifier->clock_sequence.lower |= utf32_string[ string_index ] - (uint32_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'A' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'F' ) )
		{
			internal_identifier->clock_sequence.lower |= utf32_string[ string_index ] - (uint32_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( utf32_string[ string_index ] != (uint32_t) '-' )
	{
		goto on_error;
	}
	string_index++;

	for( byte_index = 0;
	     byte_index < 12;
	     byte_index++ )
	{
		node_index = byte_index / 2;

		internal_identifier->node[ node_index ] <<= 4;

		if( ( utf32_string[ string_index ] >= (uint32_t) '0' )
		 && ( utf32_string[ string_index ] <= (uint32_t) '9' ) )
		{
			internal_identifier->node[ node_index ] |= utf32_string[ string_index ] - (uint32_t) '0';
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'a' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'f' ) )
		{
			internal_identifier->node[ node_index ] |= utf32_string[ string_index ] - (uint32_t) 'a' + 10;
		}
		else if( ( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		      && ( utf32_string[ string_index ] >= (uint32_t) 'A' )
		      && ( utf32_string[ string_index ] <= (uint32_t) 'F' ) )
		{
			internal_identifier->node[ node_index ] |= utf32_string[ string_index ] - (uint32_t) 'A' + 10;
		}
		else
		{
			goto on_error;
		}
		string_index++;
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		if( utf32_string[ string_index ] != (uint32_t) '}' )
		{
			goto on_error;
		}
		string_index++;
	}
	*utf32_string_index = string_index;

	return( 1 );

on_error:
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
	 "%s: unsupported character value: 0x%08" PRIx32 " at index: %d.",
	 function,
	 utf32_string[ string_index ],
	 string_index );

	return( -1 );
}

/* Copies the identifier to an UTF-32 encoded string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_utf32_string(
     libfguid_identifier_t *identifier,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function     = "libfguid_identifier_copy_to_utf32_string";
	size_t utf32_string_index = 0;

	if( libfguid_identifier_copy_to_utf32_string_with_index(
	     identifier,
	     utf32_string,
	     utf32_string_size,
	     &utf32_string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier to UTF-32 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the identifier to an UTF-32 encoded string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfguid_identifier_copy_to_utf32_string_with_index(
     libfguid_identifier_t *identifier,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libfguid_internal_identifier_t *internal_identifier = NULL;
	static char *function                               = "libfguid_identifier_copy_to_utf32_string_with_index";
	size_t string_index                                 = 0;
	size_t string_size                                  = 0;
	uint32_t supported_flags                            = 0;
	uint8_t byte_value                                  = 0;
	uint8_t node_index                                  = 0;
	int8_t byte_shift                                   = 0;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	internal_identifier = (libfguid_internal_identifier_t *) identifier;

	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: UTF-32 string size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 index.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE
	                | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES;

	if( ( string_format_flags & supported_flags ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_size = 37;

	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		string_size += 2;
	}
	string_index = *utf32_string_index;

	if( ( string_index + string_size ) > utf32_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string is too small.",
		 function );

		return( -1 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		utf32_string[ string_index++ ] = (uint32_t) '{';
	}
	string_index = *utf32_string_index;

	byte_shift = 28;

	do
	{
		byte_value = ( internal_identifier->time.lower >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf32_string[ string_index++ ] = (uint32_t) 'A' + byte_value - 10;
		}
		else
		{
			utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf32_string[ string_index++ ] = (uint32_t) '-';

	byte_shift = 12;

	do
	{
		byte_value = ( internal_identifier->time.middle >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf32_string[ string_index++ ] = (uint32_t) 'A' + byte_value - 10;
		}
		else
		{
			utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf32_string[ string_index++ ] = (uint32_t) '-';

	byte_shift = 12;

	do
	{
		byte_value = ( internal_identifier->time.upper >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf32_string[ string_index++ ] = (uint32_t) 'A' + byte_value - 10;
		}
		else
		{
			utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf32_string[ string_index++ ] = (uint32_t) '-';

	byte_shift = 4;

	do
	{
		byte_value = ( internal_identifier->clock_sequence.upper >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf32_string[ string_index++ ] = (uint32_t) 'A' + byte_value - 10;
		}
		else
		{
			utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	byte_shift = 4;

	do
	{
		byte_value = ( internal_identifier->clock_sequence.lower >> byte_shift ) & 0x0f;

		if( byte_value <= 9 )
		{
			utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
		}
		else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
		{
			utf32_string[ string_index++ ] = (uint32_t) 'A' + byte_value - 10;
		}
		else
		{
			utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
		}
		byte_shift -= 4;
	}
	while( byte_shift >= 0 );

	utf32_string[ string_index++ ] = (uint32_t) '-';

	for( node_index = 0;
	     node_index < 6;
	     node_index++ )
	{
		byte_shift = 4;

		do
		{
			byte_value = ( internal_identifier->node[ node_index ] >> byte_shift ) & 0x0f;

			if( byte_value <= 9 )
			{
				utf32_string[ string_index++ ] = (uint32_t) '0' + byte_value;
			}
			else if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE ) != 0 )
			{
				utf32_string[ string_index++ ] = (uint32_t) 'A' + byte_value - 10;
			}
			else
			{
				utf32_string[ string_index++ ] = (uint32_t) 'a' + byte_value - 10;
			}
			byte_shift -= 4;
		}
		while( byte_shift >= 0 );
	}
	if( ( string_format_flags & LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES ) != 0 )
	{
		utf32_string[ string_index++ ] = (uint32_t) '}';
	}
	utf32_string[ string_index++ ] = 0;

	*utf32_string_index = string_index;

	return( 1 );
}

