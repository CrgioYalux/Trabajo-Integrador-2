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

char NUMEROS[] = "0123456789";
char ABC_MAYUS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ABC_MINUS[] = "abcdefghijklmnopqrstuvwxyz";
char CARACTERES[] = "0123456789+-/*?¿!¡";
char SIMBOLOS[] = "+-/*?¿!¡._";

typedef char Cadena[100];

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

struct Historia_Clinica {
	char apellido_nombre[61];
	int DNI;
	char localidad[61];
	char edad[61];
	float peso;
	char evolucion[381];
	char redactadaPor[61];
	Fecha fechaAtencion;
};

struct ContadorAtenciones {
	char apellido_nombre_veterinario[61];
	int cantAtenciones;
};

void limpiar(int i);
void inputString(char resultado[], const char texto[], int cantMaxCaracteres = 101, int cantMinCaracteres = 1);
void inputFloat(float &resultado, const char texto[], bool permitirLimites = false, int valorMin = INT_MIN, int valorMax = INT_MAX);
void inputInt(int &resultado, const char texto[], bool permitirLimites = false, int valorMin = INT_MIN, int valorMax = INT_MAX);
int comprobarCaracteresFloat(char numero[]);
int cantidadCoincidencias(char cadena1[], char cadena2[]);
int ASCII(char letra);
void formatearFecha(Fecha fecha);
void enteroACadena(int entero, char resultado[]);
int descomponerNumero(int numero);
void crearArregloDesdeInt(int numero, int cantUnidades, int arregloResultado[]);
float convertirCadenaEnFloat(char cadena[]);
int convertirCadenaEnEntero(char cadena[]);
int lenCadenaMasLarga(Cadena cadenas[], int cantCadenas);
void crearSeparador(char resultado[], int len, const char separador);
char enteroACaracter(int numero);
void formatearMenu(const char tituloMenu[], char output[], Cadena opciones[], int cantOpciones);
int esMinuscula(char nombreUsuario[]);
void aMinuscula(char cadena[], char copia[]);
int comprobarClaveUsuario(char claveUsuario[]);
int comprobarNombreUsuario(char nombreUsuario[]);
int comprobarApellidoYNombre(char apellidoYNombre[]);
int analizarCadenaPorCaracteresNoAlfanumericos(char cadena[]);
int analizarCadenaPorCaracteresSoloAlfabeticos(char cadena[]);
int analizarCadenaPorConsecuciones_Letras(char cadena[], char consecucionEncontrada[]);
int analizarCadenaPorConsecuciones_Numeros(char cadena[], char consecucionEncontrada[]);
int comprobarExistenciaArchivo(const char direccion[]);


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

void formatearFecha(Fecha fecha){
	if(fecha.day < 10){
		cout << "0" << fecha.day << "/";
	}
	else{
		cout << fecha.day << "/";
	}
	if(fecha.month < 10){
		cout << "0" << fecha.month << "/";
	}
	else{
		cout << fecha.month << "/";	
	}
	cout << fecha.year;
};

void enteroACadena(int entero, char resultado[]){
	int enteroLen = descomponerNumero(entero);
	int arreglo_entero[enteroLen]; 
	crearArregloDesdeInt(entero, enteroLen, arreglo_entero);

	for(int i = 0; i < enteroLen; i++){
		resultado[i] = enteroACaracter(arreglo_entero[i]);
	}
};

int descomponerNumero(int numero){
	int unidades = 0;
	while(true){
		if(numero == 0){
			return unidades;
		}
		numero /= 10;				
		unidades++;
	}
};

