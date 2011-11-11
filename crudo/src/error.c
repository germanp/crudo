#include "error.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/** 
 * Given an error code returns te corresponding error string.
 * 
 * @param e Input error code
 * 
 * @return 
 */

/* char* string_error(const int e){ */
/*   const char* error_strings[]={ */
/*     "There is no error.", */
/*     "There was an error when parsing control file, sintaxis is wrong.", */
/*     "Critical error, the memory is exhausted." */
/*   } */
/*   int len=strlen(error_strings[e]); */
/*   char* buf=malloc(len); */
/*   strncpy(buf,error_strings[e],len); */
/*   return buff; */
/* } */

void put_errorf(const char* format, ...){
     va_list args;
     extern char *program_invocation_name;
     fprintf( stderr, "%s: ", program_invocation_name);
     va_start( args, format );
     vfprintf( stderr, format, args );
     va_end( args );
     fputs( "\n" , stderr);
}

void put_error(const char* string){
     va_list args;
     extern char *program_invocation_name;
     fprintf( stderr, "%s: %s\n", program_invocation_name,string);
}


void put_message(const char* string){
     va_list args;
     extern char *program_invocation_name;
     printf( "%s: %s\n", program_invocation_name,string);
}

void put_messagef(const char* format, ...){
     va_list args;
     extern char *program_invocation_name;
     printf( "%s: ", program_invocation_name);
     va_start( args, format );
     vprintf( format, args );
     va_end( args );
     puts( "\n" );
}
