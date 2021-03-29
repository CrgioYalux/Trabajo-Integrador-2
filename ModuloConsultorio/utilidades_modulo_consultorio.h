int menu_consultorio();

int menu_consultorio(){
	int elegir;
	bool menuLoop = true;

	Cadena opciones[] = {"Visualizar Lista de Espera de Turnos", "Registrar evolucion de la Mascota"};	
	char texto_menu[350];
	formatearMenu("\t\tMenu",texto_menu,opciones,2);

	while(menuLoop){
		inputInt(elegir, texto_menu, true, 1, 3);

		system("cls");
		
		switch(elegir){
			case 1:
				break;
			case 2:
				break;
			case 3:
				menuLoop = false;
				break;
		}
	}
};