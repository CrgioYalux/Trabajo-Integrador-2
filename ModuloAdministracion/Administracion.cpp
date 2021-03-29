#include "../utilidades_generales.h"
#include "./direcciones_archivos.h"
#include "./utilidades_modulo_administracion.h"

int main(){
	if(menu_autenticacion_administracion()){
		menu_administracion();
	}
	return 0;	
}

