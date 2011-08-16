#include "parser.h"
#include "package.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

Package* parse(const char* file){
  FILE *fp = fopen(file, "r");
  char* buffer = strip_spaces(fp);
  Package* p=(Package*)malloc(sizeof(Package));
  regex_t filter;
  regmatch_t* match_array=(regmatch_t*)malloc(sizeof(regmatch_t)*2);

  if(regcomp(&filter, "\([A-Za-z]*\)", 0) != 0)
    perror("Critical error."); // Revisar
  if ( regexec(&filter,buffer,1,match_array,0) == 0 ) {
    printf("%d\n",match_array[0].rm_eo);
  }
  regfree(&filter);
  fclose(fp);
  return p;
}

/** 
 * Strip all the repeated spaces (tabs, returns, etc)
 * 
 * @param f Already open file stream
 * 
 * @return It returns an already allocated char*. You must free it.
 */

char* strip_spaces(FILE* f){
  char* buffer=(char*)malloc(sizeof(char)*1024); // Voy a copiar todo acá y después la voy a parsear
  int letter, i=0, last_letter=0;
  while( (letter=fgetc(f)) != EOF ) {
    if (isspace(letter)) {
      if ( letter == last_letter ){
	last_letter=letter;
	continue;
      }
    }
    last_letter=letter;
    buffer[i]=letter;
    i++;
    // Super dynamic allocation.
    if (!(i%1024)) buffer=(char*)realloc(buffer,(i+1024)*sizeof(char));
  }
  buffer[i]='\0';
  return buffer;
}

