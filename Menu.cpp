#include "Menu.h"

// Implementacion del constructor y los metodos
MenuUI::MenuUI() : ancho(0), alto(0) {
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
			cout << YELLOW; 
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
    cout << RESET;
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
				cout << YELLOW; 
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
	const vector<string> colors = {RED, GREEN, YELLOW, CYAN, PURPURA};
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