#ifndef _ERROR_H_
#define _ERROR_H_

#define libc_error(msg) perror(msg)
void libc_errorf(const char* format, ...);
void error_message(const char* msg);
void error_messagef(const char* format, ...);
void success_message(const char* msg);

#endif /* _ERROR_H_ */
