#ifndef PACKAGE_H
#define PACKAGE_H

typedef struct {
  char* name;
  char comparator[3];
  unsigned long int version;
} Relation;

typedef struct{
  char* name;
  char* description;
  unsigned long int version;
  //char* command;
  char* section;
  struct Relacion* depends;
  struct Relacion* conflicts;
  struct Relacion* optionals;
} Package;

#endif // PACKAGE_H
