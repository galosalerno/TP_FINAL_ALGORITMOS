#include "Arista.h"

Arista::Arista(Vertice* _dest, int _precio, float _tiempo)
{
	dest = _dest;
	precio = _precio;
	tiempo = _tiempo;
	sig = NULL;
}