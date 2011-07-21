#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  FILE *fp = fopen("prueba.txt", "r");
  char buffer[2000]; // Voy a copiar todo acá y después la voy a parsear
  int car=getc(fp), i=0, boolean flag=0;
  while( car != EOF ) {
    if ( car == ' ' ){ // Cambiar por un tipo de espacio 
      buffer[i]=car;      
  }
  return 0;
}

