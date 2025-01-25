#pragma once
#include <vector>
#include <conio.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono> // Para la funcion sleep
#include <atomic> // Para banderas atomicas

using namespace std;

class MenuUI {
private:
    int cursor;
    int consoleWidth; // Ancho de la consola para centrar el menu horizontalmente
    atomic<bool> loading; // Para detener la pantalla de carga
public:
    MenuUI(int width);
    enum Tecla { ARRIBA, ABAJO, ENTER, ESCAPE, OTRA };
    void mostrarMenu(const vector<string>& opcionesMenu) const;
    Tecla getTecla() const;
    void moverCursor(const vector<string>& opcionesMenu, MenuUI::Tecla tecla);
    int getCursor() const;
    void setCursor(int posicion);
    
    // Metodo para la pantalla de carga y su hilo
    void pantallaDeCarga();
    void iniciarPantallaDeCarga();
    void detenerPantallaDeCarga();
    
    // Metodos para transiciones
    void transicionDeslizante(const vector<string>& menuActual, const vector<string>& siguienteMenu) const;
    void mostrarMenuConTransicion(const vector<string>& menuActual, const vector<string>& siguienteMenu);
	
	bool confirmacion(const string& mensaje);
};
