#include <iostream>
#include "Menu.h"
#include <thread>
#include <Windows.h>

int main() {
    vector<string> menuOptions = {"Inicio", "Opciones", "Solicitar Dato", "Salir"};
    vector<string> subMenuOptions = {"Configurar", "Volver"};
    MenuUI menu(80); // Ancho de la consola definido como 80 caracteres
	
	SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
	
    while (true) {
        menu.mostrarMenu(menuOptions);
        MenuUI::Tecla tecla = menu.getTecla();

        if (tecla == MenuUI::ENTER) {
            int opcionSeleccionada = menu.getCursor();
            if (opcionSeleccionada == 0) { // Cuando seleccionamos "Inicio" para probar
                menu.transicionDeslizante(menuOptions, subMenuOptions);
                while (true) { // Permitir navegar en el submenú sin mostrar la transición de nuevo
                    menu.mostrarMenu(subMenuOptions);
                    MenuUI::Tecla subTecla = menu.getTecla();
                    if (subTecla == MenuUI::ENTER || subTecla == MenuUI::ESCAPE) {
                        break; // Salir del submenú al presionar Enter o Escape
                    }
                    menu.moverCursor(subMenuOptions, subTecla);
                }
            } else if (opcionSeleccionada == 2) { // Solicitar Dato
                string dato = menu.solicitarDato<string>("Ingrese un saludo: ");
                cout << "				Saludo ingresado: " << dato << endl;
                cout << endl << PURPURA << SEPARADOR << RESET << endl << endl;
                getch();
			} else if (opcionSeleccionada == 3) {
                if (menu.confirmacion("¿Estas seguro que deseas salir?")) {
                    cout << "Saliendo del menú..." << endl;
                    break;
                } else {
                    menu.mostrarMenu(menuOptions);
                }
            }
        } else if (tecla == MenuUI::ESCAPE) {
            if (menu.confirmacion("¿Estás seguro que deseas salir?")) {
                cout << "Saliendo del menú..." << endl;
                break;
            }
        } else {
            menu.moverCursor(menuOptions, tecla);
        }
    }

    return 0;
}
