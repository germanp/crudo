#include "parser.h"
#include <stdio.h>
#include <unistd.h>

int parse(const char* file){
  FILE *fp = fopen(file, "r");
  return 0;
}

/** 
 * Strip all the repeated spaces (tabs, returns, etc)
 * 
 * @param f Already open file stream
 * 
 * @return It returns an already allocated char*. You must free it.
 */

char* strip_spaces(FILE* f){
  /* char* buffer; // Voy a copiar todo acá y después la voy a parsear */
  /* int car=getc(f), i=0, flag=0; */
  /* while( car != EOF ) { */
  /*   if ( isspace(car) ){ // Cambiar por un tipo de espacio  */
      
  /*   } */
  /* } */
  return 0;
}
