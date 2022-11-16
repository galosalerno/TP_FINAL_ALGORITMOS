#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
using namespace std;
#include <string>

class Nodo {

    private:
        //atributos
        string dato;
        Nodo* siguiente;
    
    public:
        // metodos
        // constructor
        // PRE:
        // POS: crea un nodo con dato = d y siguiente = 0 (NULL)
        Nodo (string d);

        void cambiar_dato(string d);

        void cambiar_siguiente(Nodo* s);

        string obtener_dato();
        
        Nodo* obtener_siguiente();
};

#endif //NODO_H_INCLUDED