# Copyright © 2016  Roel Janssen <roel@gnu.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS 	= subdir-objects
AM_CFLAGS               = -I.
ACLOCAL_AMFLAGS         = -I m4
lib_LTLIBRARIES         = libinfra.la
libinfra_la_LDFLAGS     = -no-undefined
libinfra_la_SOURCES     = src/timer.c src/logger.c
nobase_include_HEADERS  = libinfra/timer.h libinfra/logger.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libinfra.pc
