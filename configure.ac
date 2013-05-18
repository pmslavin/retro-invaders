#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([invaders], [1.0], [slavinp@cs.man.ac.uk])
AM_INIT_AUTOMAKE([foreign -Wall])
#AC_CONFIG_SRCDIR([invaders.cpp])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
#LT_INIT
AC_PROG_LIBTOOL
AC_PROG_CXX

# Checks for libraries.
SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION,:,AC_MSG_ERROR([*** SDL >= $SDL_VERSION not found!]))
AC_CHECK_HEADERS([SDL/SDL.h])
AC_CHECK_LIB([SDL], [main])
AC_CHECK_LIB([SDL_image], [main])
AC_CHECK_LIB([SDL_ttf], [main])
AC_CHECK_LIB([SDL_mixer], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile lib/Makefile src/Makefile])
AC_OUTPUT
