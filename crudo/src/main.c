#include "package.h"
#include "parser.h"
#include "config.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <string.h>
#include <error.h>
#include <errno.h>

/* void show_usage(){ */
/*   printf("Uso: %s options [argumentos...]\n",PACKAGE_NAME); */
/*   printf("   -h  --help                Shows this help.\n" */
/* 	 "   -a  --add [file]          Adds package from a control file.\n" */
/* 	 "   -b  --borrar  paquete     Borrar el paquete especificado.\n" */
/* 	 "   -m  --mostrar [paquete]   Muestra información sobre el paquete especificado.\n" */
/* 	 "   -c  --init [database.cdb] Initializes an empty package database.\n"); */
/* } */

const char *argp_program_version=PACKAGE_STRING;
const char *argp_program_bug_address=PACKAGE_BUGREPORT;
     
/* Program documentation. */
static char doc[] =
  "crudo -- a tool to add, remove and manage LinuxCrudo packages.";

static char args_doc[] =
  "--add [FILE]\n"
  "--delete PACKAGE\n"
  "--show [SEARCH_PATTERN]\n"
  "--init [DATABASE_FILE]";

static struct argp_option options[] =
{
  {"add",'a',"FILE", OPTION_ARG_OPTIONAL, "Adds package from a control file or stdin (default)"},
  {"delete",'d',"PACKAGE", 0,"Deletes the indicated PACKAGE"},
  {"show",'s',"PATTERN", OPTION_ARG_OPTIONAL,"Shows info about all packages matching PATTERN."},
  {"init",'i',"DATABASE_FILE", OPTION_ARG_OPTIONAL,"Creates the initial structore for database."},
  {0}
};

  /* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  switch (key) {
  case 'a':
    
    break;
  case ARGP_KEY_NO_ARGS:
    argp_usage (state);  
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char** argv){
  argp_parse (&argp, argc, argv, 0, 0, 0);
  /* do{ */
  /*   option=getopt_long(argc,argv,"ha:b:m::c::",long_opts,NULL); */
  /*   switch( option ){ */
  /*   case 'h': */
  /*     show_usage(); */
  /*     return 0; */
  /*   case 'a': */
  /*     ;  // <-- GCC problem??? */
  /*     FILE *fp = fopen(optarg, "r"); */
  /*     if ( fp ) { */
  /* 	crudo_err err; */
  /*     	Package* p=parse(fp,&err); */
  /*     	if ( p ) { */
	  
  /*     	} else { */
	  
  /*     	} */
  /*     } else */
  /*     	perror("Failed to open the file."); */
  /*     break; */
  /*   case 'b': */
  /*     break; */
  /*   case 'm': */
  /*     break; */
  /*   case 'i': */
  /*     ; */
  /*     char* database_file; */
  /*     if ( argv[optind] ) */
  /*     	database_file=argv[optind]; */
  /*     else */
  /* 	database_file=DEFAULT_DATABASE_FILE; */
  /*     struct stat buf; */
  /*     int ret_val=stat(database_file, &buf); */
  /*     if ( ret_val == ENOENT ) { */
  /* 	if ( init_database(database_file) ) { */
  /* 	  printf("Successfully initialized the database.\n"); */
  /* 	  return 0; */
  /* 	} else { */
  /* 	  perror("Failed to create the database."); */
  /* 	} */
  /*     } else if ( ! ret_val ) { */
  /* 	error(1,0,"'%s' already exists, remove it if you are sure.",database_file); */
  /*     } */
  /*     return 1; */
  /*     break; */
  /*   case '?': */
  /*   default: */
  /*     show_usage(); */
  /*     return -1; */
  /*   } */
  /* } while ( option != -1 ); */
  return 0;
}
