#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

//Declaramos las variables de tipo string a utilizar
string TablaSimbolos[7] = {"si","sino","para","mientras","definir","encender","Apagar"};
string Temporal[200];
string Variables[200];
string comando;

//almacenaremos los caracteres en este arreglo para tokenizar
char cadena[200];

//Declaramos las variables de tipo entero a utilizar
int contador;
int ContadorVariables;
int TamanioTemporal=0;
int ContadorComandos[7] = {0, 0, 0, 0, 0, 0, 0};

//funciones o metodos que utilizaremos
bool si();
bool sino();
bool mientras();
bool para();
bool encender();
bool apagar();
bool definir();
bool cadenas(string p);
bool palabra(string p);
bool numero(string p);

void EncontrarComandos();
void tokens();
void leerArchivo(char *txt);
void ResumenComandos();


int main(int argc, char* argv[]){
	//leyendo el archivo de texto que indica el usuario desde consola
	char *txt = argv[1];
	leerArchivo(txt);
	
	tokens();
	cout<<"\n\t++ Resumen de sintaxis de instrucciones ++ \n"<<endl;
	EncontrarComandos();
	ResumenComandos();
	
	return 0;

}

//generar tokens de las cadenas del archivo de texto, para analizar las palabras
void tokens(){
	char *token;
	int n = 0;
	//Sacamos la primer palabra de la cadena leida del archivo de texto
	token = strtok(cadena, " ,;");
	
	//Sacamos el tamaño de nuestra tabla de simbolos para recorrer y comparar las palabras
	int TamanioArreglo = sizeof TablaSimbolos/sizeof TablaSimbolos[0];
	
	
	while(token){
		comando = token;
		
		for (TamanioTemporal = 0; TamanioTemporal<TamanioArreglo; TamanioTemporal++){
			//comparamos si el comando existe en  nuestra tabla de simbolos
			if (comando.compare(TablaSimbolos[TamanioTemporal])==0){
				cout<<"Comando reconocido: "<<comando<<endl;
				break;
			}
		}
		//Pasamos a la siguiente palabra, para analizar
		token = strtok(NULL," ,;");
		//Almacenamos las palabras encontradas en un arreglo, para luego trabajar con el arreglo en los comandos y sus fuciones
		Temporal[n] = comando;
		n++;
	}
	TamanioTemporal = n;
}
//Leemos el archivo txt, para analizarlo
void leerArchivo(char *txt){
	int j=0;
	int i=0;
	
	ifstream archivo;
	string nombreArchivo,texto;
	
	//abrimos el archivo de texto, almacenamos su informacion
	archivo.open(txt,ios::in); 
	
	//If por surge un error al momento de abrir el archivo txt
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo.eof()){
		//Obtenemos las cadenas por lineas 
		getline(archivo,texto, '\n');
		for (i=0; i<texto.size(); i++){
			cadena[j] = texto[i];
			j++;
		}
	}
	
	archivo.close();
}

