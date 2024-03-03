/*
 * Library metadata_table_header type test program
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

#include "vhdi_test_libcerror.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_macros.h"
#include "vhdi_test_memory.h"
#include "vhdi_test_unused.h"

#include "../libvhdi/libvhdi_metadata_table_header.h"

uint8_t vhdi_test_metadata_table_header_data1[ 32 ] = {
	0x6d, 0x65, 0x74, 0x61, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

/* Tests the libvhdi_metadata_table_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_metadata_table_header_initialize(
     void )
{
	libcerror_error_t *error                               = NULL;
	libvhdi_metadata_table_header_t *metadata_table_header = NULL;
	int result                                             = 0;

#if defined( HAVE_VHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests                        = 1;
	int number_of_memset_fail_tests                        = 1;
	int test_number                                        = 0;
#endif

	/* Test regular cases
	 */
	result = libvhdi_metadata_table_header_initialize(
	          &metadata_table_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "metadata_table_header",
	 metadata_table_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvhdi_metadata_table_header_free(
	          &metadata_table_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "metadata_table_header",
	 metadata_table_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvhdi_metadata_table_header_initialize(
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

	metadata_table_header = (libvhdi_metadata_table_header_t *) 0x12345678UL;

	result = libvhdi_metadata_table_header_initialize(
	          &metadata_table_header,
	          &error );

	metadata_table_header = NULL;

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
		/* Test libvhdi_metadata_table_header_initialize with malloc failing
		 */
		vhdi_test_malloc_attempts_before_fail = test_number;

		result = libvhdi_metadata_table_header_initialize(
		          &metadata_table_header,
		          &error );

		if( vhdi_test_malloc_attempts_before_fail != -1 )
		{
			vhdi_test_malloc_attempts_before_fail = -1;

			if( metadata_table_header != NULL )
			{
				libvhdi_metadata_table_header_free(
				 &metadata_table_header,
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
			 "metadata_table_header",
			 metadata_table_header );

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
		/* Test libvhdi_metadata_table_header_initialize with memset failing
		 */
		vhdi_test_memset_attempts_before_fail = test_number;

		result = libvhdi_metadata_table_header_initialize(
		          &metadata_table_header,
		          &error );

		if( vhdi_test_memset_attempts_before_fail != -1 )
		{
			vhdi_test_memset_attempts_before_fail = -1;

			if( metadata_table_header != NULL )
			{
				libvhdi_metadata_table_header_free(
				 &metadata_table_header,
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
			 "metadata_table_header",
			 metadata_table_header );

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
	if( metadata_table_header != NULL )
	{
		libvhdi_metadata_table_header_free(
		 &metadata_table_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvhdi_metadata_table_header_free function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_metadata_table_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvhdi_metadata_table_header_free(
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

/* Tests the libvhdi_metadata_table_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int vhdi_test_metadata_table_header_read_data(
     void )
{
	libcerror_error_t *error                               = NULL;
	libvhdi_metadata_table_header_t *metadata_table_header = NULL;
	int result                                             = 0;

	/* Initialize test
	 */
	result = libvhdi_metadata_table_header_initialize(
	          &metadata_table_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NOT_NULL(
	 "metadata_table_header",
	 metadata_table_header );

	VHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvhdi_metadata_table_header_read_data(
	          metadata_table_header,
	          vhdi_test_metadata_table_header_data1,
	          32,
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
	result = libvhdi_metadata_table_header_read_data(
	          NULL,
	          vhdi_test_metadata_table_header_data1,
	          32,
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

	result = libvhdi_metadata_table_header_read_data(
	          metadata_table_header,
	          NULL,
	          32,
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

	result = libvhdi_metadata_table_header_read_data(
	          metadata_table_header,
	          vhdi_test_metadata_table_header_data1,
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

	result = libvhdi_metadata_table_header_read_data(
	          metadata_table_header,
	          vhdi_test_metadata_table_header_data1,
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

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint32_little_endian(
	 vhdi_test_metadata_table_header_data1,
	 0xffffffffUL );

	result = libvhdi_metadata_table_header_read_data(
	          metadata_table_header,
	          vhdi_test_metadata_table_header_data1,
	          32,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 vhdi_test_metadata_table_header_data1,
	 0x69676572UL );

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
	result = libvhdi_metadata_table_header_free(
	          &metadata_table_header,
	          &error );

	VHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VHDI_TEST_ASSERT_IS_NULL(
	 "metadata_table_header",
	 metadata_table_header );

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
	if( metadata_table_header != NULL )
	{
		libvhdi_metadata_table_header_free(
		 &metadata_table_header,
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
	 "libvhdi_metadata_table_header_initialize",
	 vhdi_test_metadata_table_header_initialize );

	VHDI_TEST_RUN(
	 "libvhdi_metadata_table_header_free",
	 vhdi_test_metadata_table_header_free );

	VHDI_TEST_RUN(
	 "libvhdi_metadata_table_header_read_data",
	 vhdi_test_metadata_table_header_read_data );

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVHDI_DLL_IMPORT ) */
}

