#include "package.h"
#include "parser.h"
#include "config.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>

extern char *program_invocation_name;

void show_usage(){
  printf("Usage: %s --add [controlfile]\n",program_invocation_name);
  printf("  or:  crudo --delete package\n"
	 "  or:  crudo --show [search_pattern]\n"
	 "  or:  crudo --init [database_file]\n"
	 );
}

void show_help(){
  show_usage();
  printf("%s -- %s\n\n",program_invocation_name,PACKAGE_BRIEF);

  printf("  -a, --add[=file]           Adds package from a control file or stdin\n"
	 "                             (default).\n"
	 "  -d, --delete=package       Deletes the indicated package.\n"
	 "  -i, --init[=database_file] Creates the initial structure for database.\n"
	 "  -s, --show[=pattern]       Shows info about all packages matching PATTERN.\n"
	 "  -?, --help                 Give this help list.\n"
	 "      --usage                Give a short usage message.\n"
	 "  -V, --version              Print program version.\n\n"
	 );
	 
  printf("Report bugs to %s.\n",PACKAGE_BUGREPORT);
}

int main(int argc, char** argv){
  int option;
  const struct option long_opts[] = {
    { "add",optional_argument,NULL,'a' },
    { "delete",required_argument,NULL,'d' },
    { "show",optional_argument,NULL,'s' },
    { "init",optional_argument,NULL,'i' },
    { "help",no_argument,NULL,'h' },
    { "usage",no_argument,NULL,'u' },
    { "version",no_argument,NULL,'V' }
  };

  do{
    option=getopt_long(argc,argv,"huVa::d:s::i::",long_opts,NULL);
    switch( option ){
    case 'a':
      ;  // <-- GCC problem???
      /* FILE *fp = fopen(optarg, "r"); */
      /* if ( fp ) { */
      /* 	crudo_err err; */
      /* 	Package* p=parse(fp,&err); */
      /* 	if ( p ) { */
	  
      /* 	} else { */
	  
      /* 	} */
      /* } else */
      /* 	perror("Failed to open the file."); */
      return 0;
    case 'd':
      break;
    case 's':
      break;
    case 'i':
      ;
      if ( argc > 3 )
	printf("Warning: Ignoring '%s' option and what follows.\n",argv[3]);
      char* database_file= argv[optind] ? argv[optind] : DEFAULT_DATABASE_FILE;

      struct stat buf;
      int ret_val=stat(database_file, &buf);
      if ( errno == ENOENT ) {
      	if ( init_database(database_file) ) {
      	  put_message("Successfully initialized the database.");
      	  return 0;
      	} else {
      	  put_error("Failed to create the database.");
	  return 1;
      	}
      } else if ( ! ret_val ) {
      	put_errorf("'%s' already exists, remove it if you are sure.",database_file);
	return 1;
      } else {
	put_errorf("Couldn't open file '%s': %s",database_file,strerror(errno));
      }
      return 0;
    case 'h':
      show_help();
      return -1;
    case 'u':
      show_usage();
      return -1;
    case 'V':
      puts(PACKAGE_STRING);
      return 0;
    case '?':
      fprintf(stderr,"Try `%s --help' for more information.\n",program_invocation_name);
      return -1;
    case -1:
      put_errorf("What do you want do?\n"
		 "Try `%s --help' for more information.",program_invocation_name);
      return -1;
    /* default: */
    /*   show_usage(); */
    /*   return -1; */
    }
  } while ( option != -1 );
  return 0;
}
