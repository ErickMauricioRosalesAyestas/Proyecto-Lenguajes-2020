#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

bool palabra();

int main(){
	
}


//funcion para reconocer si es una palabra o cadena lo ingresado
bool palabra(string cadena){
	cout<<cadena<<endl;
	enum TEstado{q0,q1,qe};
	
	TEstado Estado;
	
	int Simbolo;
	
	int i;
	int longitud;
	
	i = longitud = 0;
	
	
	longitud = cadena.size();
	
	while (longitud > i and Estado != qe){
		Simbolo = cadena[i];
		
		switch (Estado){
			case q0:
				if (Simbolo >= 'a' && Simbolo <= 'z'){
					Estado = q1;
				}
				break;
			case q1:
				if (Simbolo >= 'a' && Simbolo <= 'z'){
					Estado = q1;
				}
				else{
					Estado = qe;
				}
				break;
		}
		i++;
	}
	if (Estado == q1){
		return true;
	}
	else{
		return false;
	}
}
