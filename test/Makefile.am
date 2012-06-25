## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src
LDADD = $(top_srcdir)/src/parser.o $(top_srcdir)/src/package.o $(top_srcdir)/src/database.o $(top_srcdir)/src/error.o $(top_srcdir)/src/sqlite3.o

TESTS = test_runner
check_PROGRAMS = test_runner
test_runner_SOURCES = unity/unity.c unity/unity_fixture.c test_runner.c parser_test.c database_test.c
