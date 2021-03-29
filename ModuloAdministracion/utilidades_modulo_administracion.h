int iniciarSesionAdministracion();
int validarAcceso(Usuario buscar_usuario);

void menu_administracion();
int menu_autenticacion_administracion();

void registrarUsuario();
void registrarUsuarioAsistente();
void registrarUsuarioVeterinario();

void guardarUsuario(Usuario usuario);
void guardarUsuarioAsistente(Usuario_Asistente asistente);
void guardarUsuarioVeterinario(Usuario_Veterinario veterinario);

int comprobarDisponibilidadNombre_Usuario(char nombreUsuario[]);
int comprobarDisponibilidadNombre_UsuarioAsistente(char nombreUsuario[]);
int comprobarDisponibilidadNombre_UsuarioVeterinario(char nombreUsuario[]);

int iniciarSesionAdministracion(){
	if(comprobarExistenciaArchivo(direccion_archivo_usuarios)){
		Usuario usuario;

		cout << "Ingrese su nombre de usuario: " << endl;
		cout << "\n-> ";
		_flushall();
		gets(usuario.nombre);

		system("cls");

		cout << "Ingrese su clave de usuario: " << endl;
		cout << "\n-> ";
		_flushall();
		gets(usuario.clave);

		system("cls");

		if(validarAcceso(usuario)){
			cout << "Las credenciales ingresadas son correctas. Bienvenido " << usuario.nombre << "." << endl;
			cout << "Presione cualquier tecla para ir al menu." << endl;
			limpiar(0);
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

int validarAcceso(Usuario buscar_usuario){
	FILE *UsuariosGuardados;
	UsuariosGuardados = fopen(direccion_archivo_usuarios, "rb");
	Usuario usuario;
	rewind(UsuariosGuardados);
	fread(&usuario, sizeof(Usuario), 1, UsuariosGuardados);
	while( !feof(UsuariosGuardados) ){
		if(strcmp(usuario.nombre, buscar_usuario.nombre) == 0 && strcmp(usuario.clave, buscar_usuario.clave) == 0){
			fclose(UsuariosGuardados);
			return 1;
		}
		fread(&usuario, sizeof(Usuario), 1, UsuariosGuardados);
	}
	fclose(UsuariosGuardados);
	return 0;
};


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
				registrarUsuarioVeterinario();
				break;
			case 2:
				registrarUsuarioAsistente();
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

int menu_autenticacion_administracion(){
	bool loopMenu = true;
	int elegir;

	Cadena opciones[] = {"Iniciar Sesion", "Registrarse como nuevo usuario"};
	char textoMenu[350];
	formatearMenu("     Modulo administracion", textoMenu, opciones, 2);
	while(loopMenu){
		inputInt(elegir, textoMenu, true, 1, 3);		

		system("cls");

		switch(elegir){
			case 1:
				if(iniciarSesionAdministracion()){
					elegir = false;
					return 1;
				}
				break;
			case 2:
				registrarUsuario();
				break;
			case 3:
				elegir = false;
				return 0;
		}
	}
};

void registrarUsuario(){
	Usuario usuario;

	do{
		inputString(usuario.nombre, "Ingrese un nombre de usuario.", 11);
		
    if(!comprobarDisponibilidadNombre_Usuario(usuario.nombre)){
      cout << "El nombre de usuario ingresado ya esta en uso." << endl;
      cout << "Debe elegir uno distinto." << endl;
      cout << endl;
      limpiar(1);
	  }
	}while(!comprobarNombreUsuario(usuario.nombre) || !comprobarDisponibilidadNombre_Usuario(usuario.nombre));
  cout << "El nombre de usuario ingresado es valido." << endl;
	limpiar(1);
	
	do{
		inputString(usuario.clave, "Ingrese una clave de usuario.", 33, 6);
	}while(!comprobarClaveUsuario(usuario.clave));
  cout << "La clave de usuario ingresada es valida." << endl;
	limpiar(1);
	
	guardarUsuario(usuario);
	
	cout << "Credenciales registradas:" << endl;
	cout << "Nombre de usuario: " << usuario.nombre << endl;
	cout << "Clave de usuario: " << usuario.clave << endl;
	
	cout << endl;
	limpiar(1);
};

void registrarUsuarioAsistente(){
  Usuario_Asistente asistente;
  
  do{
		inputString(asistente.apellido_nombre, "Ingrese apellido y nombre del asistente.", 61);
  }while(!comprobarApellidoYNombre(asistente.apellido_nombre));
  cout << "El apellido y nombre ingresados son validos." << endl;
  limpiar(1);

  do{
		inputString(asistente.usuario.nombre, "Ingrese un nombre de usuario.", 11, 6);
    if(!comprobarDisponibilidadNombre_UsuarioAsistente(asistente.usuario.nombre)){
      cout << "El nombre de usuario ingresado ya esta en uso." << endl;
      cout << "Debe elegir uno distinto." << endl;
      limpiar(1);
    }
  }while(!comprobarNombreUsuario(asistente.usuario.nombre) || !comprobarDisponibilidadNombre_UsuarioAsistente(asistente.usuario.nombre));
  cout << "El nombre de usuario ingresado es valido." << endl;
  limpiar(1);

  do{
		inputString(asistente.usuario.clave, "Ingrese una clave de usuario.", 33, 6);
  }while(!comprobarClaveUsuario(asistente.usuario.clave));
  cout << "La clave de usuario ingresada es valida." << endl;
  limpiar(1);

	guardarUsuarioAsistente(asistente);

	cout << "Credenciales registradas:" << endl;
	cout << "Apellido y nombre:" << asistente.apellido_nombre << endl;
	cout << "Nombre de usuario: " << asistente.usuario.nombre << endl;
	cout << "Clave de usuario: " << asistente.usuario.clave << endl;

	cout << endl;
	limpiar(1);
};

void registrarUsuarioVeterinario(){
	Usuario_Veterinario veterinario;
	bool auxloop = true;

	do{
		inputString(veterinario.apellido_nombre, "Ingrese apellido y nombre del veterinario.", 61);
	}while(!comprobarApellidoYNombre(veterinario.apellido_nombre));
	cout << "El apellido y nombre ingresados son validos." << endl;
	limpiar(1);

	do{
		inputString(veterinario.usuario.nombre, "Ingrese un nombre de usuario.", 11, 6);
		if(!comprobarDisponibilidadNombre_UsuarioVeterinario(veterinario.usuario.nombre)){
      cout << "El nombre de usuario ingresado ya esta en uso." << endl;
      cout << "Debe elegir uno distinto." << endl;
      limpiar(1);
    }
	}while(!comprobarNombreUsuario(veterinario.usuario.nombre) || !comprobarDisponibilidadNombre_UsuarioVeterinario(veterinario.usuario.nombre));
	cout << "El nombre de usuario ingresado es valido." << endl;
	limpiar(1);

	do{
		inputString(veterinario.usuario.clave, "Ingrese una clave de usuario.", 33, 6);
	}while(!comprobarClaveUsuario(veterinario.usuario.clave));
	cout << "La clave ingresada es valida." << endl;
	limpiar(1);

	inputInt(veterinario.matricula, "Ingrese el numero de matricula: ", true, 1);
	cout << "El numero de matricula ingresado es valido." << endl;
	limpiar(1);

	inputInt(veterinario.DNI, "Ingrese el numero de DNI: ", true, 1);
	cout << "El numero de DNI ingresado es valido." << endl;
	limpiar(1);

	do{
		inputString(veterinario.telefono, "Ingrese el numero de telefono.", 26, 1);
		if(cantidadCoincidencias(veterinario.telefono, NUMEROS) != strlen(veterinario.telefono)){
			cout << "Solo se aceptan caracteres numericos." << endl;
			cout << "Por favor, ingreselo nuevamente." << endl;
			limpiar(1);
		}
		else{
			auxloop = false;
		}
	}while(auxloop);
	cout << "El numero de telefono ingresado es valido." << endl;
	limpiar(1);

	guardarUsuarioVeterinario(veterinario);
	
	cout << "Credenciales registradas:" << endl;
	cout << "Apellido y nombre: " << veterinario.apellido_nombre << endl;
	cout << "Nombre de usuario: " << veterinario.usuario.nombre << endl;
	cout << "Clave de usuario: " << veterinario.usuario.clave << endl;
	cout << "Numero de matricula: " << veterinario.matricula << endl;
	cout << "Numero de DNI: " << veterinario.DNI << endl;
	cout << "Numero de telefono: " << veterinario.telefono << endl;
	
	cout << endl;
	limpiar(1);
};

void guardarUsuario(Usuario nuevo_usuario){
	FILE *UsuariosGuardados;

	if(!comprobarExistenciaArchivo(direccion_archivo_usuarios)){
		if(strcmp(direccion_archivo_usuarios, "./ModuloAdministracion/Datos/Usuarios.dat") == 0){
			system("cd ModuloAdministracion && mkdir Datos");
		}
		else{
			system("mkdir Datos");
		}
	}
	
	UsuariosGuardados = fopen(direccion_archivo_usuarios, "a+b");
	fseek(UsuariosGuardados, sizeof(Usuario), SEEK_END);
	fwrite(&nuevo_usuario, sizeof(Usuario), 1, UsuariosGuardados);
	fclose(UsuariosGuardados);
};

void guardarUsuarioAsistente(Usuario_Asistente nuevo_usuario_asistente){
  FILE *UsuariosAsistentesGuardados;
	UsuariosAsistentesGuardados = fopen(direccion_archivo_asistentes, "a+b");
	fseek(UsuariosAsistentesGuardados, sizeof(Usuario_Asistente), SEEK_END);
	fwrite(&nuevo_usuario_asistente, sizeof(Usuario_Asistente), 1, UsuariosAsistentesGuardados);
	fclose(UsuariosAsistentesGuardados);
};

void guardarUsuarioVeterinario(Usuario_Veterinario nuevo_usuario_veterinario){
	FILE *UsuariosVeterinariosGuardados;
	UsuariosVeterinariosGuardados = fopen(direccion_archivo_veterinarios, "a+b");
	fseek(UsuariosVeterinariosGuardados, sizeof(Usuario_Veterinario), SEEK_END);
	fwrite(&nuevo_usuario_veterinario, sizeof(Usuario_Veterinario), 1, UsuariosVeterinariosGuardados);
	fclose(UsuariosVeterinariosGuardados);
};

int comprobarDisponibilidadNombre_UsuarioVeterinario(char nombreUsuario[]){
	if(comprobarExistenciaArchivo(direccion_archivo_asistentes)){
		FILE *UsuariosVeterinariosGuardados;
		Usuario_Veterinario veterinario;
		UsuariosVeterinariosGuardados = fopen(direccion_archivo_asistentes, "rb");
		rewind(UsuariosVeterinariosGuardados);
		fread(&veterinario, sizeof(Usuario_Veterinario), 1, UsuariosVeterinariosGuardados);
		while( !feof(UsuariosVeterinariosGuardados) ){
			if(strcmp(veterinario.usuario.nombre, nombreUsuario) == 0){
				fclose(UsuariosVeterinariosGuardados);
				return 0;
			}
			fread(&veterinario, sizeof(Usuario_Veterinario), 1, UsuariosVeterinariosGuardados);
		}
		fclose(UsuariosVeterinariosGuardados);	
	}
	return 1;
};

int comprobarDisponibilidadNombre_Usuario(char nombreUsuario[]){
	if(comprobarExistenciaArchivo(direccion_archivo_usuarios)){
		FILE *UsuariosGuardados;
		UsuariosGuardados = fopen(direccion_archivo_usuarios, "rb");
		Usuario usuario;
		rewind(UsuariosGuardados);
		fread(&usuario, sizeof(Usuario), 1, UsuariosGuardados);
		while( !feof(UsuariosGuardados) ){
			if(strcmp(usuario.nombre, nombreUsuario) == 0){
				fclose(UsuariosGuardados);
				return 0;
			}
			fread(&usuario, sizeof(Usuario), 1, UsuariosGuardados);
		}
		fclose(UsuariosGuardados);
	}
	return 1;
};

int comprobarDisponibilidadNombre_UsuarioAsistente(char nombreUsuario[]){
	if(comprobarExistenciaArchivo(direccion_archivo_asistentes)){
		FILE *UsuariosAsistentesGuardados;
		UsuariosAsistentesGuardados = fopen(direccion_archivo_asistentes, "rb");
	  Usuario_Asistente asistente;
	  rewind(UsuariosAsistentesGuardados);
	  fread(&asistente, sizeof(Usuario_Asistente), 1, UsuariosAsistentesGuardados);
	  while( !feof(UsuariosAsistentesGuardados) ){
  		if(strcmp(asistente.usuario.nombre, nombreUsuario) == 0){
			  fclose(UsuariosAsistentesGuardados);
			  return 0;
		  }
			fread(&asistente, sizeof(Usuario_Asistente), 1, UsuariosAsistentesGuardados);
  	}
	  fclose(UsuariosAsistentesGuardados);
	}
	return 1;
};