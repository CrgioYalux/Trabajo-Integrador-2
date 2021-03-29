#include "./utilidades_generales.h"
#include "./direcciones_archivos.h"
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
				if(menu_autenticacion_consultorio()){
					menu_consultorio();
				};		
				break;
			case 2:
				if(menu_autenticacion_recepcion()){
					menu_recepcion();
				};
				break;
			case 3:
				if(menu_autenticacion_administracion()){
					menu_administracion();
				};
				break;
			case 4:
				menuLoop = false;
				break;
		}
	}
};
