/*
	AUTOR: JUAN GARCIA

Esta es una interfaz de menus basica para proyectos. La idea es facilitar el manejo de menus y la interaccion de un programa con el usuario.
Aun faltan muchas funciones por añadir.

Funciones añadidas:
	* Ajuste automatico al tamaño de la ventana.
	* Manejo de entradas del teclado.
	* Manejo de interfaz por medio de flechas, enter y escape.
	* Pantalla de carga.
	* Pantalla de solicitud de dato.
	* Pantalla de confirmacion de seleccion.
	* Pantalla de menu para cualquier menu general.
	* Centrado de textos en pantalla.
	* Herramientas varias para el embellecimiento de la interfaz:
		- Codigo de escape ANSI para cambiar colores.
		- Metodo separador ajustado al tamaño de la pantalla.

Proximas funciones:
	* Funciones para que el usuario pueda personalizar la interfaz durante la ejecucion del programa.
	* Funciones para el manejo de archivos de audio.
	* Animaciones de transicion entre menus.
	* Alinear los textos en el centro con un margen izquierdo.
	* Interfaz de teclado para mover el cursor de derecha a izquierda.
	* Mas colores.
	* Cambiar tamaño de fuente.
*/
#include "Menu.h"

// Implementacion del constructor y los metodos
MenuUI::MenuUI() : ancho(0), alto(0) {
	colorCursor = YELLOW;
	actualizarTamanoConsola();
}

void MenuUI::actualizarTamanoConsola() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) {
		throw runtime_error("No se pudo obtener el handle de la consola");
	}

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		throw runtime_error("No se pudo obtener la informacion de la ventana de consola");
	}

	ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int MenuUI::getAncho() const {
	return ancho;
}

int MenuUI::getAlto() const {
	return alto;
}

MenuUI::Tecla MenuUI::getTecla() const {
	int c = _getch();
	switch (c) {
		case 72:
			return MenuUI::ARRIBA;
		case 80:
			return MenuUI::ABAJO;
		case 13:
			return MenuUI::ENTER;
		case 27:
			return MenuUI::ESCAPE;
		default:
			return MenuUI::OTRA;
	}
}

void MenuUI::moverCursor(const vector<string>& opcionesMenu, MenuUI::Tecla tecla) {
	switch (tecla) {
		case MenuUI::ARRIBA:
			if (cursor > 0) cursor--;
			break;
		case MenuUI::ABAJO:
			if (cursor < opcionesMenu.size() - 1) cursor++;
			break;
		default:
			break;
	}
}

int MenuUI::getCursor() const {
	return cursor;
}

void MenuUI::setCursor(int posicion) {
	cursor = posicion;
}

void MenuUI::separador() {
	cout << endl << endl << PURPURA;
	for(int i = 0; i < ancho; i++) {
		cout  << "-";
	}
	cout << endl << endl << RESET;
}

void MenuUI::mostrarCentrado(const string& mensaje) const {
	int longitudMensaje = mensaje.length();
	int posicionCentrada = (ancho - longitudMensaje) / 2;

	// Imprimir espacios en blanco antes del mensaje para centrarlo
	cout << string(posicionCentrada, ' ') << mensaje;
}

void MenuUI::mostrarMenu(const vector<string>& opcionesMenu) {
	system("cls");
	MenuUI::separador();
	for(size_t i = 0; i < opcionesMenu.size(); ++i) { // Imprime todas las opciones del menu.
		if(i == cursor) { // Coloca una flecha en la posicion del cursor.
			cout << colorCursor; 
			MenuUI::mostrarCentrado("> " + opcionesMenu[i] + " <");
			cout << RESET;
		} else {
			MenuUI::mostrarCentrado(opcionesMenu[i]);
		}
		if(i < opcionesMenu.size() - 1) cout << endl;
	}
	MenuUI::separador();
}

string MenuUI::solicitarDato(const string& mensaje) {
    string entrada;

    // Mostrar el mensaje centrado
    system("cls");
    MenuUI::separador();
    mostrarCentrado(mensaje);
    cout << endl << GREEN;
    mostrarCentrado("-> ");
    cout << "\0337";
    MenuUI::separador();
    cout << "\0338";
    getline(cin, entrada);
	
    return entrada;
}

bool MenuUI::confirmacion(const string& mensaje) {
	vector<string> opciones = {"Si", "No"};
	int seleccion = 0;
	while (true) {
		system("cls");
		MenuUI::separador();
		MenuUI::mostrarCentrado(mensaje);
		cout << endl;
		for (int i = 0; i < opciones.size(); ++i) {
			if (i == seleccion) {
				cout << colorCursor; 
				MenuUI::mostrarCentrado("> " + opciones[i] + " <");
				cout << RESET;
			} else {
				MenuUI::mostrarCentrado(opciones[i]);
			}
			if(i < opciones.size() - 1) cout << endl;
		}
		MenuUI::separador();
		Tecla tecla = MenuUI::getTecla();
		if (tecla == ARRIBA && seleccion > 0) {
			seleccion--;
		} else if (tecla == ABAJO && seleccion < opciones.size() - 1) {
			seleccion++;
		} else if (tecla == ENTER) {
			return seleccion == 0;
		}
	}
}

void MenuUI::pantallaDeCarga() {
	const vector<string> frames = {"-", "\\", "|", "/"};
	const vector<string> colors = {RED, GREEN, YELLOW, CYAN, PURPURA, BLUE};
	int frameIndex = 0;
	int colorIndex = 0;

	while (loading) {
		system("cls");
		MenuUI::separador();
		MenuUI::mostrarCentrado(" Cargando ");
		cout << endl << colors[colorIndex];
		MenuUI::mostrarCentrado(frames[frameIndex]);
		cout << RESET; 
		frameIndex = (frameIndex + 1) % frames.size();
		colorIndex = (colorIndex + 1) % colors.size();
		MenuUI::separador();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void MenuUI::iniciarPantallaDeCarga() {
	loading = true;
	thread t(&MenuUI::pantallaDeCarga, this);
	t.detach();
}

void MenuUI::detenerPantallaDeCarga() {
	loading = false;
	MenuUI::mostrarCentrado(" Cargando... Completado! ");
	cout << endl;
}

void MenuUI::setColorCursor(string color) {
	colorCursor = color;
}

bool MenuUI::cambiarColorCursor() {
	const vector<string> colors = {RESET, RED, GREEN, YELLOW, CYAN, PURPURA, BLUE};
	const vector<string> opciones = {"Blanco", "Rojo", "Verde", "Amarillo", "Cian", "Magenta", "Azul"};
	int seleccion = 0;
	
	while (true) {
		system("cls");
		MenuUI::separador();
		MenuUI::mostrarCentrado("Elige un color:");
		cout << endl;
		for (int i = 0; i < opciones.size(); ++i) {
			if (i == seleccion) {
				cout << colorCursor; 
				MenuUI::mostrarCentrado("> " + opciones[i] + " <");
				cout << RESET;
			} else {
				MenuUI::mostrarCentrado(opciones[i]);
			}
			if(i < opciones.size() - 1) cout << endl;
		}
		MenuUI::separador();
		Tecla tecla = MenuUI::getTecla();
		if (tecla == ARRIBA && seleccion > 0) {
			seleccion--;
		} else if (tecla == ABAJO && seleccion < opciones.size() - 1) {
			seleccion++;
		} else if (tecla == ENTER) {
			setColorCursor(colors[seleccion]);
			return true;
		} else if (tecla == ESCAPE) return false;
	}
}