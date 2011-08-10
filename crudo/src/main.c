/* #include "logparser.h" */
/* #include "paquete.h" */
/* #include "base.h" */
/* #include <sqlite3.h> */
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


const char* nombre_programa;

void imprime_uso(){
  printf("Uso: %s opciones [argumentos...]\n",nombre_programa);
  printf("   -h  --help                Muestra esta ayuda.\n"
	 "   -a  --agregar fichero     Agregar informaci�n a partir de un archivo.\n"
	 "   -b  --borrar  paquete     Borrar el paquete especificado.\n"
	 "   -m  --mostrar [paquete]   Muestra informaci�n sobre el paquete especificado.\n"
	 "   -c  --crear [fichero.cdb] Crea una base de datos de los paquetes vac�a.\n");
}

//sqlite3* base;

int main(int argc, char** argv){
  //static Paquete paq;
  int opcion;
  struct stat buf;
  const char* txt_base="/var/lib/crudo/base.cdb"; // Path por defecto a la base de datos
  //const char* txt_base="crudo.cdb";
  const struct option opc_largas[] = {
    { "help",no_argument,NULL,'h' },
    { "agregar",required_argument,NULL,'a' },
    { "borrar",required_argument,NULL,'b' },
    { "mostrar",optional_argument,NULL,'m' },
    { "crear",optional_argument,NULL,'c' }
  };
  nombre_programa=argv[0];
  do{
    opcion=getopt_long(argc,argv,"ha:b:m::c::",opc_largas,NULL);
    switch( opcion ){
    case 'h':
      imprime_uso();
      return 0;
    case 'a':
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
      /* 	fprintf(stderr,"Error: %s no tiene una sintaxis v�lida\n",optarg); */
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
      /* 	fprintf(stderr,"Error: %s no tiene una sintaxis v�lida\n",optarg); */
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
    case 'c':
      /* if ( argv[optind] != NULL ){ */
      /* 	txt_base=argv[optind]; */
      /* } */
      /* if ( stat(txt_base,&buf) == -1 ){ */
      /* 	if ( CrearBase(txt_base) == 0 ) */
      /* 	  return 0; */
      /* 	else */
      /* 	  fprintf(stderr,"Error: No se pudo crear '%s'.\n",txt_base); */
      /* 	return 1; */
      /* } */
      /* else{ */
      /* 	fprintf(stderr,"Error: '%s' ya existe.\n",txt_base); */
      /* 	return 1; */
      /* } */
      break;
    case '?':
      fprintf(stderr,"  Escriba '%s --help' para obtener ayuda.\n",nombre_programa);
      return -1;
    default:
      return 1;
    }
  } while ( opcion != -1 );
  return 0;
}