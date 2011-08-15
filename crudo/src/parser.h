#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include "package.h"

struct Package* parse(const char* );

char* strip_spaces(FILE* );

#endif /* _PARSER_H_ */
