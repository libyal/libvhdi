/*
 * Library dynamic_disk_header type test program
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
#include <byte_stream.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vhdi_test_functions.h"
#include "vhdi_test_libbfio.h"
#include "vhdi_test_libcerror.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_macros.h"
#include "vhdi_test_memory.h"
#include "vhdi_test_unused.h"

#include "../libvhdi/libvhdi_dynamic_disk_header.h"

uint8_t vhdi_test_dynamic_disk_header_data1[ 1024 ] = {
	0x63, 0x78, 0x73, 0x70, 0x61, 0x72, 0x73, 0x65, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x20, 0x00, 0x00, 0xff, 0xff, 0xe1, 0xc1, 0xd4, 0x9c, 0x5c, 0x80, 0x35, 0x0a, 0x4a, 0x89,
	0x89, 0x8a, 0x5a, 0xd6, 0xd1, 0x0f, 0x65, 0x78, 0x19, 0x22, 0x07, 0x7c, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x64, 0x00, 0x79, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x69, 0x00, 0x63, 0x00, 0x2e,
	0x00, 0x76, 0x00, 0x68, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x57, 0x32, 0x6b, 0x75, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x57, 0x32, 0x72, 0x75, 0x00, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
	0x57, 0x69, 0x32, 0x6b, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x57, 0x69, 0x32, 0x72, 0x00, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

/* Tests the libvhdi_dynamic_disk_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_initialize(
     void )
{
	libcerror_error_t *error                           = NULL;
	libvhdi_dynamic_disk_header_t *dynamic_disk_header = NULL;
	int result                                         = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests                    = 1;
	int number_of_memset_fail_tests                    = 1;
	int test_number                                    = 0;
#endif

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_initialize(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_dynamic_disk_header_free(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_dynamic_disk_header_initialize(
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

	dynamic_disk_header = (libvhdi_dynamic_disk_header_t *) 0x12345678UL;

	result = libvhdi_dynamic_disk_header_initialize(
	          &dynamic_disk_header,
	          &error );

	dynamic_disk_header = NULL;

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
		/* Test libvhdi_dynamic_disk_header_initialize with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_dynamic_disk_header_initialize(
		          &dynamic_disk_header,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;

			if( dynamic_disk_header != NULL )
			{
				libvhdi_dynamic_disk_header_free(
				 &dynamic_disk_header,
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
			 "dynamic_disk_header",
			 dynamic_disk_header );

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
		/* Test libvhdi_dynamic_disk_header_initialize with memset failing
		 */
		vhdi_test_memset_attempts_before_fail = test_number;

		result = libvhdi_dynamic_disk_header_initialize(
		          &dynamic_disk_header,
		          &error );

		if( vhdi_test_memset_attempts_before_fail != -1 )
		{
			vhdi_test_memset_attempts_before_fail = -1;

			if( dynamic_disk_header != NULL )
			{
				libvhdi_dynamic_disk_header_free(
				 &dynamic_disk_header,
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
			 "dynamic_disk_header",
			 dynamic_disk_header );

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
	if( dynamic_disk_header != NULL )
	{
		libvhdi_dynamic_disk_header_free(
		 &dynamic_disk_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_dynamic_disk_header_free function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_dynamic_disk_header_free(
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

/* Tests the libvhdi_dynamic_disk_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_read_data(
     void )
{
	libcerror_error_t *error                           = NULL;
	libvhdi_dynamic_disk_header_t *dynamic_disk_header = NULL;
	int result                                         = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests                    = 1;
	int number_of_memcpy_fail_tests                    = 2;
	int test_number                                    = 0;
#endif

	/* Initialize test
	 */
	result = libvhdi_dynamic_disk_header_initialize(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          vhdi_test_dynamic_disk_header_data1,
	          1024,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvhdi_dynamic_disk_header_free(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libvhdi_dynamic_disk_header_initialize(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_dynamic_disk_header_read_data(
	          NULL,
	          vhdi_test_dynamic_disk_header_data1,
	          1024,
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

	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          NULL,
	          1024,
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

	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          vhdi_test_dynamic_disk_header_data1,
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

	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          vhdi_test_dynamic_disk_header_data1,
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

#if defined( HAVE_VHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvhdi_dynamic_disk_header_read_data with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_dynamic_disk_header_read_data(
		          dynamic_disk_header,
		          vhdi_test_dynamic_disk_header_data1,
		          1024,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;
		}
		else
		{
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
	}
	for( test_number = 0;
	     test_number < number_of_memcpy_fail_tests;
	     test_number++ )
	{
		/* Test libvhdi_dynamic_disk_header_read_data with memcpy failing
		 */
		vhdi_test_memcpy_attempts_before_fail = test_number;

		result = libvhdi_dynamic_disk_header_read_data(
		          dynamic_disk_header,
		          vhdi_test_dynamic_disk_header_data1,
		          1024,
		          &error );

		if( vhdi_test_memcpy_attempts_before_fail != -1 )
		{
			vhdi_test_memcpy_attempts_before_fail = -1;
		}
		else
		{
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
	}
#endif /* defined( HAVE_VHDI_TEST_MEMORY ) */

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint64_big_endian(
	 vhdi_test_dynamic_disk_header_data1,
	 0xffffffffffffffffUL );

	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          vhdi_test_dynamic_disk_header_data1,
	          1024,
	          &error );

	byte_stream_copy_from_uint64_big_endian(
	 vhdi_test_dynamic_disk_header_data1,
	 0x6378737061727365UL );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case where format version is invalid
	 */
	byte_stream_copy_from_uint32_big_endian(
	 &( vhdi_test_dynamic_disk_header_data1[ 24 ] ),
	 0xffffffffUL );

	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          vhdi_test_dynamic_disk_header_data1,
	          1024,
	          &error );

	byte_stream_copy_from_uint32_big_endian(
	 &( vhdi_test_dynamic_disk_header_data1[ 24 ] ),
	 0x00010000UL );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case where block size is invalid
	 */
/* TODO implement */

	/* Clean up
	 */
	result = libvhdi_dynamic_disk_header_free(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

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
	if( dynamic_disk_header != NULL )
	{
		libvhdi_dynamic_disk_header_free(
		 &dynamic_disk_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_dynamic_disk_header_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle                   = NULL;
	libcerror_error_t *error                           = NULL;
	libvhdi_dynamic_disk_header_t *dynamic_disk_header = NULL;
	int result                                         = 0;

	/* Initialize test
	 */
	result = libvhdi_dynamic_disk_header_initialize(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = vhdi_test_open_file_io_handle(
	          &file_io_handle,
	          vhdi_test_dynamic_disk_header_data1,
	          1024,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_read_file_io_handle(
	          dynamic_disk_header,
	          file_io_handle,
	          0,
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
	result = libvhdi_dynamic_disk_header_read_file_io_handle(
	          NULL,
	          file_io_handle,
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

	result = libvhdi_dynamic_disk_header_read_file_io_handle(
	          dynamic_disk_header,
	          NULL,
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

	result = libvhdi_dynamic_disk_header_read_file_io_handle(
	          dynamic_disk_header,
	          file_io_handle,
	          -1,
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

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint64_big_endian(
	 vhdi_test_dynamic_disk_header_data1,
	 0xffffffffffffffffUL );

	result = libvhdi_dynamic_disk_header_read_file_io_handle(
	          dynamic_disk_header,
	          file_io_handle,
	          0,
	          &error );

	byte_stream_copy_from_uint64_big_endian(
	 vhdi_test_dynamic_disk_header_data1,
	 0x6378737061727365UL );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up file IO handle
	 */
	result = vhdi_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = vhdi_test_open_file_io_handle(
	          &file_io_handle,
	          vhdi_test_dynamic_disk_header_data1,
	          8,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_dynamic_disk_header_read_file_io_handle(
	          dynamic_disk_header,
	          file_io_handle,
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

	result = vhdi_test_close_file_io_handle(
	          &file_io_handle,
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
	result = libvhdi_dynamic_disk_header_free(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( dynamic_disk_header != NULL )
	{
		libvhdi_dynamic_disk_header_free(
		 &dynamic_disk_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_dynamic_disk_header_get_parent_identifier function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_get_parent_identifier(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_get_parent_identifier(
	          dynamic_disk_header,
	          guid_data,
	          16,
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
	result = libvhdi_dynamic_disk_header_get_parent_identifier(
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

	result = libvhdi_dynamic_disk_header_get_parent_identifier(
	          dynamic_disk_header,
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

	result = libvhdi_dynamic_disk_header_get_parent_identifier(
	          dynamic_disk_header,
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

	result = libvhdi_dynamic_disk_header_get_parent_identifier(
	          dynamic_disk_header,
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

#if defined( HAVE_VHDI_TEST_MEMORY )

	/* Test libvhdi_dynamic_disk_header_get_parent_identifier with memcpy failing
	 */
	vhdi_test_memcpy_attempts_before_fail = 0;

	result = libvhdi_dynamic_disk_header_get_parent_identifier(
	          dynamic_disk_header,
	          guid_data,
	          16,
	          &error );

	if( vhdi_test_memcpy_attempts_before_fail != -1 )
	{
		vhdi_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_VHDI_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvhdi_dynamic_disk_header_get_utf8_parent_filename_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_get_utf8_parent_filename_size(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header )
{
	libcerror_error_t *error             = NULL;
	size_t utf8_parent_filename_size     = 0;
	int result                           = 0;
	int utf8_parent_filename_size_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_get_utf8_parent_filename_size(
	          dynamic_disk_header,
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
	result = libvhdi_dynamic_disk_header_get_utf8_parent_filename_size(
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
		result = libvhdi_dynamic_disk_header_get_utf8_parent_filename_size(
		          dynamic_disk_header,
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

/* Tests the libvhdi_dynamic_disk_header_get_utf8_parent_filename function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_get_utf8_parent_filename(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header )
{
	uint8_t utf8_parent_filename[ 512 ];

	libcerror_error_t *error        = NULL;
	int result                      = 0;
	int utf8_parent_filename_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_get_utf8_parent_filename(
	          dynamic_disk_header,
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
	result = libvhdi_dynamic_disk_header_get_utf8_parent_filename(
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
		result = libvhdi_dynamic_disk_header_get_utf8_parent_filename(
		          dynamic_disk_header,
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

		result = libvhdi_dynamic_disk_header_get_utf8_parent_filename(
		          dynamic_disk_header,
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

		result = libvhdi_dynamic_disk_header_get_utf8_parent_filename(
		          dynamic_disk_header,
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

/* Tests the libvhdi_dynamic_disk_header_get_utf16_parent_filename_size function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_get_utf16_parent_filename_size(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header )
{
	libcerror_error_t *error              = NULL;
	size_t utf16_parent_filename_size     = 0;
	int result                            = 0;
	int utf16_parent_filename_size_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_get_utf16_parent_filename_size(
	          dynamic_disk_header,
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
	result = libvhdi_dynamic_disk_header_get_utf16_parent_filename_size(
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
		result = libvhdi_dynamic_disk_header_get_utf16_parent_filename_size(
		          dynamic_disk_header,
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

/* Tests the libvhdi_dynamic_disk_header_get_utf16_parent_filename function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_dynamic_disk_header_get_utf16_parent_filename(
     libvhdi_dynamic_disk_header_t *dynamic_disk_header )
{
	uint16_t utf16_parent_filename[ 512 ];

	libcerror_error_t *error         = NULL;
	int result                       = 0;
	int utf16_parent_filename_is_set = 0;

	/* Test regular cases
	 */
	result = libvhdi_dynamic_disk_header_get_utf16_parent_filename(
	          dynamic_disk_header,
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
	result = libvhdi_dynamic_disk_header_get_utf16_parent_filename(
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
		result = libvhdi_dynamic_disk_header_get_utf16_parent_filename(
		          dynamic_disk_header,
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

		result = libvhdi_dynamic_disk_header_get_utf16_parent_filename(
		          dynamic_disk_header,
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

		result = libvhdi_dynamic_disk_header_get_utf16_parent_filename(
		          dynamic_disk_header,
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

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */

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
#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	libcerror_error_t *error                           = NULL;
	libvhdi_dynamic_disk_header_t *dynamic_disk_header = NULL;
	int result                                         = 0;

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */

	VHDI_TEST_UNREFERENCED_PARAMETER( argc )
	VHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

	VHDI_TEST_RUN(
	 "libvhdi_dynamic_disk_header_initialize",
	 vhdi_test_dynamic_disk_header_initialize );

	VHDI_TEST_RUN(
	 "libvhdi_dynamic_disk_header_free",
	 vhdi_test_dynamic_disk_header_free );

	VHDI_TEST_RUN(
	 "libvhdi_dynamic_disk_header_read_data",
	 vhdi_test_dynamic_disk_header_read_data );

	VHDI_TEST_RUN(
	 "libvhdi_dynamic_disk_header_read_file_io_handle",
	 vhdi_test_dynamic_disk_header_read_file_io_handle );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize dynamic_disk_header for tests
	 */
	result = libvhdi_dynamic_disk_header_initialize(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_dynamic_disk_header_read_data(
	          dynamic_disk_header,
	          vhdi_test_dynamic_disk_header_data1,
	          1024,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Run tests
	 */
	VHDI_TEST_RUN_WITH_ARGS(
	 "libvhdi_dynamic_disk_header_get_parent_identifier",
	 vhdi_test_dynamic_disk_header_get_parent_identifier,
	 dynamic_disk_header );

	VHDI_TEST_RUN_WITH_ARGS(
	 "libvhdi_dynamic_disk_header_get_utf8_parent_filename_size",
	 vhdi_test_dynamic_disk_header_get_utf8_parent_filename_size,
	 dynamic_disk_header );

	VHDI_TEST_RUN_WITH_ARGS(
	 "libvhdi_dynamic_disk_header_get_utf8_parent_filename",
	 vhdi_test_dynamic_disk_header_get_utf8_parent_filename,
	 dynamic_disk_header );

	VHDI_TEST_RUN_WITH_ARGS(
	 "libvhdi_dynamic_disk_header_get_utf16_parent_filename_size",
	 vhdi_test_dynamic_disk_header_get_utf16_parent_filename_size,
	 dynamic_disk_header );

	VHDI_TEST_RUN_WITH_ARGS(
	 "libvhdi_dynamic_disk_header_get_utf16_parent_filename",
	 vhdi_test_dynamic_disk_header_get_utf16_parent_filename,
	 dynamic_disk_header );

	/* Clean up
	 */
	result = libvhdi_dynamic_disk_header_free(
	          &dynamic_disk_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "dynamic_disk_header",
	 dynamic_disk_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

on_error:
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( dynamic_disk_header != NULL )
	{
		libvhdi_dynamic_disk_header_free(
		 &dynamic_disk_header,
		 NULL );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */
}

