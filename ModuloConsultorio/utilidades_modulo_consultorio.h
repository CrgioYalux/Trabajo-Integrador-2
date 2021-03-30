int menu_consultorio();
int menu_autenticacion_consultorio();
int validarAccesoConsultorio(Usuario_Veterinario veterinario);
int iniciarSesionConsultorio();
void sesionTemporal(Usuario_Veterinario veterinario);
void visualizarTurnos();
int recuperarDatosMascota_conDNI(Mascota &buscar_mascota);
void calcularEdad(char resultado[], Fecha fecha1, Fecha fecha2);
void registrarEvolucion();
int comprobarExistenciaMascota(char nombreMascota[]);
int recuperarDatosMascota_conNombre(Mascota &buscar_mascota);
int recuperarDatosVeterinario_conMatricula(Usuario_Veterinario &buscar_veterinario);
void guardarHistoriaClinica(Historia_Clinica atencion);
void borrarTurnoRegistrado(Turno borrar_turno);
void actualizarRankingAtenciones(char apellidoNombre_veterinario[]);

int menu_consultorio(){
	system("cls");
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
				visualizarTurnos();
				break;
			case 2:
				registrarEvolucion();
				break;
			case 3:
				remove(direccion_archivo_sesion);
				menuLoop = false;
				break;
		}
	}
};

