## Process this file with automake to produce Makefile.in

bin_PROGRAMS = crudo
crudo_SOURCES = main.c parser.c package.c sqlite3.c database.c error.c

sqlite3.o: sqlite3.c
	$(CC) $(CFLAGS) -DSQLITE_DEFAULT_FOREIGN_KEYS=1 -c $< -o $@

