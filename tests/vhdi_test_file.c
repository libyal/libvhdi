/*
 * Library file type test program
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

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vhdi_test_getopt.h"
#include "vhdi_test_libcerror.h"
#include "vhdi_test_libclocale.h"
#include "vhdi_test_libcpath.h"
#include "vhdi_test_libuna.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_macros.h"
#include "vhdi_test_memory.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vhdi_test_file generate verbose output
#define VHDI_TEST_FILE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int vhdi_test_file_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "vhdi_test_file_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int vhdi_test_file_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "vhdi_test_file_get_wide_source";
	size_t source_length    = 0;
	size_t wide_source_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int vhdi_test_file_open_source(
     libvhdi_file_t **file,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "vhdi_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libvhdi_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvhdi_file_open_wide(
	          *file,
	          source,
	          LIBVHDI_OPEN_READ,
	          error );
#else
	result = libvhdi_file_open(
	          *file,
	          source,
	          LIBVHDI_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libvhdi_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Opens the parent input file
 * Returns 1 if successful, 0 if no parent file or -1 on error
 */
int vhdi_test_file_open_parent_file(
     libvhdi_file_t **parent_file,
     const system_character_t *source,
     libvhdi_file_t *file,
     libcerror_error_t **error )
{
	uint8_t guid[ 16 ];

	system_character_t *basename_end        = NULL;
	system_character_t *parent_basename_end = NULL;
	system_character_t *parent_filename     = NULL;
	system_character_t *parent_path         = NULL;
	static char *function                   = "vhdi_test_file_open_parent_file";
	size_t basename_length                  = 0;
	size_t parent_basename_length           = 0;
	size_t parent_filename_size             = 0;
	size_t parent_path_size                 = 0;
	size_t source_length                    = 0;
	int result                              = 0;

	if( parent_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid parent file.",
		 function );

		return( -1 );
	}
	result = libvhdi_file_get_parent_identifier(
	          file,
	          guid,
	          16,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve parent content identifier.",
		 function );

		goto on_error;
	}
	else if( result != 1 )
	{
		return( 0 );
	}
	source_length = system_string_length(
	                 source );

	basename_end = system_string_search_character_reverse(
	                source,
	                (system_character_t) LIBCPATH_SEPARATOR,
	                source_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - source );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvhdi_file_get_utf16_parent_filename_size(
		  file,
		  &parent_filename_size,
		  error );
#else
	result = libvhdi_file_get_utf8_parent_filename_size(
		  file,
		  &parent_filename_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve parent filename size.",
		 function );

		goto on_error;
	}
	if( parent_filename_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing parent filename.",
		 function );

		goto on_error;
	}
	if( parent_filename_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid parent filename size value exceeds maximum.",
		 function );

		goto on_error;
	}
	parent_filename = system_string_allocate(
	                   parent_filename_size );

	if( parent_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create parent filename string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvhdi_file_get_utf16_parent_filename(
		  file,
		  (uint16_t *) parent_filename,
		  parent_filename_size,
		  error );
#else
	result = libvhdi_file_get_utf8_parent_filename(
		  file,
		  (uint8_t *) parent_filename,
		  parent_filename_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve parent filename.",
		 function );

		goto on_error;
	}
	parent_basename_end = system_string_search_character_reverse(
	                       parent_filename,
	                       (system_character_t) '\\',
	                       parent_filename_size );

	if( parent_basename_end != NULL )
	{
		parent_basename_length = (size_t) ( parent_basename_end - parent_filename ) + 1;
	}
	if( basename_length == 0 )
	{
		parent_path      = &( parent_filename[ parent_basename_length ] );
		parent_path_size = parent_filename_size - ( parent_basename_length + 1 );
	}
	else
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( libcpath_path_join_wide(
		     &parent_path,
		     &parent_path_size,
		     source,
		     basename_length,
		     &( parent_filename[ parent_basename_length ] ),
		     parent_filename_size - ( parent_basename_length + 1 ),
		     error ) != 1 )
