#include "package.h"

#include <stdio.h>

Package* init_package(){
  Package* p=calloc(1,sizeof(Package));
  return p;
}

Relation* init_relation(){
  Relation* rel=malloc(sizeof(Relation));
  rel->next=0;
  return rel;
}

void free_package(Package** p){
  free((*p)->name);
  free((*p)->description);
  free((*p)->web);
  free((*p)->section);
  free_relations(&(*p)->depends);
  free_relations(&(*p)->conflicts);
  free_relations(&(*p)->optionals);
  (*p)=0;
}

void free_relation(Relation** r){
  free((*r)->name);
  free(*r);
}

void free_relations(Relation** r){
  Relation* _r=*r;
  Relation* tmp_r;
  if ( _r )
    do {
      tmp_r=_r->next;
      free_relation(&_r);
    } while( (_r=tmp_r) );
  *r=NULL;
}
