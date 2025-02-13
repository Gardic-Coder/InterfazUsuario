/*
	IMPORTANTE: Algunas funciones requieren una terminal que soporte funcionalidades avanzadas de codigo de escape ANSI.

	AUTOR: JUAN GARCIA (Gardic-Coder)

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
	* Mas colores.
	* Funciones para que el usuario pueda personalizar la interfaz durante la ejecucion del programa.

Proximas funciones:
	* Funciones para el manejo de archivos de audio.
	* Animaciones de transicion entre menus.
	* Alinear los textos en el centro con un margen izquierdo.
	* Interfaz de teclado para mover el cursor de derecha a izquierda.
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
#define COD_ESC "\033["
#define COLORES "\033[38;5;" // Codigo de escape ANSI para establecer color de texto. Se usa "COLORES << Entero 0-255 << FINAL"
#define FINAL "m" // Final del codigo de escape ANSI para graficos.
#define ACOPLE ";"
#define PARPADEO "5" // Agrega parpadeo al texto.

#define GUARDAR "\0337" // Guarda la posicion del cursor.
#define CARGAR "\0338" // Mueve el cursor a la posicion cargada.
#define OCULTAR "\033[?25l" // Hace el cursor invisible.
#define MOSTRAR "\033[?25h" // Hace el cursor visible.

using namespace std;

//const RESET = "\033[0m";
//const string COLORES = "\033[38;5;";
//const string FINAL = "m";
/*const COD_ESC = "\033[";
const RED =
const YELLOW = "33";
const */

class MenuUI {
public:
	MenuUI(); // Constructor.
	MenuUI(string cursor, string _colorSeparador, string fuente, string _caracterSeparador);
    
	// Entradas de teclado y actualizacion del cursor.
	enum Tecla { ARRIBA, ABAJO, ENTER, ESCAPE, OTRA };
	void moverCursor(const vector<string>& opcionesMenu, MenuUI::Tecla tecla);
    
    // Pantalla.
    void mostrarCentrado(const string& mensaje) const;
    void centradoVertical(const int numLineas) const;
    void mostrarMenu(const vector<string>& opcionesMenu);
    void separador();
    bool confirmacion(const string& mensaje);
    string solicitarDato(const string& mensaje); // Método para solicitar datos al usuario
    
    // Configuracion.
    void actualizarTamanoConsola(); // Toma el tamaño de la consola y actualiza las variables.
    
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
    void setColorSeparador(string color);
    void setColorFuente(string color);
    void setCaracterSeparador(string caracter);
    

private:
    int ancho; // Ancho de la ventana.
    int alto; // Alto de la ventana.
    int cursor; // Posicion del cursor.
    atomic<bool> loading; // Para detener la pantalla de carga
    string colorCursor;
    string colorSeparador;
    string colorFuente;
    string caracterSeparador;
    
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