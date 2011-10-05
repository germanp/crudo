## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src
LDADD = cu/libcu.a $(top_srcdir)/src/parser.o $(top_srcdir)/src/package.o

TESTS = suite
check_PROGRAMS = suite
suite_SOURCES = suite.c check_parser.c
#check_parser_CFLAGS = -I $(top_srcdir)/src

cu/libcu.a:
	make -C cu/