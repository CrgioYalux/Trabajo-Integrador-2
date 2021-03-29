#include "./utilidades_generales.h"
#include "./ModuloConsultorio/utilidades_modulo_consultorio.h"
#include "./ModuloRecepcion/utilidades_modulo_recepcion.h"
#include "./ModuloAdministracion/utilidades_modulo_administracion.h"

int main(){
  int elegir;
	bool menuLoop = true;

	Cadena opciones[] = {"Modulo Consultorio", "Modulo Recepcion", "Modulo Administracion"};
	char texto_menu[350];
	formatearMenu("\t  Menu", texto_menu, opciones, 3);
  
	while(menuLoop){
		inputInt(elegir, texto_menu, true, 1, 4);
		
		system("cls");

		switch(elegir){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				menuLoop = false;
				break;
		}
	}
};
