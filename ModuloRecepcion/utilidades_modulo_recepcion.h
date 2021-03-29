int menu_recepcion();

int menu_recepcion(){
  int elegir;
	bool menuLoop = true;

	Cadena opciones[] = {"Registrar Mascota", "Registrar Turno", "Listado de Atenciones por Veterinario y Fecha"};
	char texto_menu[350];
	formatearMenu("\t\t     Menu", texto_menu, opciones, 3);

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
        break;
		}
	}
};