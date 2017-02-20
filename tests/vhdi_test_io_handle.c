/*
 * Library io_handle type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vhdi_test_libcerror.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_macros.h"
#include "vhdi_test_memory.h"
#include "vhdi_test_unused.h"

#include "../libvhdi/libvhdi_io_handle.h"

#if defined( __GNUC__ )

/* Tests the libvhdi_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvhdi_io_handle_t *io_handle  = NULL;
	int result                      = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NOT_NULL(
         "io_handle",
         io_handle );

        VHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NULL(
         "io_handle",
         io_handle );

        VHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libvhdi_io_handle_initialize(
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

	io_handle = (libvhdi_io_handle_t *) 0x12345678UL;

	result = libvhdi_io_handle_initialize(
	          &io_handle,
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

	io_handle = NULL;

#if defined( HAVE_VHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvhdi_io_handle_initialize with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_io_handle_initialize(
		          &io_handle,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libvhdi_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
		/* Test libvhdi_io_handle_initialize with memset failing
		 */
		vhdi_test_memset_attempts_before_fail = test_number;

		result = libvhdi_io_handle_initialize(
		          &io_handle,
		          &error );

		if( vhdi_test_memset_attempts_before_fail != -1 )
		{
			vhdi_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libvhdi_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_io_handle_free(
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

/* Tests the libvhdi_io_handle_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_get_identifier(
     void )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error       = NULL;
	libvhdi_io_handle_t *io_handle = NULL;
	int result                     = 0;

	/* Initialize test
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NOT_NULL(
         "io_handle",
         io_handle );

        VHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test regular cases
	 */
	result = libvhdi_io_handle_get_identifier(
	          io_handle,
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
	result = libvhdi_io_handle_get_identifier(
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

	result = libvhdi_io_handle_get_identifier(
	          io_handle,
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

	result = libvhdi_io_handle_get_identifier(
	          io_handle,
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

	result = libvhdi_io_handle_get_identifier(
	          io_handle,
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

	/* Clean up
	 */
	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NULL(
         "io_handle",
         io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_io_handle_get_parent_identifier function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_get_parent_identifier(
     void )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error       = NULL;
	libvhdi_io_handle_t *io_handle = NULL;
	int result                     = 0;

	/* Initialize test
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NOT_NULL(
         "io_handle",
         io_handle );

        VHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test regular cases
	 */
	result = libvhdi_io_handle_get_parent_identifier(
	          io_handle,
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
	result = libvhdi_io_handle_get_parent_identifier(
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

	result = libvhdi_io_handle_get_parent_identifier(
	          io_handle,
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

	result = libvhdi_io_handle_get_parent_identifier(
	          io_handle,
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

	result = libvhdi_io_handle_get_parent_identifier(
	          io_handle,
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

	/* Clean up
	 */
	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NULL(
         "io_handle",
         io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_io_handle_get_utf8_parent_filename_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_get_utf8_parent_filename_size(
     void )
{
	libcerror_error_t *error             = NULL;
	libvhdi_io_handle_t *io_handle       = NULL;
	size_t utf8_parent_filename_size     = 0;
	int result                           = 0;
	int utf8_parent_filename_size_is_set = 0;

	/* Initialize test
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_io_handle_get_utf8_parent_filename_size(
	          io_handle,
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
	result = libvhdi_io_handle_get_utf8_parent_filename_size(
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
		result = libvhdi_io_handle_get_utf8_parent_filename_size(
		          io_handle,
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
	/* Clean up
	 */
	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_io_handle_get_utf8_parent_filename function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_get_utf8_parent_filename(
     void )
{
	uint8_t utf8_parent_filename[ 512 ];

	libcerror_error_t *error        = NULL;
	libvhdi_io_handle_t *io_handle  = NULL;
	int result                      = 0;
	int utf8_parent_filename_is_set = 0;

	/* Initialize test
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_io_handle_get_utf8_parent_filename(
	          io_handle,
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
	result = libvhdi_io_handle_get_utf8_parent_filename(
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
		result = libvhdi_io_handle_get_utf8_parent_filename(
		          io_handle,
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

		result = libvhdi_io_handle_get_utf8_parent_filename(
		          io_handle,
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

		result = libvhdi_io_handle_get_utf8_parent_filename(
		          io_handle,
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
	/* Clean up
	 */
	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_io_handle_get_utf16_parent_filename_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_get_utf16_parent_filename_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libvhdi_io_handle_t *io_handle        = NULL;
	size_t utf16_parent_filename_size     = 0;
	int result                            = 0;
	int utf16_parent_filename_size_is_set = 0;

	/* Initialize test
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_io_handle_get_utf16_parent_filename_size(
	          io_handle,
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
	result = libvhdi_io_handle_get_utf16_parent_filename_size(
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
		result = libvhdi_io_handle_get_utf16_parent_filename_size(
		          io_handle,
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
	/* Clean up
	 */
	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_io_handle_get_utf16_parent_filename function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_io_handle_get_utf16_parent_filename(
     void )
{
	uint16_t utf16_parent_filename[ 512 ];

	libcerror_error_t *error         = NULL;
	libvhdi_io_handle_t *io_handle   = NULL;
	int result                       = 0;
	int utf16_parent_filename_is_set = 0;

	/* Initialize test
	 */
	result = libvhdi_io_handle_initialize(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_io_handle_get_utf16_parent_filename(
	          io_handle,
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
	result = libvhdi_io_handle_get_utf16_parent_filename(
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
		result = libvhdi_io_handle_get_utf16_parent_filename(
		          io_handle,
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

		result = libvhdi_io_handle_get_utf16_parent_filename(
		          io_handle,
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

		result = libvhdi_io_handle_get_utf16_parent_filename(
		          io_handle,
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
	/* Clean up
	 */
	result = libvhdi_io_handle_free(
	          &io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvhdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc VHDI_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] VHDI_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc VHDI_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] VHDI_TEST_ATTRIBUTE_UNUSED )
#endif
{
	VHDI_TEST_UNREFERENCED_PARAMETER( argc )
	VHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ )

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_initialize",
	 vhdi_test_io_handle_initialize );

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_free",
	 vhdi_test_io_handle_free );

	/* TODO: add tests for libvhdi_io_handle_clear */

	/* TODO: add tests for libvhdi_io_handle_read_file_footer */

	/* TODO: add tests for libvhdi_io_handle_read_dynamic_disk_header */

#ifdef TODO

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_get_identifier",
	 vhdi_test_io_handle_get_identifier );

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_get_parent_identifier",
	 vhdi_test_io_handle_get_parent_identifier );

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_get_utf8_parent_filename_size",
	 vhdi_test_io_handle_get_utf8_parent_filename_size );

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_get_utf8_parent_filename",
	 vhdi_test_io_handle_get_utf8_parent_filename );

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_get_utf16_parent_filename_size",
	 vhdi_test_io_handle_get_utf16_parent_filename_size );

	VHDI_TEST_RUN(
	 "libvhdi_io_handle_get_utf16_parent_filename",
	 vhdi_test_io_handle_get_utf16_parent_filename );

#endif /* TODO */

	/* TODO: add tests for libvhdi_io_handle_read_data_block */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

