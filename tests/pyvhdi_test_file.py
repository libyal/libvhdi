#!/usr/bin/env python
#
# Python-bindings file type test script
#
# Copyright (C) 2012-2018, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pyvhdi


class FileTypeTests(unittest.TestCase):
  """Tests the file type."""

  def test_open(self):
    """Tests the open function."""
    if not unittest.source:
      return

    vhdi_file = pyvhdi.file()

    vhdi_file.open(unittest.source)

    with self.assertRaises(IOError):
      vhdi_file.open(unittest.source)

    vhdi_file.close()

    with self.assertRaises(TypeError):
      vhdi_file.open(None)

    with self.assertRaises(ValueError):
      vhdi_file.open(unittest.source, mode="w")

  def test_open_file_object(self):
    """Tests the open_file_object function."""
    if not unittest.source:
      return

    file_object = open(unittest.source, "rb")

    vhdi_file = pyvhdi.file()

    vhdi_file.open_file_object(file_object)

    with self.assertRaises(IOError):
      vhdi_file.open_file_object(file_object)

    vhdi_file.close()

    # TODO: change IOError into TypeError
    with self.assertRaises(IOError):
      vhdi_file.open_file_object(None)

    with self.assertRaises(ValueError):
      vhdi_file.open_file_object(file_object, mode="w")

  def test_close(self):
    """Tests the close function."""
    if not unittest.source:
      return

    vhdi_file = pyvhdi.file()

    with self.assertRaises(IOError):
      vhdi_file.close()

  def test_open_close(self):
    """Tests the open and close functions."""
    if not unittest.source:
      return

    vhdi_file = pyvhdi.file()

    # Test open and close.
    vhdi_file.open(unittest.source)
    vhdi_file.close()

    # Test open and close a second time to validate clean up on close.
    vhdi_file.open(unittest.source)
    vhdi_file.close()

    file_object = open(unittest.source, "rb")

    # Test open_file_object and close.
    vhdi_file.open_file_object(file_object)
    vhdi_file.close()

    # Test open_file_object and close a second time to validate clean up on close.
    vhdi_file.open_file_object(file_object)
    vhdi_file.close()

    # Test open_file_object and close and dereferencing file_object.
    vhdi_file.open_file_object(file_object)
    del file_object
    vhdi_file.close()

  def test_read_buffer(self):
    """Tests the read_buffer function."""
    if not unittest.source:
      return

    vhdi_file = pyvhdi.file()

    vhdi_file.open(unittest.source)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      parent_filename = os.path.join(
        os.path.dirname(unittest.source), vhdi_file.parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    file_size = vhdi_file.get_media_size()

    # Test normal read.
    data = vhdi_file.read_buffer(size=4096)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(file_size, 4096))

    if file_size < 4096:
      data = vhdi_file.read_buffer()

      self.assertIsNotNone(data)
      self.assertEqual(len(data), file_size)

    # Test read beyond file size.
    if file_size > 16:
      vhdi_file.seek_offset(-16, os.SEEK_END)

      data = vhdi_file.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 16)

    with self.assertRaises(ValueError):
      vhdi_file.read_buffer(size=-1)

    vhdi_file.close()

    if vhdi_parent_file:
      vhdi_parent_file.close()

    # Test the read without open.
    with self.assertRaises(IOError):
      vhdi_file.read_buffer(size=4096)

  def test_read_buffer_file_object(self):
    """Tests the read_buffer function on a file-like object."""
    if not unittest.source:
      return

    file_object = open(unittest.source, "rb")

    vhdi_file = pyvhdi.file()

    vhdi_file.open_file_object(file_object)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      parent_filename = os.path.join(
        os.path.dirname(unittest.source), vhdi_file.parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    file_size = vhdi_file.get_media_size()

    # Test normal read.
    data = vhdi_file.read_buffer(size=4096)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(file_size, 4096))

    vhdi_file.close()

    if vhdi_parent_file:
      vhdi_parent_file.close()

  def test_read_buffer_at_offset(self):
    """Tests the read_buffer_at_offset function."""
    if not unittest.source:
      return

    vhdi_file = pyvhdi.file()

    vhdi_file.open(unittest.source)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      parent_filename = os.path.join(
        os.path.dirname(unittest.source), vhdi_file.parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    file_size = vhdi_file.get_media_size()

    # Test normal read.
    data = vhdi_file.read_buffer_at_offset(4096, 0)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(file_size, 4096))

    # Test read beyond file size.
    if file_size > 16:
      data = vhdi_file.read_buffer_at_offset(4096, file_size - 16)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 16)

    with self.assertRaises(ValueError):
      vhdi_file.read_buffer_at_offset(-1, 0)

    with self.assertRaises(ValueError):
      vhdi_file.read_buffer_at_offset(4096, -1)

    vhdi_file.close()

    if vhdi_parent_file:
      vhdi_parent_file.close()

    # Test the read without open.
    with self.assertRaises(IOError):
      vhdi_file.read_buffer_at_offset(4096, 0)

  def test_seek_offset(self):
    """Tests the seek_offset function."""
    if not unittest.source:
      return

    vhdi_file = pyvhdi.file()

    vhdi_file.open(unittest.source)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      parent_filename = os.path.join(
        os.path.dirname(unittest.source), vhdi_file.parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    file_size = vhdi_file.get_media_size()

    vhdi_file.seek_offset(16, os.SEEK_SET)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, 16)

    vhdi_file.seek_offset(16, os.SEEK_CUR)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, 32)

    vhdi_file.seek_offset(-16, os.SEEK_CUR)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, 16)

    vhdi_file.seek_offset(-16, os.SEEK_END)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, file_size - 16)

    vhdi_file.seek_offset(16, os.SEEK_END)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, file_size + 16)

    with self.assertRaises(IOError):
      vhdi_file.seek_offset(-1, os.SEEK_SET)

    with self.assertRaises(IOError):
      vhdi_file.seek_offset(-32 - file_size, os.SEEK_CUR)

    with self.assertRaises(IOError):
      vhdi_file.seek_offset(-32 - file_size, os.SEEK_END)

    with self.assertRaises(IOError):
      vhdi_file.seek_offset(0, -1)

    vhdi_file.close()

    if vhdi_parent_file:
      vhdi_parent_file.close()

    # Test the seek without open.
    with self.assertRaises(IOError):
      vhdi_file.seek_offset(16, os.SEEK_SET)


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="The path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
