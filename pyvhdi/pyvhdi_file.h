/*
 * Python object wrapper of libvhdi_file_t
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

#if !defined( _PYVHDI_FILE_H )
#define _PYVHDI_FILE_H

#include <common.h>
#include <types.h>

#include "pyvhdi_libbfio.h"
#include "pyvhdi_libvhdi.h"
#include "pyvhdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvhdi_file pyvhdi_file_t;

struct pyvhdi_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvhdi file
	 */
	libvhdi_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The parent file
	 */
	pyvhdi_file_t *parent_file;
};

extern PyMethodDef pyvhdi_file_object_methods[];
extern PyTypeObject pyvhdi_file_type_object;

int pyvhdi_file_init(
     pyvhdi_file_t *pyvhdi_file );

void pyvhdi_file_free(
      pyvhdi_file_t *pyvhdi_file );

PyObject *pyvhdi_file_signal_abort(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_open(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvhdi_file_open_file_object(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvhdi_file_close(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_read_buffer(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvhdi_file_read_buffer_at_offset(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvhdi_file_seek_offset(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvhdi_file_get_offset(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_set_parent(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvhdi_file_get_format_version(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_get_disk_type(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_get_media_size(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_get_bytes_per_sector(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_get_identifier(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_get_parent_identifier(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

PyObject *pyvhdi_file_get_parent_filename(
           pyvhdi_file_t *pyvhdi_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVHDI_FILE_H ) */

