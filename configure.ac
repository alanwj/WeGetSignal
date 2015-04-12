AC_PREREQ([2.69])
AC_INIT([WeGetSignal], [0.1], [alan.wayne.johnson@gmail.com])
AC_CONFIG_SRCDIR([src/wgs.c])

AM_INIT_AUTOMAKE([foreign -Wall -Werror -Wno-portability])
AM_PATH_GTK_3_0

AC_PROG_CC
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, [glib-compile-resources])

AC_SEARCH_LIBS([cos], [m], [], [
  AC_MSG_ERROR([unable to find cos function])
])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
