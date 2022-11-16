#include "Arista.h"
#include "Vertice.h"
using namespace std;

class Grafo {
    Vertice* primero;
    int tamano;
public:
    Grafo();
    bool estaVacio(); 
    int obtenerTamano(); //Cantidad de vertices del grafo
    Vertice* obtenerVertice(string nombre); //Retorna el vertice con el nombre del parametro
    void insertaVertice(string nombre); //Inserta un nuevo vertice al grafo.
    void insertarArista(string origen, string destino, int distancia, float tiempo); //Inserta arista entre los 2 vertices pasados por parametro
    void mostrarRecorridos(); // Muestra todos los vertices
    void eliminarAristas(Vertice* vertice); //Elimina las aristas del vertice pasado por parametro 
    void eliminarVertice(string nombre); //Elimina un vertice.
    void eliminarAristasDestino(string destino); //Elimina las aristas que tienen como destino el vertide pasado por parametro
    void eliminarArista(string origen, string destino); //Elimina la arista entre un origen y destino.
    void eliminarTodo(); 
    void leerTerminales();//Lee "terminales.txt" y genera los vertices.
    void precioMinimo(string origen,string destino); //Determina el camino mas economico entre un origen y un destino.
    void caminoMinimo(string origen,string destino); //Determina el camino mas rapido entre un origen y un destino.
    void leerRecorridos();//Lee "terminales.txt" y genera las aristas.
};