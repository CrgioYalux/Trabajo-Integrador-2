int menu_recepcion();
int menu_autenticacion_recepcion();
void registrarTurno();
void registrarMascota();
void guardarTurno(Turno nuevo_turno);
void guardarMascota(Mascota nueva_mascota);
int comprobarExistenciaMatricula(int matricula);
int buscarMascotaPorDNI(int DNI);
int iniciarSesionRecepcion();
int validarAccesoRecepcion(Usuario_Asistente asistente);
void listarAtenciones();

int menu_recepcion(){
	system("cls");
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
				registrarMascota();
				break;
			case 2:
				registrarTurno();
				break;
			case 3:
				listarAtenciones();
        break;
      case 4:
				menuLoop = false;
        break;
		}
	}
};

int menu_autenticacion_recepcion(){
	system("cls");
	int elegir;
	bool menuLoop = true;
	Cadena opciones[] = {"Iniciar Sesion"};
	char texto_menu[250];
	formatearMenu("   Menu Autenticacion", texto_menu, opciones, 1);
	while(menuLoop){	
			inputInt(elegir, texto_menu, true, 1, 2);

			system("cls");

			switch (elegir){
				case 1:
					if(iniciarSesionRecepcion()){
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

void registrarTurno(){

	if(comprobarExistenciaArchivo(direccion_archivo_mascotas)){
	Turno nuevo_turno;
	bool loop = true;
		// input DNI dueño
		inputInt(nuevo_turno.DNI, "Ingrese el DNI de el due\244o de la mascota: ", true, 1);
		if(buscarMascotaPorDNI(nuevo_turno.DNI)){
			// input Matricula
			do{
			inputInt(nuevo_turno.matriculaVeterinario, "Ingrese la matricula del veterinario: ", true, 1);
			if(comprobarExistenciaMatricula(nuevo_turno.matriculaVeterinario)){
				loop = false;
				cout << "Matricula del veterinario ingresada correctamente." << endl;
				limpiar(1);
			}
			else{
				cout << "La matricula ingresada no pertenece a ningun veterinario. Intentelo otra vez." << endl;
				limpiar(1);
			}
		}while(loop);

		// reiniciar loop
		loop = true;

		// input fecha de nacimiento
		cout << "Ingrese la fecha del turno (en numeros):" << endl;		
		inputInt(nuevo_turno.fecha.day, "Dia: ", true, 1, 30);
		inputInt(nuevo_turno.fecha.month, "Mes: ", true, 1, 12);
		inputInt(nuevo_turno.fecha.year, "A\244o: ", true, 1980, 2021);
		cout << "Fecha del turno ingresada correctamente." << endl;
		limpiar(1);

		// input detalles atencion
		inputString(nuevo_turno.detalleAtencion, "Ingrese los detalles de la atencion.", 381);
		cout << "Detalles de la atencion ingresados correctamente." << endl;
		limpiar(1);
		
		guardarTurno(nuevo_turno);

		cout << "Datos del turno registrados:" << endl;
		cout << "Matricula del veterinario: " << nuevo_turno.matriculaVeterinario << endl;
		cout << "Fecha: ";
		formatearFecha(nuevo_turno.fecha);
		cout << endl;
		cout << "DNI del due\244o de la mascota: " << nuevo_turno.DNI << endl;
		cout << "Detalles de la atencion: " << nuevo_turno.detalleAtencion << endl;

		limpiar(1);
		}
		else{
			cout << "El DNI ingresado no coincide con el de una mascota registrada." << endl;
			limpiar(1);
		}
	}
	else{
		cout << "No hay mascotas registradas." << endl;
		cout << "Registre a una mascota primero para luego poder sacarle un turno." << endl;
		limpiar(1);
	}
};

void registrarMascota(){
	Mascota nueva_mascota;

	// input apellido y nombre
	bool loop = true;
	do{
		inputString(nueva_mascota.apellido_nombre, "Ingrese el apellido y nombre de la mascota.\nSe entiende por su apellido a el de su due\244o: ", 61);
		if(cantidadCoincidencias(nueva_mascota.apellido_nombre, NUMEROS) > 0){
			cout << "No se aceptan caracteres numericos. Intentelo otra vez." << endl;
			limpiar(1);
		}
		else{
			cout << "Apellido y nombre de la mascota ingresados correctamente." << endl;
			limpiar(1);
			loop = false;
		}
	}while(loop);

	// input domicilio
	inputString(nueva_mascota.domicilio, "Ingrese el domicilio: ", 61);
	cout << "Domicilio ingresado correctamente." << endl;
	limpiar(1);

	// input DNI del dueño
	inputInt(nueva_mascota.DNI, "Ingrese el DNI de el due\244o de la mascota: ", true, 0);
	cout << "DNI de el due\244o de la mascota registrado correctamente." << endl;
	limpiar(1);
	

	// input localidad
	inputString(nueva_mascota.localidad, "Ingrese la localidad: ", 61);
	cout << "Localidad ingresada correctamente." << endl;
	limpiar(1);

	// input fecha de nacimiento
	cout << "Ingrese la fecha de nacimiento de la mascota (en numeros):" << endl;		
	inputInt(nueva_mascota.fechaNacimiento.day, "Dia: ", true, 1, 30);
	inputInt(nueva_mascota.fechaNacimiento.month, "Mes: ", true, 1, 12);
	inputInt(nueva_mascota.fechaNacimiento.year, "A\244o: ", true, 1980, 2021);
	cout << "Fecha de nacimiento de la mascota ingresada correctamente." << endl;
	limpiar(1);

	// input peso de la mascota
	inputFloat(nueva_mascota.peso, "Ingrese el peso de la mascota (en Kg).\nUtilice '.' en caso de querer indicar decimales (Ej: 5.5): ", true, 0);
	cout << "Peso de la mascota ingresado correctamente." << endl;
	limpiar(1);

	// reiniciar loop
	loop = true;

	// input telefono
	do{
		inputString(nueva_mascota.telefono, "Ingrese el numero de telefono: ", 26);
		if(cantidadCoincidencias(nueva_mascota.telefono, NUMEROS) != strlen(nueva_mascota.telefono)){
			cout << "Solo se aceptan caracteres numericos. Intentelo otra vez." << endl;
			limpiar(1);
		}
		else{
			cout << "Numero de telefono ingresado correctamente." << endl;
			limpiar(1);
			loop = false;
		}
	}while(loop);

	guardarMascota(nueva_mascota);

	// mostrar datos
	cout << "Credenciales guardadas." << endl;
	cout << "Apellido y nombre de la mascota: " << nueva_mascota.apellido_nombre << endl;
	cout << "Domicilio: " << nueva_mascota.domicilio << endl;
	cout << "DNI del due\244o: " << nueva_mascota.DNI << endl;
	cout << "Localidad: " << nueva_mascota.localidad << endl;
	cout << "Fecha de Nacimiento:";
	formatearFecha(nueva_mascota.fechaNacimiento);
	cout << endl;
	cout << "Peso de la mascota: " << nueva_mascota.peso << " Kg" << endl;
	cout << "Telefono: " << nueva_mascota.telefono << endl;
	limpiar(1);
};

void guardarTurno(Turno nuevo_turno){
	FILE *TurnosGuardados;
	TurnosGuardados = fopen(direccion_archivo_turnos, "a+b");
	fseek(TurnosGuardados, sizeof(Turno), SEEK_END);
	fwrite(&nuevo_turno, sizeof(Turno), 1, TurnosGuardados);
	fclose(TurnosGuardados);
};

void guardarMascota(Mascota nueva_mascota){
	FILE *MascotasGuardadas;
	MascotasGuardadas = fopen(direccion_archivo_mascotas, "a+b");
	fseek(MascotasGuardadas, sizeof(Mascota), SEEK_END);
	fwrite(&nueva_mascota, sizeof(Mascota), 1, MascotasGuardadas);
	fclose(MascotasGuardadas);
};

int comprobarExistenciaMatricula(int matricula){
	FILE *UsuariosGuardados;
	Usuario_Veterinario veterinario;
	UsuariosGuardados = fopen(direccion_archivo_veterinarios, "rb");
	rewind(UsuariosGuardados);
	fread(&veterinario, sizeof(Usuario_Veterinario), 1, UsuariosGuardados);
	while( !feof(UsuariosGuardados) ){
		if(veterinario.matricula == matricula){
			cout << "Matricula perteneciente al veterinario: " << veterinario.apellido_nombre << endl;
			fclose(UsuariosGuardados);
			return 1;
		}
		fread(&veterinario, sizeof(Usuario_Veterinario), 1, UsuariosGuardados);
	}
	fclose(UsuariosGuardados);
	return 0;
};

int buscarMascotaPorDNI(int DNI){
	FILE *MascotasGuardadas;
	Mascota mascota;
	MascotasGuardadas = fopen(direccion_archivo_mascotas, "rb");
	rewind(MascotasGuardadas);
	fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);

	while( !feof(MascotasGuardadas) ){
		if(mascota.DNI == DNI){
			fclose(MascotasGuardadas);
			return 1;
		}
		fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	}
	fclose(MascotasGuardadas);
	return 0;
};

int iniciarSesionRecepcion(){
  if(comprobarExistenciaArchivo(direccion_archivo_asistentes)){
		Usuario_Asistente asistente;
		
		cout << "Ingrese su nombre de usuario:" << endl;
		cout << "\n-> ";
		_flushall();
		gets(asistente.usuario.nombre);

		system("cls");

		cout << "Ingrese su clave de usuario:" << endl;
		cout << "\n-> ";
		_flushall();
		gets(asistente.usuario.clave);

		system("cls");

		if(validarAccesoRecepcion(asistente)){
			limpiar(1);
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

int validarAccesoRecepcion(Usuario_Asistente asistente){
	Usuario_Asistente datos_guardados_usuario;
	FILE *UsuariosGuardados;
	UsuariosGuardados = fopen(direccion_archivo_asistentes, "rb");
	rewind(UsuariosGuardados);
	fread(&datos_guardados_usuario, sizeof(Usuario_Asistente), 1, UsuariosGuardados);
	while( !feof(UsuariosGuardados) ){
		if(strcmp(asistente.usuario.nombre, datos_guardados_usuario.usuario.nombre) == 0 && strcmp(asistente.usuario.clave, datos_guardados_usuario.usuario.clave) == 0){
			cout << "Las credenciales ingresadas son correctas. Bienvenido " << datos_guardados_usuario.apellido_nombre << "." << endl;
			fclose(UsuariosGuardados);
			return 1;
		}
		fread(&datos_guardados_usuario, sizeof(Usuario_Asistente), 1, UsuariosGuardados);
	}
	fclose(UsuariosGuardados);
	return 0;
};

void listarAtenciones(){
	if(comprobarExistenciaArchivo(direccion_archivo_atenciones)){
		FILE *AtencionesGuardadas;
		Historia_Clinica atencion;
		AtencionesGuardadas = fopen(direccion_archivo_atenciones, "rb");
		rewind(AtencionesGuardadas);
		fread(&atencion, sizeof(Historia_Clinica), 1, AtencionesGuardadas);
		int index = 1;
		while( !feof(AtencionesGuardadas) ){
			cout << "Atencion #" << index << endl << endl;
			cout << "-> Atencion hecha por el veterinario: " << atencion.redactadaPor << endl;
			cout << "-> Nombre de la mascota: " << atencion.apellido_nombre << endl;
			cout << "-> Fecha de la atencion: ";
			formatearFecha(atencion.fechaAtencion);
			cout << endl << endl;
			
			index++;
			fread(&atencion, sizeof(Historia_Clinica), 1, AtencionesGuardadas);
		}
		fclose(AtencionesGuardadas);
	}
	else{
		cout << "No hay atenciones registradas." << endl;
	}
	limpiar(1);
};