void crearArregloDesdeInt(int numero, int cantUnidades, int arregloResultado[]){
	for(int i=cantUnidades-1; i>=0; i--){
		arregloResultado[i] = numero % 10;
		numero /=  10;
	}
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

int lenCadenaMasLarga(Cadena cadenas[], int cantCadenas){
	int lenCadena = 0;
	for(int i = 0; i<cantCadenas; i++){
		if(strlen(cadenas[i]) > lenCadena){
			lenCadena = strlen(cadenas[i]);
		} 
	}
	return lenCadena;
};

void crearSeparador(char resultado[], int len, const char separador){
	char texto_separador[len];
	for(int i=0; i<len-2; i++){
		texto_separador[i] = separador;
	}
	texto_separador[len-2] = '\n';
	texto_separador[len-1] = '\0';
	strcpy(resultado, texto_separador);
};

char enteroACaracter(int numero){
    return numero + '0';
};

void formatearMenu(const char tituloMenu[], char output[], Cadena opciones[], int cantOpciones){
	int resultadoLen = cantOpciones * 100 + 50;
	char resultado[resultadoLen] = {'\0'};

	char minimunLen = strlen("Cerrar la aplicacion\n");
	int len = lenCadenaMasLarga(opciones, cantOpciones);
	if(len < minimunLen){
		len = minimunLen;
	}
	char separador[len+6];
	crearSeparador(separador, len+4, '=');

	strcat(resultado, tituloMenu);
	strcat(resultado, "\n");
	strcat(resultado, separador);

	for(int i=0; i<cantOpciones; i++){
		char numero = enteroACaracter(i+1);
		char numero_opcion[] = {numero, '.', '\0'};
		char opcion[100] = {'\0'};
		strcat(opcion, numero_opcion);
		strcat(opcion, opciones[i]);
		strcat(opcion, "\n");
		strcat(resultado, opcion);
	}

	char numero = enteroACaracter(cantOpciones+1);
	char numero_opcion[] = {numero, '.', '\0'};
	char opcion[100] = {'\0'};
	strcat(opcion, "\n");
	strcat(opcion, numero_opcion);	
	strcat(opcion, "Cerrar la aplicacion\n");
	strcat(resultado, opcion);
	strcat(resultado, separador);
	strcat(resultado, "Ingrese una opcion: ");
	strcpy(output, resultado);
};

int esMinuscula(char nombreUsuario[]){
	
	char primerLetra = nombreUsuario[0];
	
	for(int i=0; i<26; i++){
		if(primerLetra == ABC_MAYUS[i]){
			return 0;
		}
	}
	
	return 1;
};

void aMinuscula(char cadena[], char copia[]) {
	int cadenaLen = strlen(cadena);
	int index = 0;
  	for (int i = 0; i < cadenaLen; i++) {
  		int valorASCII = cadena[i];
  		if(valorASCII>64 && valorASCII<91){
  			copia[index] = tolower(cadena[i]);		
  			index++;
  		}
  		else if(valorASCII>96 && valorASCII<123){
  			copia[index] = cadena[i];
  			index++;
  		}
  	}
};

int comprobarClaveUsuario(char claveUsuario[]){
	int claveUsuarioLen = strlen(claveUsuario);
	char consecucionEncontrada_Numeros[4];
	char consecucionEncontrada_Letras[2];
	
	if(analizarCadenaPorCaracteresNoAlfanumericos(claveUsuario)){
		cout << "La clave de usuario no puede tener ningun caracter de puntuacion, ni acentos, ni espacios." << endl;
		cout << "Solo se permiten caracteres alfanumericos." << endl;
		cout << "Por favor, ingresela nuevamente" << endl;
		
		limpiar(1);

		return 0;
	}

	// comprobar que contiene mayuscula, minuscula y numero
	if(cantidadCoincidencias(claveUsuario, ABC_MINUS) < 1 || cantidadCoincidencias(claveUsuario, ABC_MAYUS) < 1 || cantidadCoincidencias(claveUsuario, NUMEROS) < 1){
		cout << "La clave de usuario debe tener al menos una letra mayuscula, una letra minuscula y un numero." << endl;
		cout << "Por favor, ingresela nuevamente." << endl;
		
		limpiar(1);
		
		return 0;
	}
	
	// comprobar que no contiene caracteres numericos consecutivos
	if(analizarCadenaPorConsecuciones_Numeros(claveUsuario, consecucionEncontrada_Numeros)){
		cout << "La clave de usuario no debe tener mas de 3 caracteres numericos consecutivos." << endl;
		cout << "Se encontro la siguiente secuencia de caracteres consecutivos: " << "\"...";
		for(int i=0; i<4; i++){
			cout << consecucionEncontrada_Numeros[i];
		}
		cout << "...\"" << endl;
		cout << "Por favor, ingresela nuevamente.";
		
		limpiar(1);
		
		return 0;		
	}
	
	// comprobar que no contiene letras consecutivas
	if(analizarCadenaPorConsecuciones_Letras(claveUsuario, consecucionEncontrada_Letras)){
		cout << "La clave de usuario no debe tener mas de 2 letras alfabeticamente consecutivas." << endl;
		cout << "Se encontro la siguiente secuencia de caracteres consecutivos: " << "\"...";
		for(int i=0; i<2; i++){
			cout << consecucionEncontrada_Letras[i];
		}
		cout << "...\"" << endl;
		cout << "Por favor, ingresela nuevamente." << endl;
		
		limpiar(1);
		
		return 0;		
	}
	return 1;
};


int comprobarNombreUsuario(char nombreUsuario[]){
	char ABC_MAYUS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char ABC_MINUS[] = "abcdefghijklmnopqrstuvwxyz";
	char CARACTERES[] = "0123456789+-/*?¿!¡";
	int nombreUsuarioLen = strlen(nombreUsuario);

	// comprobar si comienza con min�scula
	if(!esMinuscula(nombreUsuario)){
		cout << "El nombre de usuario debe comenzar con una letra minuscula." << endl; 
		cout << "Por favor, ingreselo nuevamente." << endl;
		cout << endl;
		limpiar(1);
		
		return 0;
	}
	
	// comprobar cantidad de mayusculas
	if(cantidadCoincidencias(nombreUsuario, ABC_MAYUS) < 2){
		cout << "El nombre de usuario debe contener al menos 2 letras mayusculas." << endl;
		cout << "Por favor, ingreselo nuevamente." << endl;
		cout << endl;
		limpiar(1);
		
		return 0;
	}
	
	//comprobar cantidad de digitos
	if(cantidadCoincidencias(nombreUsuario, CARACTERES) > 3){
		cout << "El nombre de usuario debe contener como maximo 3 digitos." << endl; 
		cout << "Por favor, ingreselo nuevamente." << endl;
		cout << endl;
		limpiar(1);
		
		return 0;
	}
	return 1;
};

int comprobarApellidoYNombre(char apellidoYNombre[]){
  int apellidoYNombreLen = strlen(apellidoYNombre);

  if(apellidoYNombreLen <= 0 || apellidoYNombreLen > 60){
    cout << "La longitud del apellido y nombre ingresado es invalida." << endl;
    cout << "Por favor, ingreselo nuevamente." << endl;

    limpiar(1);

    return 0;
	} 
}

int analizarCadenaPorCaracteresNoAlfanumericos(char cadena[]){
	int cadenaLen = strlen(cadena);

	for(int i=0; i<cadenaLen; i++){
		int valorASCII = ASCII(cadena[i]);
		if(valorASCII < 48 || (valorASCII > 57 && valorASCII < 65) || (valorASCII > 90 && valorASCII < 97) || valorASCII > 122){
			return 1;
		}
	}
	return 0;
};

int analizarCadenaPorCaracteresSoloAlfabeticos(char cadena[]){
  int cadenaLen = strlen(cadena);

  for(int i=0; i<cadenaLen; i++){
    int valorASCII = ASCII(cadena[i]);
    if(!(valorASCII > 64 && valorASCII < 91 || valorASCII > 96 && valorASCII < 123 || valorASCII == 32)){
      return 1;
    }
  }

  return 0;
};

int analizarCadenaPorConsecuciones_Letras(char cadena[], char consecucionEncontrada[]){
	int cadenaLen = strlen(cadena);
	char copiaEnMinusculas[cadenaLen];
	aMinuscula(cadena, copiaEnMinusculas);
	
	int index = 0;
	char aux;
	
	bool hayOrdenAscendente;
	for(int i=0; i<cadenaLen; i++){
		hayOrdenAscendente = true;
		int valorASCII = ASCII(copiaEnMinusculas[i]);
		
		if(valorASCII > 96 && valorASCII < 123){
			
			if(i != 0 && aux == valorASCII - 1){
				consecucionEncontrada[index] = cadena[i];
				index++;
				for(int j=0; j<2; j++){
					if(consecucionEncontrada[j] == -1){
						hayOrdenAscendente = false;
					}
				}
				if(hayOrdenAscendente){
					return 1;
				} 
			}
			else{
				consecucionEncontrada[0] = cadena[i];
				consecucionEncontrada[1] = -1;
				index = 1;
			}
			aux = ASCII(copiaEnMinusculas[i]);
		}
	}
	return 0;
};


int analizarCadenaPorConsecuciones_Numeros(char cadena[], char consecucionEncontrada[]){
	int cadenaLen = strlen(cadena);
	int index = 0;
	char aux;
	
	bool hayOrdenAscendente;
	for(int i=0; i<cadenaLen; i++){
		hayOrdenAscendente = true;
		int valorASCII = ASCII(cadena[i]);
		if(valorASCII > 47 && valorASCII < 58){
			if(i != 0 && aux == valorASCII - 1){
				consecucionEncontrada[index] = cadena[i];
				index++;
				for(int j=0; j<4; j++){
					if(consecucionEncontrada[j] == -1){
						hayOrdenAscendente = false;
					}
				}
				if(hayOrdenAscendente) return 1;
			}
			else{
				consecucionEncontrada[0] = cadena[i];
				consecucionEncontrada[1] = -1;
				consecucionEncontrada[2] = -1;
				consecucionEncontrada[3] = -1;
				index = 1;
			}
			aux = cadena[i];
		}
	}
	
	bool hayOrdenDescendente;
	for(int i=0; i<cadenaLen; i++){
		hayOrdenDescendente = true;
		int valorASCII = ASCII(cadena[i]);
		if(valorASCII > 47 && valorASCII < 58){		
			if(i != 0 && aux == valorASCII + 1){
				consecucionEncontrada[index] = cadena[i];
				index++;
				for(int j=0; j<4; j++){
					if(consecucionEncontrada[j] == -1){
						hayOrdenDescendente = false;
					}
				}
				if(hayOrdenDescendente) return 1;
			}
			else{
				consecucionEncontrada[0] = cadena[i];
				consecucionEncontrada[1] = -1;
				consecucionEncontrada[2] = -1;
				consecucionEncontrada[3] = -1;
				index = 1;
			}
			aux = cadena[i];
		}
	}
	return 0;
};


int comprobarExistenciaArchivo(const char direccion[]){
	FILE *Archivo;
	Archivo = fopen(direccion, "rb");
	if(Archivo == NULL){
		fclose(Archivo);
		return 0;
	}
	fclose(Archivo);
	return 1;	
};