int menu_autenticacion_consultorio(){
	system("cls");
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

void visualizarTurnos(){
	if(comprobarExistenciaArchivo(direccion_archivo_turnos)){
		Turno turno;
		Usuario_Veterinario veterinario;
		FILE *TurnosGuardados;
		FILE *SesionActual;
		SesionActual = fopen(direccion_archivo_sesion, "rb");
		TurnosGuardados = fopen(direccion_archivo_turnos, "rb");
		rewind(TurnosGuardados);
		rewind(SesionActual);
		fread(&turno, sizeof(Turno), 1, TurnosGuardados);
		fread(&veterinario, sizeof(Usuario_Veterinario), 1, SesionActual);
		
		int index = 1;
		while( !feof(TurnosGuardados) ){
			if(veterinario.matricula == turno.matriculaVeterinario){
				Mascota mascota_encontrada;
				char edadMascota[100];
				mascota_encontrada.DNI = turno.DNI;
				recuperarDatosMascota_conDNI(mascota_encontrada);
				calcularEdad(edadMascota, turno.fecha, mascota_encontrada.fechaNacimiento);

				cout << "Turno #" << index << ":" << endl;
				cout << "-> DNI del due\244o de la mascota: " << mascota_encontrada.DNI << endl;
				cout << "-> Apellido y nombre de la mascota: " << mascota_encontrada.apellido_nombre << endl;
				cout << "-> Fecha del turno: ";
				formatearFecha(turno.fecha);
				cout << endl;
				cout << "-> Edad de la mascota: " << edadMascota << endl;
				cout << "-> Peso de la mascota: " << mascota_encontrada.peso << endl;
				cout << "-> Localidad: " << mascota_encontrada.localidad << endl;
				cout << endl;
				index++;
			}
			fread(&turno, sizeof(Turno), 1, TurnosGuardados);
		}
		fclose(TurnosGuardados);
		fclose(SesionActual);
	}
	else{
		cout << "No hay turnos registrados." << endl;
	}
	limpiar(1);
};

int recuperarDatosMascota_conDNI(Mascota &buscar_mascota){
	FILE *MascotasGuardadas;
	Mascota mascota;
	MascotasGuardadas = fopen(direccion_archivo_mascotas, "rb");
	rewind(MascotasGuardadas);
	fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	while( !feof(MascotasGuardadas) ){
		if(buscar_mascota.DNI == mascota.DNI){
			buscar_mascota = mascota;
			fclose(MascotasGuardadas);
			return 1;
		}
		fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	}
	fclose(MascotasGuardadas);
	return 0;
};

void calcularEdad(char resultado[], Fecha fecha1, Fecha fecha2){
	int diffyears = fecha1.year - fecha2.year;
	if(diffyears < 0){
		diffyears = diffyears * (-1);
		//la fecha es
	}

	int diffmonths = fecha1.month - fecha2.month;
	if(diffmonths < 0){
		diffmonths = diffmonths * (-1);
		//la fecha es
	}

	int diffdays = fecha1.day - fecha2.day;
	if(diffdays < 0){
		diffdays = diffdays * (-1);
		//la fecha es
	}

	char years[10] = {'\0'};
	char months[10] = {'\0'};
	char days[10] = {'\0'};
	enteroACadena(diffyears, years);
	enteroACadena(diffmonths, months);
	enteroACadena(diffdays, days);
	if(diffyears == 0){
		strcpy(years, "0");
	}
	if(diffmonths == 0){
		strcpy(months, "0");
	}
	if(diffdays == 0){
		strcpy(days, "0");
	}
	char aux[100] = "La mascota tiene ";
	strcat(aux, years);
	strcat(aux, " a\244os, ");
	strcat(aux, months);
	strcat(aux, " meses y ");
	strcat(aux, days);
	strcat(aux, " dias.");
	
	strcpy(resultado, aux);
};

void registrarEvolucion(){
	Historia_Clinica atencion;

	if(comprobarExistenciaArchivo(direccion_archivo_mascotas)){
		inputString(atencion.apellido_nombre, "Ingrese el apellido y nombre de la mascota", 61);
		if(comprobarExistenciaMascota(atencion.apellido_nombre)){
			Mascota mascota;
			strcpy(mascota.apellido_nombre, atencion.apellido_nombre);
			char edadMascota[100];

			cout << "Ingrese la fecha actual: " << endl;
			inputInt(atencion.fechaAtencion.day, "Dia: ", true, 1, 30);
			inputInt(atencion.fechaAtencion.month, "Mes: ", true, 1, 12);
			inputInt(atencion.fechaAtencion.year, "A\244o: ", true, 1980, 2021);
			
			recuperarDatosMascota_conNombre(mascota);
			atencion.DNI = mascota.DNI;
			strcpy(atencion.localidad, mascota.localidad);
			calcularEdad(edadMascota, mascota.fechaNacimiento, atencion.fechaAtencion);
			strcpy(atencion.edad, edadMascota);
			atencion.peso = mascota.peso;
			
			inputString(atencion.evolucion,"Evolucion de la mascota: ", 381, 1);

			FILE *SesionActual;
			Usuario_Veterinario veterinario;
			SesionActual = fopen(direccion_archivo_sesion, "rb");
			rewind(SesionActual);
			fread(&veterinario, sizeof(Usuario_Veterinario), 1, SesionActual);
			recuperarDatosVeterinario_conMatricula(veterinario);	
			fclose(SesionActual);
			strcpy(atencion.redactadaPor, veterinario.apellido_nombre);
			
			Turno borrar_turno;
			borrar_turno.DNI = mascota.DNI;
			guardarHistoriaClinica(atencion);
			borrarTurnoRegistrado(borrar_turno);
			actualizarRankingAtenciones(atencion.redactadaPor);

			cout << "Datos de la evolucion registrada" << endl;
			cout << "Apellido y nombre de la mascota: " << atencion.apellido_nombre << endl;
			cout << "DNI (del due\244o): " << atencion.DNI << endl;
			cout << "Edad de la mascota: " << atencion.edad << endl;
			cout << "Evolucion: " << atencion.evolucion << endl;
			cout << "Fecha de atencion: ";
			formatearFecha(atencion.fechaAtencion);
			cout << endl;
			cout << "Localidad: " << atencion.localidad << endl;
			cout << "Peso de la mascota: " << atencion.peso << endl;
			cout << "Apellido y nombre del veterinario: " << atencion.redactadaPor << endl;
		}
		else{
			cout << "No existe una mascota registrada con ese apellido y nombre." << endl;
		}
	}
	else{
		cout << "No hay mascotas registradas." << endl;
	}
	limpiar(1);
};

int comprobarExistenciaMascota(char nombreMascota[]){
	FILE *MascotasGuardadas;
	Mascota mascota;
	MascotasGuardadas = fopen(direccion_archivo_mascotas, "rb");
	rewind(MascotasGuardadas);
	fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	while( !feof(MascotasGuardadas) ){
		if(strcmp(nombreMascota, mascota.apellido_nombre) == 0){
			fclose(MascotasGuardadas);
			return 1;
		}
		fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	}
	fclose(MascotasGuardadas);
	return 0;
};

int recuperarDatosMascota_conNombre(Mascota &buscar_mascota){
	FILE *MascotasGuardadas;
	Mascota mascota;
	MascotasGuardadas = fopen(direccion_archivo_mascotas, "rb");
	rewind(MascotasGuardadas);
	fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	while( !feof(MascotasGuardadas) ){
		if(strcmp(buscar_mascota.apellido_nombre, mascota.apellido_nombre) == 0){
			buscar_mascota = mascota;
			fclose(MascotasGuardadas);
			return 1;
		}
		fread(&mascota, sizeof(Mascota), 1, MascotasGuardadas);
	}
	fclose(MascotasGuardadas);
	return 0;
};

int recuperarDatosVeterinario_conMatricula(Usuario_Veterinario &buscar_veterinario){
	FILE *VeterinariosGuardados;
	Usuario_Veterinario veterinario;
	VeterinariosGuardados = fopen(direccion_archivo_veterinarios, "rb");
	rewind(VeterinariosGuardados);
	fread(&veterinario, sizeof(Usuario_Veterinario), 1, VeterinariosGuardados);
	while( !feof(VeterinariosGuardados) ){
		if(buscar_veterinario.matricula == veterinario.matricula){
			buscar_veterinario = veterinario;
			fclose(VeterinariosGuardados);
			return 1;
		}
		fread(&veterinario, sizeof(Usuario_Veterinario), 1, VeterinariosGuardados);
	}
	fclose(VeterinariosGuardados);
	return 0;
};

void guardarHistoriaClinica(Historia_Clinica atencion){
	FILE *AtencionesGuardadas;
	AtencionesGuardadas = fopen(direccion_archivo_atenciones, "a+b");
	fseek(AtencionesGuardadas, sizeof(Historia_Clinica), SEEK_END);
	fwrite(&atencion, sizeof(Historia_Clinica), 1, AtencionesGuardadas);
	fclose(AtencionesGuardadas);
};

void borrarTurnoRegistrado(Turno borrar_turno){
	FILE *TurnosGuardados, *Aux;
	Turno turno;
	TurnosGuardados = fopen(direccion_archivo_turnos, "rb");
	Aux = fopen(direccion_archivo_turnos_aux, "a+b");
	rewind(TurnosGuardados);
	fread(&turno, sizeof(Turno), 1, TurnosGuardados);
	while( !feof(TurnosGuardados) ){
		if(turno.DNI != borrar_turno.DNI){
			fwrite(&turno, sizeof(Turno), 1, Aux);
		}
		fread(&turno, sizeof(Turno), 1, TurnosGuardados);
	}
	fclose(TurnosGuardados);
	fclose(Aux);
	remove(direccion_archivo_turnos);
	rename(direccion_archivo_turnos_aux, direccion_archivo_turnos);
}

void actualizarRankingAtenciones(char apellidoNombre_veterinario[]){
	FILE *RankingGuardado, *Aux;
	ContadorAtenciones contador;
	ContadorAtenciones nuevo_contador;
	RankingGuardado = fopen(direccion_archivo_ranking, "rb");
	Aux = fopen(direccion_archivo_ranking_aux, "a+b");
	rewind(RankingGuardado);
	fread(&contador, sizeof(ContadorAtenciones), 1, RankingGuardado);
	while( !feof(RankingGuardado) ){
		if(strcmp(apellidoNombre_veterinario, contador.apellido_nombre_veterinario) == 0){
			strcpy(nuevo_contador.apellido_nombre_veterinario, contador.apellido_nombre_veterinario);
			nuevo_contador.cantAtenciones = contador.cantAtenciones + 1;
			fwrite(&nuevo_contador, sizeof(ContadorAtenciones), 1, Aux);
		}
		else{
			fwrite(&contador, sizeof(ContadorAtenciones), 1, Aux);
		}
		fread(&contador, sizeof(ContadorAtenciones), 1, RankingGuardado);
	}
	fclose(RankingGuardado);
	fclose(Aux);
	remove(direccion_archivo_ranking);
	rename(direccion_archivo_ranking_aux, direccion_archivo_ranking);
};