//Funcion para leer los comandos del usuario y verifica si el comando existe en la tabla de simbolos
void EncontrarComandos(){
	string palabra;
	
	//almacenamos la primer palabra dentro de las variables temporales
	palabra = Temporal[contador];
	
	//ciclo para recorrer el arreglo con las palabras obtenidas con los tokens
	while (contador<TamanioTemporal){
		//analisar cada palabra y comparar si coincide con la informacion de la tabla de simbolos para llamar su funcion respectiva
		if (Temporal[contador] == "si"){
			ContadorComandos[0] += 1;
			if (si()){
				cout<<"";
			}else{
				cout<<"";
			}
		}else if(Temporal[contador] == "sino"){
			ContadorComandos[1] += 1;
			if (sino()){
				cout<<"";
			}else{
				cout<<"";
			}
		
		}else if (Temporal[contador] == "mientras"){
			ContadorComandos[3] += 1;
			if (mientras()){
				cout<<"";
			}else{
				cout<<"";
			}
		}else if (Temporal[contador] == "definir"){
			ContadorComandos[4] += 1;
			if (definir()){
				cout<<"";
			}else{
				cout<<"";
			}
		}else if (Temporal[contador] == "encender"){
			ContadorComandos[5] += 1;
			if (encender()){
				cout<<"";
			}else{
				cout<<"";
			}
		}else if (Temporal[contador] == "apagar"){
			ContadorComandos[6] += 1;
			if (apagar()){
				cout<<"";
			}else{
				cout<<"";
			}
		}
		else{
			/*Revisar si las instrucciones son diferentes a la informacion de la tabla de simbolos
			while(palabra !="para"&&palabra !="si"&&palabra !="mientras"&&palabra !="definir"){
		    	contador++;
		    	palabra=Temporal[contador];
		    	cout<<"Revisar la declaracion de las instrucciones "<<Temporal[contador]<<endl;
			}
			contador--;
			return false;
			*/
			cout<<"";
			
		}
		contador++;
	}

}
//funcion si, para verificar que la instruccion fue ingresada de forma correcta
bool si(){
	contador++;
	//Analisamos si el caracter despues del si, sea un parentesis abierto
	if (Temporal[contador] == "("){
		contador++;
		//Revisamos que luego del parentesis lo que se ingresa sea un caracter o cadena
		if (palabra(Temporal[contador])){
			contador++;
			//Analisamos que luego del caracter o cadena, sea un signo matematico valido
			if (Temporal[contador]=="==" || Temporal[contador] == "!=" || Temporal[contador] == "<" || Temporal[contador] == ">"){
				contador++;
				//revisamos que lo siguiente sea un numero
				if (numero(Temporal[contador])){
					contador++;
					//Ahora revisamos si el siguiente caracter sea un parentesis, para cerrar el si
					if (Temporal[contador]==")"){
						contador++;
						//confirmamos que se abran los corchetes de la instruccion si
						if (Temporal[contador]=="{"){
							contador++;
							//confirmamos que se cierren los corchetes para darle fin a la instruccion
							if (Temporal[contador]=="}"){
								cout<<"--Instruccion si, aceptada como valida"<<endl;
								contador++;
								//hacemos la recursividad para que se analizen las siguientes instrucciones
								if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
									EncontrarComandos();
									return true;
								}else{
									return false;
								}
							//todos los else, imprimen un mensaje de que las instrucciones no escribieron de la manera correcta
							}else{
								cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
								contador++;
								return false;
							}
						}else{
							cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
							contador++;
							return false;
						}
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
				contador++;
				return false;
			}	
		}
		//Usamos el else if, para aceptar numeros tambien, luego del parentesis
		else if(numero(Temporal[contador])){
			contador++;
			if (Temporal[contador]=="==" || Temporal[contador] == "!=" || Temporal[contador] == "<" || Temporal[contador] == ">"){
				contador++;
				//revisamos que lo siguiente es una palabra
				if (palabra(Temporal[contador])){
					contador++;
					//Ahora revisamos si el siguiente caracter sea un parentesis, para cerrar el si
					if (Temporal[contador]==")"){
						contador++;
						//confirmamos que se abran los corchetes de la instruccion si
						if (Temporal[contador]=="{"){
							contador++;
							//confirmamos que se cierren los corchetes para darle fin a la instruccion
							if (Temporal[contador]=="}"){
								cout<<"--Instruccion si, aceptada como valida"<<endl;
								contador++;
								//hacemos la recursividad para que se analizen las siguientes instrucciones
								if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
									EncontrarComandos();
									return true;
								}else{
									return false;
								}
							//todos los else, imprimen un mensaje de que las instrucciones no escribieron de la manera correcta
							}else{
								cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
								contador++;
								return false;
							}
						}else{
							cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
							contador++;
							return false;
						}
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
				contador++;
				return false;
			}
		}
		else{
			cout<<"entro aqui";
			cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
			contador++;
			return false;
		}
	}else{
		cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
	//NOTA: recordar que al final de cada if y else, aumentamos el contador para ir recorriendo el arreglo
}
//funcion sino, para leer las instrucciones al momento de encontrar el comando sino
bool sino(){
	contador++;
	//Al ser un sino, no hay condicionales, simplemente verificamos que se abran los corchetes luego del sino
	if (Temporal[contador] == "{"){
		contador++;
		//verificamos que los corchetes sean cerrados para finalizar la instruccion, y aceptarla como valida
		if (Temporal[contador] == "}"){
			contador++;
			cout<<"--Instruccion sino, aceptado como valido"<<endl;
			//Hacemos la recursividad para pasar a la siguiente instruccion
			if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
				EncontrarComandos();
				return true;
			}else{
				return false;
			}
		//Todos los else solo imprimen un mensaje de error, ya que la instruccion no se ingreso de la manera correcta
		}else{
			cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
			contador++;
			return false;
		}
	}else{
		cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
}

void ResumenComandos(){
	int i;

	int tamanio = sizeof ContadorComandos/ sizeof ContadorComandos[0];
	cout<<"\n\t++ Resumen de cantidad de comandos utilizados ++ \n"<<endl;
	for (i=0; i<tamanio; i++){
		if (ContadorComandos[i] > 0){
			if (i==0){
				cout<<"--Comandos si encontrados: "<<ContadorComandos[i]<<endl;
			}
			else if(i==1){
				cout<<"--Comandos sino encontrados: "<<ContadorComandos[i]<<endl;
			}
			else if(i==2){
				cout<<"--Comandos para encontrados: "<<ContadorComandos[i]<<endl;
			}
			else if(i==3){
				cout<<"--Comandos mientras encontrados: "<<ContadorComandos[i]<<endl;
			}
			else if(i==4){
				cout<<"--Variables de memoria: "<<ContadorComandos[i]<<endl;
			}
			else if(i==5){
				cout<<"--Comandos encender encontrados: "<<ContadorComandos[i]<<endl;
			}
			else if(i==6){
				cout<<"--Comandos apagar encontrados: "<<ContadorComandos[i]<<endl;
			}
		}
		
	}
}

bool mientras(){
	contador++;
	//Analisamos si el caracter despues del si, sea un parentesis abierto
	if (Temporal[contador] == "("){
		contador++;
		//Revisamos que luego del parentesis lo que se ingresa sea un caracter o cadena
		if (palabra(Temporal[contador])){
			contador++;
			//Analisamos que luego del caracter o cadena, sea un signo matematico valido
			if (Temporal[contador]=="==" || Temporal[contador] == "!=" || Temporal[contador] == "<" || Temporal[contador] == ">"){
				contador++;
				//revisamos que lo siguiente sea un numero
				if (numero(Temporal[contador])){
					contador++;
					//Ahora revisamos si el siguiente caracter sea un parentesis, para cerrar el mientras
					if (Temporal[contador]==")"){
						contador++;
						//confirmamos que se abran los corchetes de la instruccion si
						if (Temporal[contador]=="{"){
							contador++;
							//confirmamos que se cierren los corchetes para darle fin a la instruccion
							if (Temporal[contador]=="}"){
								cout<<"--Instruccion mientras, aceptada como valida"<<endl;
								contador++;
								//hacemos la recursividad para que se analizen las siguientes instrucciones
								if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
									EncontrarComandos();
									return true;
								}else{
									return false;
								}
							//todos los else, imprimen un mensaje de que las instrucciones no escribieron de la manera correcta
							}else{
								cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
								contador++;
								return false;
							}
						}else{
							cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
							contador++;
							return false;
						}
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
				contador++;
				return false;
			}	
		}
		//Usamos el else if, para aceptar numeros tambien, luego del parentesis
		else if(numero(Temporal[contador])){
			contador++;
			if (Temporal[contador]=="==" || Temporal[contador] == "!=" || Temporal[contador] == "<" || Temporal[contador] == ">"){
				contador++;
				//revisamos que lo siguiente es una palabra
				if (palabra(Temporal[contador])){
					contador++;
					//Ahora revisamos si el siguiente caracter sea un parentesis, para cerrar el si
					if (Temporal[contador]==")"){
						contador++;
						//confirmamos que se abran los corchetes de la instruccion si
						if (Temporal[contador]=="{"){
							contador++;
							//confirmamos que se cierren los corchetes para darle fin a la instruccion
							if (Temporal[contador]=="}"){
								cout<<"--Instruccion mientras, aceptada como valida"<<endl;
								contador++;
								//hacemos la recursividad para que se analizen las siguientes instrucciones
								if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
									EncontrarComandos();
									return true;
								}else{
									return false;
								}
							//todos los else, imprimen un mensaje de que las instrucciones no escribieron de la manera correcta
							}else{
								cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
								contador++;
								return false;
							}
						}else{
							cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
							contador++;
							return false;
						}
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion mientas, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
				contador++;
				return false;
			}
		}
		else{
			cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
			contador++;
			return false;
		}
	}else{
		cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
}

bool para(){
	contador++;
	if (Temporal[contador] == "("){
		contador++;
		if (palabra(Temporal[contador])){
			contador++;
			//Analisamos que luego del caracter o cadena, sea un signo matematico valido
			if (Temporal[contador]=="="){
				contador++;
				//revisamos que lo siguiente sea un numero
				if (numero(Temporal[contador])){
					contador++;
					//Ahora revisamos si el siguiente caracter sea un parentesis, para cerrar el si
					if (Temporal[contador]==";"){
						contador++;
						if (palabra(Temporal[contador])){
							contador++;
							if(Temporal[contador]=="==" || Temporal[contador] == "!=" || Temporal[contador] == "<" || Temporal[contador] == ">"){
								contador++;
								if (palabra(Temporal[contador])){
									contador++;
								}else{
									cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
									contador++;
									return false;
								}
							}else{
								cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
								contador++;
								return false;
							}
						}else{
							cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
							contador++;
							return false;
						}
					}else{
						cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
						contador++;
						return false;
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
				contador++;
				return false;
			}	
		}
	}else{
		cout<<"--Error de sintaxis en la instruccion mientras, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
}

bool definir(){
	contador++;
	if (cadenas(Temporal[contador])){
		Variables[ContadorVariables] = Temporal[contador];
		ContadorVariables++;
		contador++;
		cout<<"--Instruccion definir, aceptado como valido"<<endl;
		//Hacemos la recursividad para pasar a la siguiente instruccion
		if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
			EncontrarComandos();
			return true;
		}else{
			return false;
		}
	}else{
		cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
}

bool encender(){
	int centinela = 0;
	int i = 0;
	contador++;
	if (cadenas(Temporal[contador])){
		string variable = Temporal[contador];
		int TamanioArreglo = sizeof Variables / sizeof Variables[0];
		for (i = 0; i<TamanioArreglo; i++){
			//comparamos si el comando existe en  nuestra tabla de simbolos
			if (variable.compare(Variables[i])==0){
				if (cadenas(Temporal[contador])){
					cout<<"--Instruccion encender aceptada, encendiendo durante "<<Temporal[contador + 1]<<" sg"<<endl;
					contador++;
					if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
						EncontrarComandos();
						return true;
					}else{
						return false;
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion encender, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"";
			}
		}
		if (centinela == 0){
			cout<<"--Comando encender no aceptado, no existe la variable "<<Temporal[contador]<< " en memoria"<<endl;
		}
		contador++;
		
	}else{
		cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
}

bool apagar(){
	int centinela = 0;
	int i=0;
	contador++;
	if (cadenas(Temporal[contador])){
		string variable = Temporal[contador];
		int TamanioArreglo = sizeof Variables / sizeof Variables[0];
		for (i = 0; i<TamanioArreglo; i++){
			//comparamos si el comando existe en  nuestra tabla de simbolos
			if (variable.compare(Variables[i])==0){
				if (cadenas(Temporal[contador])){
					centinela = 1;
					cout<<"--Instruccion apagar aceptada, apagando "<<Temporal[contador]<<endl;
					contador++;
					if (Temporal[contador] == "si" || Temporal[contador] == "sino" || Temporal[contador] == "mientras" || Temporal[contador] == "definir" || Temporal[contador] == "encender" || Temporal[contador] == "apagar"){
						EncontrarComandos();
						return true;
					}else{
						return false;
					}
				}else{
					cout<<"--Error de sintaxis en la instruccion encender, no se reconocio como valido"<<endl;
					contador++;
					return false;
				}
			}else{
				cout<<"";
			}
		}
		if (centinela == 0){
			cout<<"--Comando apagar no aceptado, no existe la variable "<<Temporal[contador]<< " en memoria"<<endl;
		}
		contador++;
	}else{
		cout<<"--Error de sintaxis en la instruccion si, no se reconocio como valido"<<endl;
		contador++;
		return false;
	}
}

//Funcion para leer un numero entero
bool numero(string num){
	//Declaramos los estados
	enum TEstado {q0,q1};
	
	TEstado Estado;
	
	int Simbolo;
	bool EsNumero;
	
	int i;
	int longitud;
	
	i = longitud = 0;
	//Iniciamos el estado en q0
	Estado = q0;
	EsNumero = false;
	
	//sacamos la longitud de la cadena para recorrerla por cada caracter
	longitud = num.size();
	
	//recorremos cada caracter para verificar que sean numeros
	while (longitud > i){
		Simbolo  = num[i];
		EsNumero = (Simbolo >= '0' && Simbolo <= '9');
		
		//si se cumple la condicion pasamos al estado q1
		if (Estado==q0){
			if(EsNumero){
				Estado = q1;
			}
		}
		//si se cumple la condicion pasamos al estado q1 otra ves
		if (Estado==q1){
			if(EsNumero){
				Estado = q1;
			}
		}
		//si no es un numero volvemos al estado q0 y terminamos el ciclo
		if (!EsNumero){
			Estado = q0;
			break;
		}
		i++;
	}
	//hacemos la verificacion si estamos en el estado q1 retornamos verdadero, en caso contrario retornamos false
	if (Estado==q1)
		return true;
	else
		return false;
}

bool cadenas(string p){
	int w =0;
	while(w<p.size()){
	//
	if(p[w]>='a' && p[w] <= 'z' ||p[w]>= '0' && p[w] <= '9'){
			return true;
		
			}else{
				return false;
			}
		    w++;
			
	}
}

//funcion para reconocer si es una palabra o cadena lo ingresado
bool palabra(string cadena){
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