#else
		if( libcpath_path_join(
		     &parent_path,
		     &parent_path_size,
		     source,
		     basename_length,
		     &( parent_filename[ parent_basename_length ] ),
		     parent_filename_size - ( parent_basename_length + 1 ),
		     error ) != 1 )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create parent path.",
			 function );

			goto on_error;
		}
	}
	if( libvhdi_file_initialize(
	     parent_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize parent input file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvhdi_file_open_wide(
	     *parent_file,
	     parent_path,
	     LIBVHDI_OPEN_READ,
	     error ) != 1 )
#else
	if( libvhdi_file_open(
	     *parent_file,
	     parent_path,
	     LIBVHDI_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open parent input file: %" PRIs_SYSTEM ".",
		 function,
		 parent_path );

		goto on_error;
	}
	if( libvhdi_file_set_parent_file(
	     file,
	     *parent_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set parent input file.",
		 function );

		goto on_error;
	}
	if( ( basename_length != 0 )
	 && ( parent_path != NULL ) )
	{
		memory_free(
		 parent_path );

		parent_path = NULL;
	}
	if( parent_filename != NULL )
	{
		memory_free(
		 parent_filename );

		parent_filename = NULL;
	}
	return( 1 );

on_error:
	if( *parent_file != NULL )
	{
		libvhdi_file_free(
		 parent_file,
		 NULL );
	}
	if( ( basename_length != 0 )
	 && ( parent_path != NULL ) )
	{
		memory_free(
		 parent_path );
	}
	if( parent_filename != NULL )
	{
		memory_free(
		 parent_filename );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int vhdi_test_file_close_source(
     libvhdi_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "vhdi_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libvhdi_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libvhdi_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libvhdi_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvhdi_file_t *file            = NULL;
	int result                      = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvhdi_file_initialize(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_file_free(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_initialize(
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = (libvhdi_file_t *) 0x12345678UL;

	result = libvhdi_file_initialize(
	          &file,
	          &error );

	file = NULL;

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvhdi_file_initialize with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_file_initialize(
		          &file,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libvhdi_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			VHDI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VHDI_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			VHDI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvhdi_file_initialize with memset failing
		 */
		vhdi_test_memset_attempts_before_fail = test_number;

		result = libvhdi_file_initialize(
		          &file,
		          &error );

		if( vhdi_test_memset_attempts_before_fail != -1 )
		{
			vhdi_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libvhdi_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			VHDI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VHDI_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			VHDI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VHDI_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_file_free function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_file_free(
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_open function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libvhdi_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = vhdi_test_file_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_file_initialize(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvhdi_file_open(
	          file,
	          narrow_source,
	          LIBVHDI_OPEN_READ,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_open(
	          file,
	          narrow_source,
	          LIBVHDI_OPEN_READ,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvhdi_file_free(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvhdi_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libvhdi_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = vhdi_test_file_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_file_initialize(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvhdi_file_open_wide(
	          file,
	          wide_source,
	          LIBVHDI_OPEN_READ,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_open_wide(
	          file,
	          wide_source,
	          LIBVHDI_OPEN_READ,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvhdi_file_free(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvhdi_file_close function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_file_close(
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_open and libvhdi_file_close functions
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libvhdi_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libvhdi_file_initialize(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvhdi_file_open_wide(
	          file,
	          source,
	          LIBVHDI_OPEN_READ,
	          &error );
#else
	result = libvhdi_file_open(
	          file,
	          source,
	          LIBVHDI_OPEN_READ,
	          &error );
#endif

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_file_close(
	          file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvhdi_file_open_wide(
	          file,
	          source,
	          LIBVHDI_OPEN_READ,
	          &error );
#else
	result = libvhdi_file_open(
	          file,
	          source,
	          LIBVHDI_OPEN_READ,
	          &error );
#endif

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_file_close(
	          file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvhdi_file_free(
	          &file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_signal_abort(
     libvhdi_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_signal_abort(
	          file,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_signal_abort(
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_read_buffer(
     libvhdi_file_t *file )
{
	uint8_t buffer[ 16 ];

	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;

	/* Determine size
	 */
	offset = libvhdi_file_seek_offset(
	          file,
	          0,
	          SEEK_END,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	/* Reset offset to 0
	 */
	offset = libvhdi_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( size > 16 )
	{
		read_count = libvhdi_file_read_buffer(
		              file,
		              buffer,
		              16,
		              &error );

		VHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 16 );

		VHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
/* TODO read on size boundary */
/* TODO read beyond size boundary */

	/* Reset offset to 0
	 */
	offset = libvhdi_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvhdi_file_read_buffer(
	              NULL,
	              buffer,
	              16,
	              &error );

	VHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvhdi_file_read_buffer(
	              file,
	              NULL,
	              16,
	              &error );

	VHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvhdi_file_read_buffer(
	              file,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	VHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_seek_offset(
     libvhdi_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;

	/* Test regular cases
	 */
	offset = libvhdi_file_seek_offset(
	          file,
	          0,
	          SEEK_END,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libvhdi_file_seek_offset(
	          file,
	          1024,
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvhdi_file_seek_offset(
	          file,
	          -512,
	          SEEK_CUR,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvhdi_file_seek_offset(
	          file,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libvhdi_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvhdi_file_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvhdi_file_seek_offset(
	          file,
	          -1,
	          SEEK_SET,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvhdi_file_seek_offset(
	          file,
	          -1,
	          SEEK_CUR,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libvhdi_file_seek_offset(
	          file,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_offset(
     libvhdi_file_t *file )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_offset(
	          file,
	          &offset,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_get_offset(
	          NULL,
	          &offset,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_offset(
	          file,
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_media_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_media_size(
     libvhdi_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t media_size      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_media_size(
	          file,
	          &media_size,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_get_media_size(
	          NULL,
	          &media_size,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_media_size(
	          file,
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_disk_type function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_disk_type(
     libvhdi_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t disk_type       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_disk_type(
	          file,
	          &disk_type,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_get_disk_type(
	          NULL,
	          &disk_type,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_disk_type(
	          file,
	          NULL,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_identifier(
     libvhdi_file_t *file )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_identifier(
	          file,
	          guid_data,
	          16,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_get_identifier(
	          NULL,
	          guid_data,
	          16,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_identifier(
	          file,
	          NULL,
	          16,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_identifier(
	          file,
	          guid_data,
	          0,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

/* TODO fix
	result = libvhdi_file_get_identifier(
	          file,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );
*/

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_parent_identifier function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_parent_identifier(
     libvhdi_file_t *file )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_parent_identifier(
	          file,
	          guid_data,
	          16,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_file_get_parent_identifier(
	          NULL,
	          guid_data,
	          16,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

/* TODO fix
	result = libvhdi_file_get_parent_identifier(
	          file,
	          NULL,
	          16,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_parent_identifier(
	          file,
	          guid_data,
	          0,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvhdi_file_get_parent_identifier(
	          file,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );
*/

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_utf8_parent_filename_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_utf8_parent_filename_size(
     libvhdi_file_t *file )
{
	libcerror_error_t *error             = NULL;
	size_t utf8_parent_filename_size     = 0;
	int result                           = 0;
	int utf8_parent_filename_size_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_utf8_parent_filename_size(
	          file,
	          &utf8_parent_filename_size,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_parent_filename_size_is_set = result;

	/* Test error cases
	 */
	result = libvhdi_file_get_utf8_parent_filename_size(
	          NULL,
	          &utf8_parent_filename_size,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf8_parent_filename_size_is_set != 0 )
	{
		result = libvhdi_file_get_utf8_parent_filename_size(
		          file,
		          NULL,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_utf8_parent_filename function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_utf8_parent_filename(
     libvhdi_file_t *file )
{
	uint8_t utf8_parent_filename[ 512 ];

	libcerror_error_t *error        = NULL;
	int result                      = 0;
	int utf8_parent_filename_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_utf8_parent_filename(
	          file,
	          utf8_parent_filename,
	          512,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_parent_filename_is_set = result;

	/* Test error cases
	 */
	result = libvhdi_file_get_utf8_parent_filename(
	          NULL,
	          utf8_parent_filename,
	          512,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf8_parent_filename_is_set != 0 )
	{
		result = libvhdi_file_get_utf8_parent_filename(
		          file,
		          NULL,
		          512,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

		result = libvhdi_file_get_utf8_parent_filename(
		          file,
		          utf8_parent_filename,
		          0,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        VHDI_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );

		result = libvhdi_file_get_utf8_parent_filename(
		          file,
		          utf8_parent_filename,
		          (size_t) SSIZE_MAX + 1,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_utf16_parent_filename_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_utf16_parent_filename_size(
     libvhdi_file_t *file )
{
	libcerror_error_t *error              = NULL;
	size_t utf16_parent_filename_size     = 0;
	int result                            = 0;
	int utf16_parent_filename_size_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_utf16_parent_filename_size(
	          file,
	          &utf16_parent_filename_size,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_parent_filename_size_is_set = result;

	/* Test error cases
	 */
	result = libvhdi_file_get_utf16_parent_filename_size(
	          NULL,
	          &utf16_parent_filename_size,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf16_parent_filename_size_is_set != 0 )
	{
		result = libvhdi_file_get_utf16_parent_filename_size(
		          file,
		          NULL,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_file_get_utf16_parent_filename function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_file_get_utf16_parent_filename(
     libvhdi_file_t *file )
{
	uint16_t utf16_parent_filename[ 512 ];

	libcerror_error_t *error         = NULL;
	int result                       = 0;
	int utf16_parent_filename_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_file_get_utf16_parent_filename(
	          file,
	          utf16_parent_filename,
	          512,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_parent_filename_is_set = result;

	/* Test error cases
	 */
	result = libvhdi_file_get_utf16_parent_filename(
	          NULL,
	          utf16_parent_filename,
	          512,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf16_parent_filename_is_set != 0 )
	{
		result = libvhdi_file_get_utf16_parent_filename(
		          file,
		          NULL,
		          512,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

		result = libvhdi_file_get_utf16_parent_filename(
		          file,
		          utf16_parent_filename,
		          0,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        VHDI_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );

		result = libvhdi_file_get_utf16_parent_filename(
		          file,
		          utf16_parent_filename,
		          (size_t) SSIZE_MAX + 1,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error    = NULL;
	libvhdi_file_t *file        = NULL;
	libvhdi_file_t *parent_file = NULL;
	system_character_t *source  = NULL;
	system_integer_t option     = 0;
	int result                  = 0;

	while( ( option = vhdi_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VHDI_TEST_FILE_VERBOSE )
	libvhdi_notify_set_verbose(
	 1 );
	libvhdi_notify_set_stream(
	 stderr,
	 NULL );
#endif

	VHDI_TEST_RUN(
	 "libvhdi_file_initialize",
	 vhdi_test_file_initialize );

	VHDI_TEST_RUN(
	 "libvhdi_file_free",
	 vhdi_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_open",
		 vhdi_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_open_wide",
		 vhdi_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVHDI_HAVE_BFIO )

		/* TODO add test for libvhdi_file_open_file_io_handle */

#endif /* defined( LIBVHDI_HAVE_BFIO ) */

		VHDI_TEST_RUN(
		 "libvhdi_file_close",
		 vhdi_test_file_close );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_open_close",
		 vhdi_test_file_open_close,
		 source );

		/* Initialize test
		 */
		result = vhdi_test_file_open_source(
		          &file,
		          source,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VHDI_TEST_ASSERT_IS_NOT_NULL(
	         "file",
	         file );

	        VHDI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = vhdi_test_file_open_parent_file(
		          &parent_file,
		          source,
		          file,
		          &error );

		VHDI_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        VHDI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_signal_abort",
		 vhdi_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

		/* TODO: add tests for libvhdi_internal_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_read_buffer",
		 vhdi_test_file_read_buffer,
		 file );

		/* TODO: add tests for libvhdi_file_read_buffer_at_offset */

		/* TODO: add tests for libvhdi_file_write_buffer */

		/* TODO: add tests for libvhdi_file_write_buffer_at_offset */

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_seek_offset",
		 vhdi_test_file_seek_offset,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_offset",
		 vhdi_test_file_get_offset,
		 file );

		/* TODO: add tests for libvhdi_file_set_parent_file */

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_media_size",
		 vhdi_test_file_get_media_size,
		 file );

		/* TODO: add tests for libvhdi_file_get_format_version */

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_disk_type",
		 vhdi_test_file_get_disk_type,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_identifier",
		 vhdi_test_file_get_identifier,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_parent_identifier",
		 vhdi_test_file_get_parent_identifier,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_utf8_parent_filename_size",
		 vhdi_test_file_get_utf8_parent_filename_size,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_utf8_parent_filename",
		 vhdi_test_file_get_utf8_parent_filename,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_utf16_parent_filename_size",
		 vhdi_test_file_get_utf16_parent_filename_size,
		 file );

		VHDI_TEST_RUN_WITH_ARGS(
		 "libvhdi_file_get_utf16_parent_filename",
		 vhdi_test_file_get_utf16_parent_filename,
		 file );

		/* Clean up
		 */
		result = vhdi_test_file_close_source(
		          &file,
		          &error );

		VHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VHDI_TEST_ASSERT_IS_NULL(
	         "file",
	         file );

	        VHDI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		if( parent_file != NULL )
		{
			result = vhdi_test_file_close_source(
			          &parent_file,
			          &error );

			VHDI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 0 );

		        VHDI_TEST_ASSERT_IS_NULL(
		         "error",
		         error );
		}
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		vhdi_test_file_close_source(
		 &file,
		 NULL );
	}
	if( parent_file != NULL )
	{
		vhdi_test_file_close_source(
		 &parent_file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

