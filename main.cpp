#include "Menu.h"
#include <iostream>

using namespace std;

int main() {
	vector<string> menuOptions = {"Inicio", "Opciones", "Solicitar Dato", "Salir"};
	vector<string> subMenu1 = {"Configurar", "Salir"};
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
