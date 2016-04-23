/*
 * Library seek testing program
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

#include <common.h>
#include <file_stream.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vhdi_test_libcerror.h"
#include "vhdi_test_libcpath.h"
#include "vhdi_test_libcstring.h"
#include "vhdi_test_libcsystem.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_unused.h"

/* Define to make vhdi_test_seek generate verbose output
#define VHDI_TEST_SEEK_VERBOSE
 */

/* Tests libvhdi_file_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_offset(
     libvhdi_file_t *file,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	off64_t result_offset     = 0;
	int result                = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libvhdi_file_seek_offset(
	                 file,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Tests seeking in a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_file(
     libvhdi_file_t *file,
     size64_t media_size )
{
	size64_t seek_offset = 0;
	int result           = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( media_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Media size exceeds maximum.\n" );

		return( -1 );
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	seek_offset = 0;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size>
	 * Expected result: <media_size>
	 */
	seek_offset = (off64_t) media_size;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size / 5>
	 * Expected result: <media_size / 5>
	 */
	seek_offset = (off64_t) ( media_size / 5 );

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size + 987>
	 * Expected result: <media_size + 987>
	 */
	seek_offset = (off64_t) ( media_size + 987 );

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	seek_offset = -987;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_SET,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <media_size + 987>
	 */
	seek_offset = 0;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_CUR,
	          (off64_t) ( media_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (media_size + 987)>
	 * Expected result: 0
	 */
	seek_offset = -1 * (off64_t) ( media_size + 987 );

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_CUR,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <media_size / 3>
	 * Expected result: <media_size / 3>
	 */
	seek_offset = (off64_t) ( media_size / 3 );

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_CUR,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	seek_offset = -2 * (off64_t) ( media_size / 3 );

	if( media_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (media_size / 3)>
		 * Expected result: 0
		 */
		result = vhdi_test_seek_offset(
		          file,
		          seek_offset,
		          SEEK_CUR,
		          0 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (media_size / 3)>
		 * Expected result: -1
		 */
		result = vhdi_test_seek_offset(
		          file,
		          seek_offset,
		          SEEK_CUR,
		          -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <media_size>
	 */
	seek_offset = 0;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_END,
	          (off64_t) media_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * media_size>
	 * Expected result: 0
	 */
	seek_offset = -1 * (off64_t) media_size;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_END,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (media_size / 4)>
	 * Expected result: <media_size - (media_size / 4)>
	 */
	seek_offset = (off64_t) ( media_size / 4 );

	result = vhdi_test_seek_offset(
	          file,
	          -1 * seek_offset,
	          SEEK_END,
	          (off64_t) media_size - seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <media_size + 542>
	 */
	seek_offset = 542;

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_END,
	          (off64_t) ( media_size + 542 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (media_size + 542)>
	 * Expected result: -1
	 */
	seek_offset = -1 * (off64_t) ( media_size + 542 );

	result = vhdi_test_seek_offset(
	          file,
	          seek_offset,
	          SEEK_END,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	result = vhdi_test_seek_offset(
	          file,
	          0,
	          88,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
}

/* Opens the parent input file
 * Returns 1 if successful, 0 if no parent or -1 on error
 */
int vhdi_test_seek_open_parent(
     libcstring_system_character_t *filename,
     libvhdi_file_t *file,
     libvhdi_file_t **parent_file,
     libcerror_error_t **error )
{
	uint8_t guid[ 16 ];

	libcstring_system_character_t *basename_end        = NULL;
	libcstring_system_character_t *parent_basename_end = NULL;
	libcstring_system_character_t *parent_filename     = NULL;
	libcstring_system_character_t *parent_path         = NULL;
	static char *function                              = "vhdi_test_seek_open_parent";
	size_t basename_length                             = 0;
	size_t filename_length                             = 0;
	size_t parent_basename_length                      = 0;
	size_t parent_filename_size                        = 0;
	size_t parent_path_size                            = 0;
	int entry_index                                    = 0;
	int result                                         = 0;

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
	filename_length = libcstring_system_string_length(
	                   filename );

	basename_end = libcstring_system_string_search_character_reverse(
	                filename,
	                (libcstring_system_character_t) LIBCPATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
	if( ( parent_filename_size > (size_t) SSIZE_MAX )
	 || ( ( sizeof( libcstring_system_character_t ) * parent_filename_size ) > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid parent filename size value exceeds maximum.",
		 function );

		goto on_error;
	}
	parent_filename = libcstring_system_string_allocate(
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
	parent_basename_end = libcstring_system_string_search_character_reverse(
	                       parent_filename,
	                       (libcstring_system_character_t) '\\',
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		if( libcpath_path_join_wide(
		     &parent_path,
		     &parent_path_size,
		     filename,
		     basename_length,
		     &( parent_filename[ parent_basename_length ] ),
		     parent_filename_size - ( parent_basename_length + 1 ),
		     error ) != 1 )
#else
		if( libcpath_path_join(
		     &parent_path,
		     &parent_path_size,
		     filename,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "%s: unable to open parent input file: %" PRIs_LIBCSTRING_SYSTEM ".",
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

/* Tests seeking in a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek(
     libcstring_system_character_t *source,
     libcerror_error_t **error )
{
	libvhdi_file_t *file        = NULL;
	libvhdi_file_t *parent_file = NULL;
	size64_t media_size         = 0;
	int result                  = 0;

	if( libvhdi_file_initialize(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvhdi_file_open_wide(
	     file,
	     source,
	     LIBVHDI_OPEN_READ,
	     error ) != 1 )
#else
	if( libvhdi_file_open(
	     file,
	     source,
	     LIBVHDI_OPEN_READ,
	     error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( vhdi_test_seek_open_parent(
	     source,
	     file,
	     &parent_file,
	     error ) == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to open parent file.\n" );

		goto on_error;
	}
	if( libvhdi_file_get_media_size(
	     file,
	     &media_size,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve media size.\n" );

		goto on_error;
	}
	result = vhdi_test_seek_file(
	          file,
	          media_size );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file.\n" );

		goto on_error;
	}
	if( libvhdi_file_close(
	     file,
	     error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file.\n" );

		goto on_error;
	}
	if( libvhdi_file_free(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	if( parent_file != NULL )
	{
		if( libvhdi_file_close(
		     parent_file,
		     error ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to close parent file.\n" );

			goto on_error;
		}
		if( libvhdi_file_free(
		     &parent_file,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free parent file.\n" );

			goto on_error;
		}
	}
	return( result );

on_error:
	if( file != NULL )
	{
		libvhdi_file_close(
		 file,
		 NULL );
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	if( parent_file != NULL )
	{
		libvhdi_file_close(
		 parent_file,
		 NULL );
		libvhdi_file_free(
		 &parent_file,
		 NULL );
	}
	return( -1 );
}

/* Tests seeking in a file without opening it
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_no_open(
     libcstring_system_character_t *source VHDI_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvhdi_file_t *file  = NULL;
	off64_t result_offset = 0;
	int result            = 0;

	VHDI_TEST_UNREFERENCED_PARAMETER( source );

	if( libvhdi_file_initialize(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Testing seek without open: \t" );

	result_offset = libvhdi_file_seek_offset(
	                 file,
	                 0,
	                 SEEK_SET,
	                 error );

	if( result_offset == -1 )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( ( error != NULL )
	 && ( *error != NULL ) )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 *error,
			 stderr );
		}
		libcerror_error_free(
		 error );
	}
	if( libvhdi_file_free(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( result );

on_error:
	if( file != NULL )
	{
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error              = NULL;
	libcstring_system_character_t *source = NULL;
	libcstring_system_integer_t option    = 0;
	int result                            = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( VHDI_TEST_SEEK_VERBOSE )
	libvhdi_notify_set_verbose(
	 1 );
	libvhdi_notify_set_stream(
	 stderr,
	 NULL );
#endif
	if( vhdi_test_seek(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file.\n" );

		goto on_error;
	}
	if( vhdi_test_seek_no_open(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file without open.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

