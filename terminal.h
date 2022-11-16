#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>
#include <string>
#include "nodo.h"
using namespace std;

class Terminal {
private:
    // atributos
    Nodo* primero;
    int largo;

public:
    // constructor
    // pos: crea una cola vacia
    Terminal();
    
    string altaTerminal(); //Retorna el codigo de la terminal dada de alta.
    
    void altaTerminalHard(string d, int pos);
    
    void bajaTerminal(string cod);
    
    void bajaTerminalHard(int pos);
    
    int consultarLargo();
    
    string buscarTerminal(int pos);
    
    string buscarTerminalPorCodigo(string codigo);
    
    int cantidadDeTerminales();
    
    void mostrarTerminales();
    
    void completarTerminales(int tamano);
    
    void leerTerminales();
    
    bool vacia();

    // pos: libera la memoria
    virtual ~Terminal();

private:
    Nodo* obtener_nodo(int pos);
};

#endif // LISTA_H_INCLUDED