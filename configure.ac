#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)

AC_INIT([pfish_syslog], [0.0], [<starcrusher2202@gmail.com>])
AM_INIT_AUTOMAKE([1.10],[foreign],[dist-bzip2])

AC_CONFIG_SRCDIR([pilot_fish/syslog.h])
AC_CONFIG_HEADER([config.h])

# Compile only as shared library.
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h syslog.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Syslog facility of this package.
AH_TEMPLATE([SYSLOG_FACILITY],[Syslog facility of this package.])
AC_DEFINE([SYSLOG_FACILITY],[LOG_LOCAL0])

# Output configuration files.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
