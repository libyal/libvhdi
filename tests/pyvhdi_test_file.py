#!/usr/bin/env python
#
# Python-bindings file type test script
#
# Copyright (C) 2012-2024, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import random
import sys
import unittest

import pyvhdi


class FileTypeTests(unittest.TestCase):
  """Tests the file type."""

  def test_signal_abort(self):
    """Tests the signal_abort function."""
    vhdi_file = pyvhdi.file()

    vhdi_file.signal_abort()

  def test_open(self):
    """Tests the open function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    with self.assertRaises(IOError):
      vhdi_file.open(test_source)

    vhdi_file.close()

    with self.assertRaises(TypeError):
      vhdi_file.open(None)

    with self.assertRaises(ValueError):
      vhdi_file.open(test_source, mode="w")

  def test_open_file_object(self):
    """Tests the open_file_object function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    if not os.path.isfile(test_source):
      raise unittest.SkipTest("source not a regular file")

    vhdi_file = pyvhdi.file()

    with open(test_source, "rb") as file_object:

      vhdi_file.open_file_object(file_object)

      with self.assertRaises(IOError):
        vhdi_file.open_file_object(file_object)

      vhdi_file.close()

      with self.assertRaises(TypeError):
        vhdi_file.open_file_object(None)

      with self.assertRaises(ValueError):
        vhdi_file.open_file_object(file_object, mode="w")

  def test_close(self):
    """Tests the close function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    with self.assertRaises(IOError):
      vhdi_file.close()

  def test_open_close(self):
    """Tests the open and close functions."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      return

    vhdi_file = pyvhdi.file()

    # Test open and close.
    vhdi_file.open(test_source)
    vhdi_file.close()

    # Test open and close a second time to validate clean up on close.
    vhdi_file.open(test_source)
    vhdi_file.close()

    if os.path.isfile(test_source):
      with open(test_source, "rb") as file_object:

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
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      _, _, parent_filename = vhdi_file.parent_filename.rpartition('\\')
      parent_filename = os.path.join(
        os.path.dirname(test_source), parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    media_size = vhdi_file.get_media_size()

    if media_size < 4096:
      # Test read without maximum size.
      vhdi_file.seek_offset(0, os.SEEK_SET)

      data = vhdi_file.read_buffer()

      self.assertIsNotNone(data)
      self.assertEqual(len(data), media_size)

    # Test read with maximum size.
    vhdi_file.seek_offset(0, os.SEEK_SET)

    data = vhdi_file.read_buffer(size=4096)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(media_size, 4096))

    if media_size > 8:
      vhdi_file.seek_offset(-8, os.SEEK_END)

      # Read buffer on media_size boundary.
      data = vhdi_file.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 8)

      # Read buffer beyond media_size boundary.
      data = vhdi_file.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 0)

    # Stress test read buffer.
    vhdi_file.seek_offset(0, os.SEEK_SET)

    remaining_media_size = media_size

    for _ in range(1024):
      read_size = int(random.random() * 4096)

      data = vhdi_file.read_buffer(size=read_size)

      self.assertIsNotNone(data)

      data_size = len(data)

      if read_size > remaining_media_size:
        read_size = remaining_media_size

      self.assertEqual(data_size, read_size)

      remaining_media_size -= data_size

      if not remaining_media_size:
        vhdi_file.seek_offset(0, os.SEEK_SET)

        remaining_media_size = media_size

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
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    if not os.path.isfile(test_source):
      raise unittest.SkipTest("source not a regular file")

    with open(test_source, "rb") as file_object:
      vhdi_file = pyvhdi.file()

      vhdi_file.open_file_object(file_object)

      vhdi_parent_file = None
      if vhdi_file.parent_identifier:
        vhdi_parent_file = pyvhdi.file()

        _, _, parent_filename = vhdi_file.parent_filename.rpartition('\\')
        parent_filename = os.path.join(
          os.path.dirname(test_source), parent_filename)
        vhdi_parent_file.open(parent_filename, "r")

        vhdi_file.set_parent(vhdi_parent_file)

      media_size = vhdi_file.get_media_size()

      # Test normal read.
      data = vhdi_file.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), min(media_size, 4096))

      vhdi_file.close()

      if vhdi_parent_file:
        vhdi_parent_file.close()

  def test_read_buffer_at_offset(self):
    """Tests the read_buffer_at_offset function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      _, _, parent_filename = vhdi_file.parent_filename.rpartition('\\')
      parent_filename = os.path.join(
        os.path.dirname(test_source), parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    media_size = vhdi_file.get_media_size()

    # Test normal read.
    data = vhdi_file.read_buffer_at_offset(4096, 0)

    self.assertIsNotNone(data)
    self.assertEqual(len(data), min(media_size, 4096))

    if media_size > 8:
      # Read buffer on media_size boundary.
      data = vhdi_file.read_buffer_at_offset(4096, media_size - 8)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 8)

      # Read buffer beyond media_size boundary.
      data = vhdi_file.read_buffer_at_offset(4096, media_size + 8)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), 0)

    # Stress test read buffer.
    for _ in range(1024):
      random_number = random.random()

      media_offset = int(random_number * media_size)
      read_size = int(random_number * 4096)

      data = vhdi_file.read_buffer_at_offset(read_size, media_offset)

      self.assertIsNotNone(data)

      remaining_media_size = media_size - media_offset

      data_size = len(data)

      if read_size > remaining_media_size:
        read_size = remaining_media_size

      self.assertEqual(data_size, read_size)

      remaining_media_size -= data_size

      if not remaining_media_size:
        vhdi_file.seek_offset(0, os.SEEK_SET)

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
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    vhdi_parent_file = None
    if vhdi_file.parent_identifier:
      vhdi_parent_file = pyvhdi.file()

      _, _, parent_filename = vhdi_file.parent_filename.rpartition('\\')
      parent_filename = os.path.join(
        os.path.dirname(test_source), parent_filename)
      vhdi_parent_file.open(parent_filename, "r")

      vhdi_file.set_parent(vhdi_parent_file)

    media_size = vhdi_file.get_media_size()

    vhdi_file.seek_offset(16, os.SEEK_SET)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, 16)

    vhdi_file.seek_offset(16, os.SEEK_CUR)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, 32)

    vhdi_file.seek_offset(-16, os.SEEK_CUR)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, 16)

    if media_size > 16:
      vhdi_file.seek_offset(-16, os.SEEK_END)

      offset = vhdi_file.get_offset()
      self.assertEqual(offset, media_size - 16)

    vhdi_file.seek_offset(16, os.SEEK_END)

    offset = vhdi_file.get_offset()
    self.assertEqual(offset, media_size + 16)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vhdi_file.seek_offset(-1, os.SEEK_SET)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vhdi_file.seek_offset(-32 - media_size, os.SEEK_CUR)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vhdi_file.seek_offset(-32 - media_size, os.SEEK_END)

    # TODO: change IOError into ValueError
    with self.assertRaises(IOError):
      vhdi_file.seek_offset(0, -1)

    vhdi_file.close()

    if vhdi_parent_file:
      vhdi_parent_file.close()

    # Test the seek without open.
    with self.assertRaises(IOError):
      vhdi_file.seek_offset(16, os.SEEK_SET)

  def test_get_offset(self):
    """Tests the get_offset function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    offset = vhdi_file.get_offset()
    self.assertIsNotNone(offset)

    vhdi_file.close()

  def test_get_media_size(self):
    """Tests the get_media_size function and media_size property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    media_size = vhdi_file.get_media_size()
    self.assertIsNotNone(media_size)

    self.assertIsNotNone(vhdi_file.media_size)

    vhdi_file.close()

  def test_get_disk_type(self):
    """Tests the get_disk_type function and disk_type property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    disk_type = vhdi_file.get_disk_type()
    self.assertIsNotNone(disk_type)

    self.assertIsNotNone(vhdi_file.disk_type)

    vhdi_file.close()

  def test_get_parent_filename(self):
    """Tests the get_parent_filename function and parent_filename property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vhdi_file = pyvhdi.file()

    vhdi_file.open(test_source)

    _ = vhdi_file.get_parent_filename()

    _ = vhdi_file.parent_filename

    vhdi_file.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
