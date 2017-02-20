/*
 * Library read testing program
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

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vhdi_test_libcerror.h"
#include "vhdi_test_libcpath.h"
#include "vhdi_test_libcsystem.h"
#include "vhdi_test_libcthreads.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_unused.h"

/* Define to make vhdi_test_read generate verbose output
#define VHDI_TEST_READ_VERBOSE
 */

#define VHDI_TEST_READ_BUFFER_SIZE		4096
#define VHDI_TEST_READ_NUMBER_OF_THREADS	4

/* Tests libvhdi_file_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_offset(
     libvhdi_file_t *file,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	int result               = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	result_offset = libvhdi_file_seek_offset(
	                 file,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
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

/* Tests libvhdi_file_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_read_buffer(
     libvhdi_file_t *file,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ VHDI_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = VHDI_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libvhdi_file_read_buffer(
			      file,
			      buffer,
			      read_size,
			      &error );

		if( read_count <= 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
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

/* Tests libvhdi_file_read_buffer_at_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_read_buffer_at_offset(
     libvhdi_file_t *file,
     off64_t input_offset,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	uint8_t buffer[ VHDI_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " and size: %" PRIu64 "\t",
	 input_offset,
	 input_size );

	while( remaining_size > 0 )
	{
		read_size = VHDI_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libvhdi_file_read_buffer_at_offset(
			      file,
			      buffer,
			      read_size,
			      input_offset,
			      &error );

		if( read_count <= 0 )
		{
			break;
		}
		input_offset   += (size64_t) read_count;
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( libvhdi_file_get_offset(
	     file,
	     &result_offset,
	     &error ) != 1 )
	{
		result = -1;
	}
	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
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

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_offset_and_read_buffer(
     libvhdi_file_t *file,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	const char *whence_string = NULL;
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
	 "Testing reading buffer at offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = vhdi_test_seek_offset(
	          file,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = vhdi_test_read_buffer(
				  file,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
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

	return( result );
}

/* Tests reading data from a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_read_from_file(
     libvhdi_file_t *file,
     size64_t media_size )
{
	off64_t read_offset = 0;
	size64_t read_size  = 0;
	int result          = 0;

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
	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <media_size>
	 * Expected result: offset: 0 size: <media_size>
	 */
	read_offset = 0;
	read_size   = media_size;

	result = vhdi_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	result = vhdi_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <media_size / 7> size: <media_size / 2>
	 * Expected result: offset: <media_size / 7> size: <media_size / 2>
	 */
	read_offset = (off64_t) ( media_size / 7 );
	read_size   = media_size / 2;

	result = vhdi_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	result = vhdi_test_seek_offset_and_read_buffer(
	          file,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 2: test read beyond media size
	 */
	read_offset = (off64_t) ( media_size - 1024 );
	read_size   = 4096;

	if( media_size < 1024 )
	{
		/* Test: offset: <media_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = vhdi_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
		result = vhdi_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: offset: <media_size - 1024> size: 4096
		 * Expected result: offset: <media_size - 1024> size: 1024
		 */
		result = vhdi_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          read_offset,
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			return( result );
		}
		result = vhdi_test_seek_offset_and_read_buffer(
		          file,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          read_offset,
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	/* Case 3: test buffer at offset read
	 */

	/* Test: offset: <media_size / 7> size: <media_size / 2>
	 * Expected result: offset: < ( media_size / 7 ) + ( media_size / 2 ) > size: <media_size / 2>
	 */
	read_offset = (off64_t) ( media_size / 7 );
	read_size   = media_size / 2;

	result = vhdi_test_read_buffer_at_offset(
	          file,
	          read_offset,
	          read_size,
	          read_offset + read_size,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	result = vhdi_test_read_buffer_at_offset(
	          file,
	          read_offset,
	          read_size,
	          read_offset + read_size,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	return( 1 );
}

/* Opens the parent input file
 * Returns 1 if successful, 0 if no parent or -1 on error
 */
int vhdi_test_read_open_parent(
     system_character_t *filename,
     libvhdi_file_t *file,
     libvhdi_file_t **parent_file,
     libcerror_error_t **error )
{
	uint8_t guid[ 16 ];

	system_character_t *basename_end        = NULL;
	system_character_t *parent_basename_end = NULL;
	system_character_t *parent_filename     = NULL;
	system_character_t *parent_path         = NULL;
	static char *function                   = "vhdi_test_read_open_parent";
	size_t basename_length                  = 0;
	size_t filename_length                  = 0;
	size_t parent_basename_length           = 0;
	size_t parent_filename_size             = 0;
	size_t parent_path_size                 = 0;
	int entry_index                         = 0;
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
	filename_length = system_string_length(
	                   filename );

	basename_end = system_string_search_character_reverse(
	                filename,
	                (system_character_t) LIBCPATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename );
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
	if( ( parent_filename_size > (size_t) SSIZE_MAX )
	 || ( ( sizeof( system_character_t ) * parent_filename_size ) > (size_t) SSIZE_MAX ) )
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

/* Tests reading a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_read(
     system_character_t *source,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	if( vhdi_test_read_open_parent(
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
	fprintf(
	 stdout,
	 "Media size: %" PRIu64 " bytes\n",
	 media_size );

	result = vhdi_test_read_from_file(
	          file,
	          media_size );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to read from file.\n" );

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

#if defined( HAVE_MULTI_THREAD_SUPPORT )

/* The thread pool callback function
 * Returns 1 if successful or -1 on error
 */
int vhdi_test_read_callback_function(
     libvhdi_file_t *file,
     void *arguments VHDI_TEST_ATTRIBUTE_UNUSED )
{
	uint8_t buffer[ VHDI_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "vhdi_test_read_callback_function";
	size_t read_size         = VHDI_TEST_READ_BUFFER_SIZE;
	ssize_t read_count       = 0;
	int number_of_iterations = 3;
	int result               = 0;

	VHDI_TEST_UNREFERENCED_PARAMETER( arguments )

	if( file == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		goto on_error;
	}
	while( number_of_iterations > 0 )
	{
		read_count = libvhdi_file_read_buffer(
		              file,
		              buffer,
		              read_size,
		              &error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read from file.",
			 function );

			goto on_error;
		}
		number_of_iterations--;

		if( number_of_iterations > 0 )
		{
			if( libvhdi_file_seek_offset(
			     file,
			     (off64_t) -read_size,
			     SEEK_CUR,
			     &error ) == -1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_SEEK_FAILED,
				 "%s: unable to seek in file.",
				 function );

				goto on_error;
			}
		}
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );

		libcerror_error_free(
		 &error );
	}
	return( -1 );
}

/* Tests reading data from a file in multiple threads
 * This test requires multi-threading support
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_read_from_file_multi_thread(
     libvhdi_file_t *file,
     size64_t media_size,
     int number_of_threads )
{
	libcerror_error_t *error               = NULL;
	libcthreads_thread_pool_t *thread_pool = NULL;
	static char *function                  = "vhdi_test_read_from_file_multi_thread";
	off64_t expected_offset                = 0;
	off64_t result_offset                  = 0;
	int iteration                          = 0;
	int number_of_iterations               = 0;
	int result                             = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		goto on_error;
	}
	if( libvhdi_file_seek_offset(
	     file,
	     0,
	     SEEK_SET,
	     &error ) == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek in file.",
		 function );

		goto on_error;
	}
	if( number_of_threads > 1 )
	{
		number_of_iterations = number_of_threads * 32;

		expected_offset = (off64_t) number_of_iterations * VHDI_TEST_READ_BUFFER_SIZE;

		if( (size64_t) expected_offset > media_size )
		{
			expected_offset = media_size;

			number_of_iterations = media_size / VHDI_TEST_READ_BUFFER_SIZE;

			if( ( media_size % VHDI_TEST_READ_BUFFER_SIZE ) != 0 )
			{
				number_of_iterations += 1;
			}
		}
		if( libcthreads_thread_pool_create(
		     &thread_pool,
		     NULL,
		     number_of_threads,
		     number_of_iterations,
		     (int (*)(intptr_t *, void *)) &vhdi_test_read_callback_function,
		     NULL,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create thread pool.",
			 function );

			goto on_error;
		}
		for( iteration = 0;
		     iteration < number_of_iterations;
		     iteration++ )
		{
			if( libcthreads_thread_pool_push(
			     thread_pool,
			     (intptr_t *) file,
			     &error ) == -1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to push file onto queue.",
				 function );

				goto on_error;
			}
		}
		if( libcthreads_thread_pool_join(
		     &thread_pool,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to join thread pool.",
			 function );

			goto on_error;
		}
	}
	if( libvhdi_file_get_offset(
	     file,
	     &result_offset,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset.",
		 function );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Testing multi-threaded read buffer at offset: 0\t" );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
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

	return( result );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );

		libcerror_error_free(
		 &error );
	}
	if( thread_pool != NULL )
	{
		libcthreads_thread_pool_join(
		 &thread_pool,
		 NULL );
	}
	return( -1 );
}

/* Tests reading a file in multiple threads
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_read_multi_thread(
     system_character_t *source,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	if( vhdi_test_read_open_parent(
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
	fprintf(
	 stdout,
	 "Media size: %" PRIu64 " bytes\n",
	 media_size );

	result = vhdi_test_read_from_file_multi_thread(
	          file,
	          media_size,
	          VHDI_TEST_READ_NUMBER_OF_THREADS );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to read from file in multiple threads.\n" );

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

#endif /* defined( HAVE_MULTI_THREAD_SUPPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
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
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( VHDI_TEST_READ_VERBOSE )
	libvhdi_notify_set_verbose(
	 1 );
	libvhdi_notify_set_stream(
	 stderr,
	 NULL );
#endif
	if( vhdi_test_read(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read file.\n" );

		goto on_error;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( vhdi_test_read_multi_thread(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read file in multiple threads.\n" );

		goto on_error;
	}
#endif
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

