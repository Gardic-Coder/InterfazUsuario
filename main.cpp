/*
	AUTOR: JUAN GARCIA

Esta es una interfaz de menus basica para proyectos. La idea es facilitar el manejo de menus y la interaccion de un programa con el usuario.
Este codigo de ejemplo sirve para mostrar las funcionalidades que trae Menu.h
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
#include <iostream>

using namespace std;

int main() {
	vector<string> menuOptions = {"Inicio", "Opciones", "Solicitar Dato", "Salir"};
	//vector<string> subMenu1 = {"Configurar", "Salir"};
	MenuUI menu;
	bool salir = false;
	
	menu.setCursor(0);
	
	while(!salir) {
		try {
			menu.actualizarTamanoConsola(); // Asegurarse de que las dimensiones están actualizadas
		} catch (const runtime_error& e) {
			cerr << e.what() << endl;
		}
		menu.mostrarMenu(menuOptions);
		MenuUI::Tecla tecla = menu.getTecla();

		switch(tecla) {
			case MenuUI::ARRIBA: {
				menu.moverCursor(menuOptions, tecla);
				break;
			}
			case MenuUI::ABAJO: {
				menu.moverCursor(menuOptions, tecla);
				break;
			}
			case MenuUI::ENTER: {
				int opcion = menu.getCursor();
				switch(opcion) {
					case 0: {
						menu.iniciarPantallaDeCarga();
						getch();
						menu.detenerPantallaDeCarga();
						break;
					}
					case 1: {

						break;
					}
					case 2: {
						string dato = menu.solicitarDato("Ingrese un saludo: ");
						menu.mostrarCentrado("Saludo ingresado: " + dato);
						menu.separador();
						getch();
						break;
					}
					case 3: {
						if(menu.confirmacion("¿Estas seguro que deseas salir?")) {
							menu.mostrarCentrado("Saliendo del menu...");
							salir = !salir;
						}

						break;
					}
				}
				break;
			}
			case MenuUI::ESCAPE: {
				if(menu.confirmacion("¿Estas seguro que deseas salir?")) {
					menu.mostrarCentrado("Saliendo del menu...");
					salir = !salir;
				}
				break;
			}
		}
	}
	return 0;
}
