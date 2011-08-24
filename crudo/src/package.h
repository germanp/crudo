#ifndef PACKAGE_H
#define PACKAGE_H

struct Relation{
  char* name;
  char comparator[3];
  unsigned long int version;
};

typedef struct Relation Relation;

struct Package{
  char* name;
  char* description;
  char* web;
  unsigned long int version;
  //char* command;
  char* section;
  struct Relation* depends;
  struct Relation* conflicts;
  struct Relation* optionals;
};

typedef struct Package Package;

#endif // PACKAGE_H
