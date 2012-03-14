#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <regex.h>
#include "package.h"
#include "error.h"

int newline_offset(char*);

int fill_package(Package* p, char* field, char* val, crudo_err* err);

Package* parse(FILE* fp, crudo_err* err);

char* strip_spaces(FILE* file);

char* strstrip(char* str);

void extract_string(char* matched,const char* txt,unsigned int base,unsigned int offset);

//char* d_extract_string(char*,int, int);

void extract_regmatch(char* matched, const char* str, regmatch_t m, unsigned int max);

long unsigned int parse_version(const char*, crudo_err*);

int parse_relation(Relation** first_rel, const char* txt_rel, crudo_err* err);

#endif /* _PARSER_H_ */
