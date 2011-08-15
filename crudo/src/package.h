#ifndef PACKAGE_H
#define PACKAGE_H

struct Relation {
  char* paquete;
  char comparador[3];
  unsigned long int version;
};

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
