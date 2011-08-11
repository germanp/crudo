## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src
LDADD = $(top_srcdir)/src/parser.o

TESTS = check_parser
check_PROGRAMS = check_parser
check_parser_SOURCES = check_parser.c
#check_parser_CFLAGS = -I $(top_srcdir)/src