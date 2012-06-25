AC_INIT([crudo], [0.1], [<german@linuxcrudo.com.ar>],,[http://www.linuxcrudo.com.ar])
AC_DEFINE([DEFAULT_DATABASE_FILE], ["/var/lib/crudo/crudo.cdb"], ["Default path to the package database."])
AC_DEFINE([PACKAGE_BRIEF], ["a tool to add, remove and manage LinuxCrudo packages."], [""])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AM_PROG_CC_C_O
AC_CHECK_LIB([pthread], [pthread_mutex_trylock])
AC_CHECK_LIB([dl], [dlopen])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES(Makefile src/Makefile test/Makefile)
AC_OUTPUT
