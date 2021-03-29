int menu_consultorio();
int menu_autenticacion_consultorio();
int validarAccesoConsultorio(Usuario_Veterinario veterinario);
int iniciarSesionConsultorio();
void sesionTemporal(Usuario_Veterinario veterinario);

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

int menu_autenticacion_consultorio(){
	int elegir;
	bool menuLoop = true;
	Cadena opciones[] = {"Iniciar Sesion"};
	char texto_menu[250];
	formatearMenu("    Menu Autenticacion", texto_menu, opciones, 1);
	while(menuLoop){	
		inputInt(elegir, texto_menu, true, 1, 2);

		system("cls");

		switch (elegir){
			case 1:
				if(iniciarSesionConsultorio()){
					menuLoop = false;
					return 1;
				}
				break;

			case 2:
				menuLoop = false;
				return 0;
		}

	}
};

int validarAccesoConsultorio(Usuario_Veterinario veterinario){
	Usuario_Veterinario datos_guardados_veterinario;
	FILE *UsuariosGuardados;
	UsuariosGuardados = fopen(direccion_archivo_veterinarios, "rb");
	rewind(UsuariosGuardados);
	fread(&datos_guardados_veterinario, sizeof(Usuario_Veterinario), 1, UsuariosGuardados);
	while( !feof(UsuariosGuardados) ){
		if(veterinario.matricula == datos_guardados_veterinario.matricula && strcmp(veterinario.usuario.clave, datos_guardados_veterinario.usuario.clave) == 0){
			cout << "Las credenciales ingresadas son correctas. Bienvenido " << datos_guardados_veterinario.apellido_nombre << "." << endl;
			fclose(UsuariosGuardados);
			return 1;
		}
		fread(&datos_guardados_veterinario, sizeof(Usuario_Veterinario), 1, UsuariosGuardados);
	}
	fclose(UsuariosGuardados);
	return 0;
};


int iniciarSesionConsultorio(){
	if(comprobarExistenciaArchivo(direccion_archivo_veterinarios)){
		Usuario_Veterinario veterinario;
		
		cout << "Ingrese su numero de matricula:" << endl;
		cout << "\n-> ";
		_flushall();
		cin >> veterinario.matricula;
		
		system("cls");

		cout << "Ingrese su clave de usuario:" << endl;
		cout << "\n-> ";
		_flushall();
		gets(veterinario.usuario.clave);

		system("cls");

		if(validarAccesoConsultorio(veterinario)){
			limpiar(1);
			sesionTemporal(veterinario);
			return 1;
		}
		cout << "Las credenciales ingresadas son incorrectas." << endl;	
	}
	else{
		cout << "Aun no existen usuarios registrados." << endl;
		cout << "Registrese primero para poder iniciar sesion." << endl;
	}
	limpiar(1);
	return 0;
};

void sesionTemporal(Usuario_Veterinario veterinario){
	FILE *SesionTemporal;
	SesionTemporal = fopen(direccion_archivo_sesion, "a+b");
	fseek(SesionTemporal, sizeof(Usuario_Veterinario), SEEK_END);
	fwrite(&veterinario, sizeof(Usuario_Veterinario), 1, SesionTemporal);
	fclose(SesionTemporal);
};
