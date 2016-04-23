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

#if !defined( _PYVHDI_METADATA_H )
#define _PYVHDI_METADATA_H

#include <common.h>
#include <types.h>

#include "pyvhdi_libvhdi.h"
#include "pyvhdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

PyObject *pyvhdi_file_get_media_size(
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

#endif /* !defined( _PYVHDI_METADATA_H ) */

