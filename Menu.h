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
// Menu.h
#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono> // Para la funcion sleep
#include <atomic> // Para banderas atomicas

#define RESET "\033[0m" // Restablece el color de la fuente.
#define YELLOW "\033[33m" // Cambia el color de la fuente a amarillo.
#define PURPURA "\033[35m" // Cambia el color de la fuente a purpura.
#define CYAN "\033[36m" // Cambia el color de la fuente a cian.
#define RED "\033[31m" // Cambia el color de la fuente a rojo.
#define GREEN "\033[32m" // Cambia el color de la fuente a verde.
#define BLUE "\033[34m" // Cambia el color de la fuente a azul.

using namespace std;

class MenuUI {
public:
	MenuUI(); // Constructor.
    void actualizarTamanoConsola(); // Toma el tamaño de la consola y actualiza las variables.
	
	// Entradas de teclado y actualizacion del cursor.
	enum Tecla { ARRIBA, ABAJO, ENTER, ESCAPE, OTRA };
	void moverCursor(const vector<string>& opcionesMenu, MenuUI::Tecla tecla);
    
    // Pantalla.
    void mostrarCentrado(const string& mensaje) const;
    void mostrarMenu(const vector<string>& opcionesMenu);
    void separador();
    bool confirmacion(const string& mensaje);
    string solicitarDato(const string& mensaje); // Método para solicitar datos al usuario
    bool cambiarColorCursor();
    
    // Metodo para la pantalla de carga y su hilo
    void iniciarPantallaDeCarga();
    void detenerPantallaDeCarga();
    
    // Getters.
    int getAncho() const;
    int getAlto() const;
    int getCursor() const;
    Tecla getTecla() const;
    
    // Setters.
    void setCursor(int posicion);
    void setColorCursor(string color);

private:
    int ancho; // Ancho de la ventana.
    int alto; // Alto de la ventana.
    int cursor; // Posicion del cursor.
    atomic<bool> loading; // Para detener la pantalla de carga
    string colorCursor;
    
    void pantallaDeCarga(); // Este metodo es llamado por iniciarPantallaDeCarga y detenerPantallaDeCarga.
};

/*void loading() {
    std::cout << "Loading..." << std::endl;
    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\r" << (i + 1) << "%" << std::flush;
    }
    std::cout << std::endl;
}*/