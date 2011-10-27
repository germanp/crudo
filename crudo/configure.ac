AC_INIT([crudo], [0.1], [<german@linuxcrudo.com.ar>])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AM_PROG_CC_C_O
AC_CHECK_LIB([pthread], [pthread_mutex_trylock])
AC_CHECK_LIB([dl], [dlopen])
AC_CONFIG_HEADERS([config.h])
AC_DEFINE([DEFAULT_DATABASE_FILE], ["/var/lib/crudo/crudo.cdb"], ["Default path to the package database."])
AC_CONFIG_FILES(Makefile src/Makefile tests/Makefile)
AC_OUTPUT