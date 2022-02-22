/*
 * Library parent_locator_entry type test program
 *
 * Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
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

#include "vhdi_test_libcerror.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_macros.h"
#include "vhdi_test_memory.h"
#include "vhdi_test_unused.h"

#include "../libvhdi/libvhdi_parent_locator_entry.h"

uint8_t vhdi_test_parent_locator_entry_data1[ 12 ] = {
	0x50, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x4c, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

/* Tests the libvhdi_parent_locator_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_parent_locator_entry_initialize(
     void )
{
	libcerror_error_t *error                             = NULL;
	libvhdi_parent_locator_entry_t *parent_locator_entry = NULL;
	int result                                           = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests                      = 1;
	int number_of_memset_fail_tests                      = 1;
	int test_number                                      = 0;
#endif

	/* Test regular cases
	 */
	result = libvhdi_parent_locator_entry_initialize(
	          &parent_locator_entry,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "parent_locator_entry",
	 parent_locator_entry );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_parent_locator_entry_free(
	          &parent_locator_entry,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "parent_locator_entry",
	 parent_locator_entry );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_parent_locator_entry_initialize(
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

	parent_locator_entry = (libvhdi_parent_locator_entry_t *) 0x12345678UL;

	result = libvhdi_parent_locator_entry_initialize(
	          &parent_locator_entry,
	          &error );

	parent_locator_entry = NULL;

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
		/* Test libvhdi_parent_locator_entry_initialize with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_parent_locator_entry_initialize(
		          &parent_locator_entry,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;

			if( parent_locator_entry != NULL )
			{
				libvhdi_parent_locator_entry_free(
				 &parent_locator_entry,
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
			 "parent_locator_entry",
			 parent_locator_entry );

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
		/* Test libvhdi_parent_locator_entry_initialize with memset failing
		 */
		vhdi_test_memset_attempts_before_fail = test_number;

		result = libvhdi_parent_locator_entry_initialize(
		          &parent_locator_entry,
		          &error );

		if( vhdi_test_memset_attempts_before_fail != -1 )
		{
			vhdi_test_memset_attempts_before_fail = -1;

			if( parent_locator_entry != NULL )
			{
				libvhdi_parent_locator_entry_free(
				 &parent_locator_entry,
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
			 "parent_locator_entry",
			 parent_locator_entry );

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
	if( parent_locator_entry != NULL )
	{
		libvhdi_parent_locator_entry_free(
		 &parent_locator_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_parent_locator_entry_free function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_parent_locator_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_parent_locator_entry_free(
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

/* Tests the libvhdi_parent_locator_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_parent_locator_entry_read_data(
     void )
{
	libcerror_error_t *error                             = NULL;
	libvhdi_parent_locator_entry_t *parent_locator_entry = NULL;
	int result                                           = 0;

	/* Initialize test
	 */
	result = libvhdi_parent_locator_entry_initialize(
	          &parent_locator_entry,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "parent_locator_entry",
	 parent_locator_entry );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_parent_locator_entry_read_data(
	          parent_locator_entry,
	          vhdi_test_parent_locator_entry_data1,
	          12,
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
	result = libvhdi_parent_locator_entry_read_data(
	          NULL,
	          vhdi_test_parent_locator_entry_data1,
	          12,
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

	result = libvhdi_parent_locator_entry_read_data(
	          parent_locator_entry,
	          NULL,
	          12,
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

	result = libvhdi_parent_locator_entry_read_data(
	          parent_locator_entry,
	          vhdi_test_parent_locator_entry_data1,
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

	result = libvhdi_parent_locator_entry_read_data(
	          parent_locator_entry,
	          vhdi_test_parent_locator_entry_data1,
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

	/* Clean up
	 */
	result = libvhdi_parent_locator_entry_free(
	          &parent_locator_entry,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "parent_locator_entry",
	 parent_locator_entry );

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
	if( parent_locator_entry != NULL )
	{
		libvhdi_parent_locator_entry_free(
		 &parent_locator_entry,
		 NULL );
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
	VHDI_TEST_UNREFERENCED_PARAMETER( argc )
	VHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

	VHDI_TEST_RUN(
	 "libvhdi_parent_locator_entry_initialize",
	 vhdi_test_parent_locator_entry_initialize );

	VHDI_TEST_RUN(
	 "libvhdi_parent_locator_entry_free",
	 vhdi_test_parent_locator_entry_free );

	VHDI_TEST_RUN(
	 "libvhdi_parent_locator_entry_read_data",
	 vhdi_test_parent_locator_entry_read_data );

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */
}

