#ifndef PACKAGE_H
#define PACKAGE_H

#include <stdlib.h>

struct Relation{
  char* name;
  char comparator[3];
  unsigned long int version;
  struct Relation* next;
};

typedef struct Relation Relation;

struct Package{
  char* name;
  char* description;
  char* web;
  unsigned long int version;
  unsigned long int size;
  char* command;
  char* section;
  struct Relation* depends;
  struct Relation* conflicts;
  struct Relation* optionals;
};

typedef struct Package Package;

Package* init_package();
void free_package(Package**);
void free_relations(Relation**);
Relation* init_relation();
void free_relation(Relation**);

#endif // PACKAGE_H
