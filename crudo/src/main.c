#include "package.h"
#include "parser.h"
#include "config.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <error.h>

void imprime_uso(){
  printf("Uso: %s opciones [argumentos...]\n",PACKAGE_NAME);
  printf("   -h  --help                Shows this help.\n"
	 "   -a  --add [file]          Adds package from a control file.\n"
	 "   -b  --borrar  paquete     Borrar el paquete especificado.\n"
	 "   -m  --mostrar [paquete]   Muestra información sobre el paquete especificado.\n"
	 "   -c  --init [database.cdb] Initializes an empty package database.\n");
}

//sqlite3* base;

int main(int argc, char** argv){
  int opcion;
  struct stat buf;
  const struct option opc_largas[] = {
    { "help",no_argument,NULL,'h' },
    { "agregar",required_argument,NULL,'a' },
    { "borrar",required_argument,NULL,'b' },
    { "mostrar",optional_argument,NULL,'m' },
    { "crear",optional_argument,NULL,'c' }
  };
  do{
    opcion=getopt_long(argc,argv,"ha:b:m::c::",opc_largas,NULL);
    switch( opcion ){
    case 'h':
      imprime_uso();
      return 0;
    case 'a':
      ;  // <-- GCC problem???
      crudo_err err;
      FILE *fp = fopen(optarg, "r");
      Package* p=parse(fp,&err);

      /* if ( procesarlog(optarg,&paq) == 0 ){ */
      /* 	if ( sqlite3_open(txt_base,&base) == SQLITE_OK ){ */
      /* 	  AgregarPaquete(&paq); */
      /* 	  sqlite3_close(base); */
      /* 	  return 0; */
      /* 	} */
      /* 	else */
      /* 	  perror("Error: No se pudo abrir la base de datos.\n"); */
      /* 	return -1; */
      /* } */
      /* else{ */
      /* 	fprintf(stderr,"Error: %s no tiene una sintaxis válida\n",optarg); */
      /* 	return -1; */
      /* } */
      break;
    case 'b':
      /* paq=IniciarPaquete(); */
      /* if ( procesarlog(optarg,&paq) == 0 ){ */
      /* 	if ( sqlite3_open(txt_base,&base) == SQLITE_OK ){ */
      /* 	  AgregarPaquete(&paq); */
      /* 	  sqlite3_close(base); */
      /* 	  return 0; */
      /* 	} */
      /* 	else */
      /* 	  perror("Error: No se pudo abrir la base de datos.\n"); */
      /* 	return -1; */
      /* } */
      /* else{ */
      /* 	fprintf(stderr,"Error: %s no tiene una sintaxis válida\n",optarg); */
      /* 	return -1; */
      /* } */
      break;
    case 'm':
      /* if ( sqlite3_open(txt_base,&base) == SQLITE_OK ){ */
      /* 	if ( argv[optind] != NULL ){ */
      /* 	  char* nombre=malloc(strlen(argv[optind])*sizeof(char)+1); */
      /* 	  strcpy(nombre,argv[optind]); */
      /* 	  strcat(nombre,"%"); */
      /* 	  mostrar_paquetes(nombre); */
      /* 	} */
      /* 	else{ */
      /* 	  mostrar_paquetes("%"); */
      /* 	} */
      /* } */
      /* break; */
      /* else{ */
      /* 	fprintf(stderr,"Error: No se pudo abrir la base de datos.\n"); */
      /* 	return -1; */
      /* } */
    case 'i':
      ;
      char* database_file;
      if ( argv[optind] )
      	database_file=argv[optind];
      else
	database_file=DEFAULT_DATABASE_FILE;
      struct stat buf;
      int ret_val=stat(database_file, &buf);
      if ( ret_val == ENOENT ) {
	if ( init_database(database_file) ) {
	  printf("Successfully initialized the database.\n");
	  return 0;
	} else {
	  perror("Failed to create the database.\n");
	}
      } else if ( ! ret_val ) {
	error(1,0,"'%s' already exists, remove it if you are sure.",database_file);
      }
      return 1;
      break;
    case '?':
      fprintf(stderr,"  Escriba '%s --help' para obtener ayuda.\n",PACKAGE);
      return -1;
    default:
      return 1;
    }
  } while ( opcion != -1 );
  return 0;
}
