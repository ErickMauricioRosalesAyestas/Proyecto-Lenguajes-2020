#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define MAX 650
#define MAX_RES 24
using namespace std;

int main(int argc, char* argv[]) {
  int i;
  printf("Se han pasado %3d argumentos:\n", argc);
  for(i=0; i<argc; i++) printf("%5d- %s\n", i, argv[i]);
  return 0;
}




char *PalabrasReservadas[MAX_RES] = {"si","entonces","sino","entero","decimal","logico","texto","char","mientras","haga","repita",
"hasta","var","como","verdadero","falso","declare","inicie","termine","lea","imprimir","intensidad","encender","apagar"};
char palabra[MAX]; //Esta variable es muy importante, pues guardara caracter por caracter formando asi una palabra y termina de guardar cuando detecta un espacio.


// Metodo para verificar si el token formado corresponde a una palabra reservada
bool verificarReservada(char palabra[]){
	int comp;
   bool esReservada=false;
   string str(palabra);
	for(int i=0; i<MAX_RES; i++)
   {
   	comp = strcmp(PalabrasReservadas[i],palabra);
      if(comp == 0)
      {
         esReservada = true;
         break;
      }
   }
   return esReservada;
}
