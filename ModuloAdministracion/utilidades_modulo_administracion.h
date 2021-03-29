void menu_administracion();

void menu_administracion(){
	bool loopMenu = true;
	int elegir;

	Cadena opciones[] = {"Registrar Veterinario", "Registrar Usuario Asistente", "Atenciones por Veterinarios","Ranking de Veterinarios por Atenciones"};
	char textoMenu[550];
	formatearMenu("\t\tAdministracion", textoMenu, opciones, 4);
  
	while(loopMenu){
		inputInt(elegir, textoMenu, true, 1, 5);

		system("cls");

		switch(elegir){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				loopMenu = false;
				break;
		}
	}
};