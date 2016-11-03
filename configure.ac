dnl
dnl Copyright © 2016 Roel Janssen <roel@gnu.org>
dnl
dnl This file is part of libinfra.
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([libinfra], [1.0.0], [roel@gnu.org])
AC_CANONICAL_HOST
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC

AM_PROG_AR([ar])

dnl Adopt the new 'default' flags for AR to silence linker warnings.
m4_divert_text([DEFAULTS], [: "${ARFLAGS=cr} ${AR_FLAGS=cr}"])

LT_INIT

AM_INIT_AUTOMAKE([1.9 tar-pax foreign -Wall -Werror])
AM_SILENT_RULES([yes])

AC_HEADER_STDC
AC_CONFIG_FILES([Makefile
                 libinfra.pc])

PKG_PROG_PKG_CONFIG
PKG_INSTALLDIR

AC_OUTPUT
