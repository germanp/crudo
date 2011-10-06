#include "error.h"
#include <string.h>

/** 
 * Given an error code returns te corresponding error string.
 * 
 * @param e Input error code
 * 
 * @return 
 */

char* string_error(const int e){
  const char* error_strings[]={
    "There is no error.",
    "There was an error when parsing control file, sintaxis is wrong.",
    "Critical error, the memory is exhausted."
  }
  int len=strlen(error_strings[e]);
  char* buf=malloc(len);
  strncpy(buf,error_strings[e],len);
  return buff;
}
