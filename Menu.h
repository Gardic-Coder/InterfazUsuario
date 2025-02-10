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
    
    // Metodo para la pantalla de carga y su hilo
    void pantallaDeCarga();
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
};

