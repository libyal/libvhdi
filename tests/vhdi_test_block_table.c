/*
 * Library block_table type test program
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

#include "../libvhdi/libvhdi_block_table.h"

#if defined( __GNUC__ )

/* Tests the libvhdi_block_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_block_table_initialize(
     void )
{
	libcerror_error_t *error           = NULL;
	libvhdi_block_table_t *block_table = NULL;
	int result                         = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests    = 1;
	int number_of_memset_fail_tests    = 1;
	int test_number                    = 0;
#endif

	/* Test regular cases
	 */
	result = libvhdi_block_table_initialize(
	          &block_table,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NOT_NULL(
         "block_table",
         block_table );

        VHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libvhdi_block_table_free(
	          &block_table,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VHDI_TEST_ASSERT_IS_NULL(
         "block_table",
         block_table );

        VHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libvhdi_block_table_initialize(
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

	block_table = (libvhdi_block_table_t *) 0x12345678UL;

	result = libvhdi_block_table_initialize(
	          &block_table,
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

	block_table = NULL;

#if defined( HAVE_VHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvhdi_block_table_initialize with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_block_table_initialize(
		          &block_table,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;

			if( block_table != NULL )
			{
				libvhdi_block_table_free(
				 &block_table,
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
			 "block_table",
			 block_table );

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
		/* Test libvhdi_block_table_initialize with memset failing
		 */
		vhdi_test_memset_attempts_before_fail = test_number;

		result = libvhdi_block_table_initialize(
		          &block_table,
		          &error );

		if( vhdi_test_memset_attempts_before_fail != -1 )
		{
			vhdi_test_memset_attempts_before_fail = -1;

			if( block_table != NULL )
			{
				libvhdi_block_table_free(
				 &block_table,
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
			 "block_table",
			 block_table );

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
	if( block_table != NULL )
	{
		libvhdi_block_table_free(
		 &block_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_block_table_free function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_block_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_block_table_free(
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

/* Tests the libvhdi_block_table_get_number_of_references function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_block_table_get_number_of_references(
     void )
{
	libcerror_error_t *error           = NULL;
	libvhdi_block_table_t *block_table = NULL;
	int number_of_references           = 0;
	int number_of_references_is_set    = 0;
	int result                         = 0;

	/* Initialize test
	 */
	result = libvhdi_block_table_initialize(
	          &block_table,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "block_table",
	 block_table );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_block_table_get_number_of_references(
	          block_table,
	          &number_of_references,
	          &error );

	VHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_references_is_set = result;

	/* Test error cases
	 */
	result = libvhdi_block_table_get_number_of_references(
	          NULL,
	          &number_of_references,
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

	if( number_of_references_is_set != 0 )
	{
		result = libvhdi_block_table_get_number_of_references(
		          block_table,
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
	result = libvhdi_block_table_free(
	          &block_table,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "block_table",
	 block_table );

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
	if( block_table != NULL )
	{
		libvhdi_block_table_free(
		 &block_table,
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
	 "libvhdi_block_table_initialize",
	 vhdi_test_block_table_initialize );

	VHDI_TEST_RUN(
	 "libvhdi_block_table_free",
	 vhdi_test_block_table_free );

	VHDI_TEST_RUN(
	 "libvhdi_block_table_get_number_of_references",
	 vhdi_test_block_table_get_number_of_references );

	/* TODO: add tests for libvhdi_block_table_get_reference_by_index */

	/* TODO: add tests for libvhdi_block_table_read */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

