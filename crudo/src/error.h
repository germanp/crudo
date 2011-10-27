#ifndef _ERROR_H_
#define _ERROR_H_

enum {
  CRUDO_OK,
  CRUDO_PARSE_ERROR,
  CRUDO_OUTMEM
} CRUDO_ERROR;

struct crudo_err {
  int code;
  char* field; // Field where error occurs
  char* str_err; // String where error occurs
};
 
typedef struct crudo_err crudo_err; 

char* string_error(const int );
void put_errorf(const char* format, ...);
void put_error(const char* string);

#endif /* _ERROR_H_ */
