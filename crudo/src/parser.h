#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include "package.h"

int newline_offset(char*);

int populate_package(Package*, char* field, char* val);

Package* parse(const char* );

char* strip_spaces(FILE* );

char* strstrip(char* );

char* extract_string(char*,int,int);

long unsigned int parse_version(char*);

Relation* parse_relation(char*);

#endif /* _PARSER_H_ */
