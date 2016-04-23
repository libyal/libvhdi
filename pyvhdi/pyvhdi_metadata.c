/*
 * Metadata functions for the Python object definition of the libvhdi file
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvhdi_error.h"
#include "pyvhdi_file.h"
#include "pyvhdi_guid.h"
#include "pyvhdi_integer.h"
#include "pyvhdi_libcerror.h"
#include "pyvhdi_libclocale.h"
#include "pyvhdi_libcstring.h"
#include "pyvhdi_libvhdi.h"
#include "pyvhdi_python.h"
#include "pyvhdi_unused.h"

/* Retrieves the media size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvhdi_file_get_media_size(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments PYVHDI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvhdi_file_get_media_size";
	size64_t media_size      = 0;
	int result               = 0;

	PYVHDI_UNREFERENCED_PARAMETER( arguments )

	if( pyvhdi_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvhdi_file_get_media_size(
	          pyvhdi_file->file,
	          &media_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvhdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve media size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvhdi_integer_unsigned_new_from_64bit(
	                  (uint64_t) media_size );

	return( integer_object );
}

/* Retrieves the parent identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvhdi_file_get_parent_identifier(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments PYVHDI_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyvhdi_file_get_parent_identifier";
	int result               = 0;

	PYVHDI_UNREFERENCED_PARAMETER( arguments )

	if( pyvhdi_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvhdi_file_get_parent_identifier(
	          pyvhdi_file->file,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvhdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve parent identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pyvhdi_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the parent filename
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvhdi_file_get_parent_filename(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments PYVHDI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	const char *errors          = NULL;
	uint8_t *parent_filename    = NULL;
	static char *function       = "pyvhdi_file_get_parent_filename";
	size_t parent_filename_size = 0;
	int result                  = 0;

	PYVHDI_UNREFERENCED_PARAMETER( arguments )

	if( pyvhdi_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvhdi_file_get_utf8_parent_filename_size(
	          pyvhdi_file->file,
	          &parent_filename_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvhdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve parent filename size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( parent_filename_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	parent_filename = (uint8_t *) PyMem_Malloc(
	                               sizeof( uint8_t ) * parent_filename_size );

	if( parent_filename == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create parent filename.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvhdi_file_get_utf8_parent_filename(
		  pyvhdi_file->file,
		  parent_filename,
		  parent_filename_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvhdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve parent filename.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) parent_filename,
			 (Py_ssize_t) parent_filename_size - 1,
			 errors );

	PyMem_Free(
	 parent_filename );

	return( string_object );

on_error:
	if( parent_filename != NULL )
	{
		PyMem_Free(
		 parent_filename );
	}
	return( NULL );
}

