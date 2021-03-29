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