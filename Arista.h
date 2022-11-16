#include <iostream>

class Vertice;

class Arista
{
	int precio;
	float tiempo;
	Arista* sig;
	Vertice* dest;

	friend class Grafo;
public:
	Arista(Vertice* _dest, int distancia, float tiempo);
};