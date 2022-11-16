#include "nodo.h"
using namespace std;
#include <string>

Nodo::Nodo(string d) {
    dato = d;
    siguiente = 0;
}

void Nodo::cambiar_dato(string d){
    dato = d;
}

void Nodo::cambiar_siguiente(Nodo* s) {
    siguiente = s;
}

string Nodo::obtener_dato() {
    return dato;
}

Nodo* Nodo::obtener_siguiente() {
    return siguiente;
}
