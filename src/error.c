#include "error.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>


void error_messagef(const char* format, ...){
     va_list args;
     extern char *program_invocation_name;
     fprintf( stderr, "%s: ", program_invocation_name);
     va_start( args, format );
     vfprintf( stderr, format, args );
     va_end( args );
     fputs( "\n" , stderr);
}

void error_message(const char* string){
     va_list args;
     extern char *program_invocation_name;
     fprintf( stderr, "%s: %s\n", program_invocation_name,string);
}


void success_message(const char* string){
     va_list args;
     extern char *program_invocation_name;
     printf( "%s: %s\n", program_invocation_name,string);
}

void success_messagef(const char* format, ...){
     va_list args;
     extern char *program_invocation_name;
     printf( "%s: ", program_invocation_name);
     va_start( args, format );
     vprintf( format, args );
     va_end( args );
     puts( "\n" );
}

void libc_errorf(const char* format, ...){
  va_list args;
  char buf[100];
  va_start( args, format );
  vsnprintf( buf, 100, format, args );
  va_end( args );
  perror(buf);
}
