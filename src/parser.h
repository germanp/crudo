#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <regex.h>
#include "package.h"
#include "error.h"

int newline_offset(char*);

int fill_package(Package* p, char* field, char* val);

Package* parse(FILE* fp);

char* strip_spaces(FILE* file);

char* strstrip(char* str);

void extract_string(char* matched,const char* txt,unsigned int base,unsigned int offset);

void extract_regmatch(char* matched, const char* str, regmatch_t m, unsigned int max);

long unsigned int parse_version(const char*);

int parse_relations(Relation** first_rel, const char* txt_rel);

#endif /* _PARSER_H_ */
