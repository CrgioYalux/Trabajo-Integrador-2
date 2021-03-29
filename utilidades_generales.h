#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cstring>
#include<windows.h>
#include<strings.h>
#include<ctype.h>
#include<math.h>
#include<limits.h>

using namespace std;

void limpiar(int i);
void inputString(char resultado[], const char texto[], int cantMaxCaracteres = 101, int cantMinCaracteres = 1);
void inputFloat(float &resultado, const char texto[], bool permitirLimites = false, int valorMin = INT_MIN, int valorMax = INT_MAX);
void inputInt(int &resultado, const char texto[], bool permitirLimites = false, int valorMin = INT_MIN, int valorMax = INT_MAX);
int comprobarCaracteresFloat(char numero[]);
int cantidadCoincidencias(char cadena1[], char cadena2[]);
int ASCII(char letra);
float convertirCadenaEnFloat(char cadena[]);
int convertirCadenaEnEntero(char cadena[]);


char NUMEROS[] = "0123456789";
char ABC_MAYUS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ABC_MINUS[] = "abcdefghijklmnopqrstuvwxyz";
char CARACTERES[] = "0123456789+-/*?¿!¡";
char SIMBOLOS[] = "+-/*?¿!¡._";

struct Usuario{
	char nombre[11];
	char clave[33];
};
struct Usuario_Asistente {
  Usuario usuario;
  char apellido_nombre[61];
};
struct Usuario_Veterinario {
  Usuario usuario;
  char apellido_nombre[61];
  int matricula;
  int DNI;
  char telefono[26];
};
struct Fecha {
	int day;
	int month;
	int year;
};
struct Mascota {
	char apellido_nombre[61];
	char domicilio[61];
	int DNI;
	char localidad[61];
	Fecha fechaNacimiento;
	float peso;
	char telefono[26];
};
struct Turno {
	int matriculaVeterinario;
	Fecha fecha;
	int DNI;
	char detalleAtencion[381];
};

void inputString(char resultado[], const char texto[], int cantMaxCaracteres, int cantMinCaracteres){
	bool loop = true;
	do{
		char aux_input[cantMaxCaracteres];
		if(strlen(texto) != 0){
			cout << texto << endl;
		}
		cout << "(" << cantMinCaracteres << " - " << (cantMaxCaracteres - 1) << " caracteres): ";
		_flushall();
		gets(aux_input);

		system("cls");

		if(strlen(aux_input) < cantMinCaracteres || strlen(aux_input) > (cantMaxCaracteres - 1)){
			cout << "No cumple con la cantidad minima o maxima de caracteres. Intentelo otra vez." << endl;
			limpiar(1);
		}
		else{
			loop = false;
			strcpy(resultado, aux_input);
		}
	}while(loop);
};

void inputFloat(float &resultado, const char texto[], bool permitirLimites, int valorMin, int valorMax){
	bool loop = true;
	do{
		char aux_input[100];
		if(strlen(texto) != 0){
			cout << texto;
		}
		_flushall();
		gets(aux_input);

		system("cls");

		if(comprobarCaracteresFloat(aux_input)){
			resultado = convertirCadenaEnFloat(aux_input);
			
			if(permitirLimites){
				if(resultado < valorMin || resultado > valorMax){
					cout << "El valor ingresado no es valido. Intentelo otra vez." << endl;
					limpiar(1);
				}
				else{
					loop = false;
				}
			}
			else{
				loop = false;
			}
		}
		else{
			cout << "Solo se permiten caracteres numericos y decimales con '.'. Intentelo otra vez." << endl;
			limpiar(1);
		}
	}while(loop);
};

void inputInt(int &resultado, const char texto[], bool permitirLimites, int valorMin, int valorMax){
	bool loop = true;
	do{
		char aux_input[100];
		if(strlen(texto) != 0){
			cout << texto;
		}
		_flushall();
		gets(aux_input);

		system("cls");

		if(cantidadCoincidencias(aux_input, NUMEROS) == strlen(aux_input)){
			resultado = convertirCadenaEnEntero(aux_input);

			if(permitirLimites){
				if(resultado < valorMin || resultado > valorMax){
					cout << "El valor ingresado no es valido. Intentelo otra vez." << endl;
					limpiar(1);
				}
				else{
					loop = false;
				}
			}
			else{
				loop = false;
			}
		}
		else{
			cout << "Solo se permiten caracteres numericos. Intentelo otra vez." << endl;
			limpiar(1);
		}
	}while(loop);
};

int comprobarCaracteresFloat(char numero[]){
	int cadenaLen = strlen(numero);
	int cont = 0;
	for(int i=0; i<cadenaLen; i++){
		int valorAscii = ASCII(numero[i]);
		if((valorAscii > 47 && valorAscii < 58) || valorAscii == 46){
			cont++;
		}
	}
	if(cont == cadenaLen){
		return 1;
	}
	else{
		return 0;
	}
};

int cantidadCoincidencias(char cadena1[], char cadena2[]){
	int cadena1Len = strlen(cadena1);
	int cadena2Len = strlen(cadena2);
	int contadorCoincidencias = 0;
	
	for(int i=0; i<cadena1Len; i++){
		for(int j=0; j<cadena2Len; j++){
			if(cadena1[i] == cadena2[j]){
				contadorCoincidencias++;
			}
		}
	}
	
	return contadorCoincidencias;
};

int ASCII(char letra){
	int ascii = letra;
	return ascii;
};

float convertirCadenaEnFloat(char cadena[]){
  int potencia = strlen(cadena);
  float resultado = 0;
	int dotpos;
  for(int i=0; i<strlen(cadena); i++){
		int valorAscii = ASCII(cadena[i]);
		if(valorAscii == 46){
			dotpos = potencia;
		}
		else{
    	potencia--;	
			double unidad = pow(10, potencia);
			char caracter = cadena[i];
			float aEntero = caracter - '0';
			float valor = unidad * aEntero;
			resultado = resultado + valor;
		}
  }
	resultado = resultado / pow(10, dotpos);
  return resultado;
};

int convertirCadenaEnEntero(char cadena[]){
  int potencia = strlen(cadena);
  int resultado = 0;
  for(int i=0; i<strlen(cadena); i++){
    potencia--;
    double unidad = pow(10, potencia);
    char caracter = cadena[i];
    int aEntero = caracter - '0';
    int valor = unidad * aEntero;
    resultado = resultado + valor;
  }
	return resultado;
};