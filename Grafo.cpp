#include "Grafo.h"
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

Grafo :: Grafo() {
    primero = NULL;
    tamano = 0;
};
string parseTerminal(string const &str,int idx)
{
    char delim = ' ';
    stringstream ss(str);
    int index = 0;
    string s = "";
    string dataReturn;
    
    while (getline(ss, s, delim)) {
        if(index==idx){
            dataReturn = s;
        }
        index++;
    }
    return dataReturn;
}
bool Grafo::estaVacio(){
    return tamano == 0;
}

int Grafo::obtenerTamano(){
    return tamano;
}

Vertice* Grafo::obtenerVertice(string nombre){
    Vertice* i = primero;
    
    while (i != NULL){
        if (i->nombre == nombre){
            return i;
        }
        i = i -> sig;
    }
    return NULL;
}

void Grafo::insertaVertice(string nombre){
    if (obtenerVertice(nombre) == NULL){
        Vertice* nuevo = new Vertice(nombre);
        if(estaVacio()){
            primero = nuevo;
        }
        else{
           Vertice* i = primero;
    
            while (i->sig != NULL){
                i = i -> sig;
            } 
            i->sig = nuevo;
        }
        tamano++;
    }
    else{
        cout << "Ese vertice ya existe en el grafo" << endl;
    }
}

void Grafo::insertarArista(string origen, string destino, int precio, float tiempo){
    Vertice* verticeOrigen = obtenerVertice(origen);
    Vertice* verticeDestino = obtenerVertice(destino);
    
    if (verticeOrigen == NULL){
         cout << "El vertice origen no existe" << endl;
    }
    if (verticeDestino == NULL){
         cout << "El vertice destino no existe" << endl;
    }
    if(verticeOrigen != NULL && verticeDestino != NULL){
        Arista* nueva = new Arista(verticeDestino, precio, tiempo);
        
        if (verticeOrigen -> ari == NULL){
            verticeOrigen -> ari = nueva;
        }
        else{
            Arista* j = verticeOrigen -> ari;
            
            while (j->sig != NULL){
                j = j -> sig;
            }
            j->sig = nueva;
                
            }
        }
    }
    
void Grafo::mostrarRecorridos(){
    Vertice* i = primero;
	while (i != NULL)
	{
		Arista* j = i->ari;
		cout << i -> nombre << " = ";

		while (j != NULL)
		{
			cout << i->nombre << " -> " << j->precio << " | " << j->tiempo << " -> " << j->dest->nombre << " / ";
			j = j->sig;
		}

		cout << endl;
		i = i->sig;
	}
}

void Grafo::eliminarAristas(Vertice* vertice){
    Arista* i = vertice -> ari;
    
    while (vertice -> ari != NULL){
        i = vertice -> ari;
        vertice -> ari = vertice -> ari -> sig;
        cout << "Arista " << vertice -> nombre << " -> " << i->dest->nombre << " eliminada" << endl;
        delete(i);
    }
}

void Grafo::eliminarVertice(string nombre){
    bool existe = false;
    if (primero -> nombre == nombre){
        Vertice* i = primero;
        primero = primero -> sig;
        eliminarAristas(i);
        eliminarAristasDestino(i -> nombre);
        cout << "El vertice " << nombre << " fue eliminado" << endl;
        delete(i);
        tamano--;
    }
    else{
        Vertice* i = primero;
        Vertice* j = i -> sig;
        while (j != NULL){
            if (j->nombre == nombre){
                i -> sig= j -> sig;
                eliminarAristas(j);
                eliminarAristasDestino(j -> nombre);
                cout << "El vertice " << nombre << " fue eliminado" << endl;
                delete(j);
                tamano--;
                existe = true;
                break;
            }
            i = j;
            j = j -> sig; 
        }
    }
    if (!existe){
        cout << "El vertice no existe!" << endl;
    }
}

void Grafo::eliminarAristasDestino(string destino){
    Vertice* i = primero;
    
    while (i != NULL){
        if (i -> nombre == destino || i -> ari == NULL){
            i = i -> sig;
            continue;
        }
        if (i -> ari->dest->nombre == destino){
             Arista* j = i -> ari;
             i -> ari = i -> ari -> sig;
            cout << "Arista " << i->nombre << " -> " << j->dest->nombre << " fue eliminada" << endl;
             delete(j);
        }
        else{
            Arista* x = i -> ari;
            Arista* y = x -> sig;
            
            while (y != NULL){
                if (y -> dest -> nombre == destino){
                    x -> sig = y -> sig;
                    cout << "Arista " << i->nombre << " -> " << destino << " fue eliminada" << endl;
                    delete(y);
                }
                x = y;
                y = y -> sig;
            }
        }
        i = i -> sig;
    }
}

void Grafo::eliminarArista(string origen, string destino){
    Vertice* verticeOrigen = obtenerVertice(origen);
    Vertice* verticeDestino = obtenerVertice(destino);
    
    if (verticeOrigen == NULL){
         cout << "El vertice origen no existe" << endl;
    }
    if (verticeDestino == NULL){
         cout << "El vertice destino no existe" << endl;
    }
    if(verticeOrigen != NULL && verticeDestino != NULL){
        if (verticeOrigen -> ari -> dest == verticeDestino){
            Arista* i = verticeOrigen -> ari;
            verticeOrigen -> ari = verticeOrigen -> ari -> sig;
            cout << "Arista " << origen << " -> " << destino << " fue eliminada" << endl;
            delete(i);
        }
        else{
            Arista* i = verticeOrigen -> ari; 
            Arista* j = i -> sig; 
            
            while (j != NULL){
                if (j -> dest -> nombre == verticeDestino -> nombre){
                    i -> sig = j -> sig;
                    cout << "Arista " << origen << " -> " << destino << " fue eliminada" << endl;
                    delete(j);
                    break;
                }
                i = j;
                j = j -> sig;
            }
        }
    }
}

void Grafo::eliminarTodo(){
    Vertice* i = primero;
    while (primero != NULL){
        i = primero;
        primero = primero -> sig;
        eliminarAristas(i);
        eliminarAristasDestino(i -> nombre);
        cout << "Vertice " << i -> nombre << "  eliminado" << endl;
        delete(i);
        tamano--;
    }
}

void Grafo::leerRecorridos(){
    string line;	
    ifstream myfile("Recorridos.txt");
     //Terminal terminal;
     if (myfile.is_open())
     {
         while (getline(myfile, line)){
            //RET COR 22483 7.31
            string codOrigen = parseTerminal(line,0);
            string codDestino = parseTerminal(line,1);
            int costo = stoi(parseTerminal(line,2));
            float duracion = stof(parseTerminal(line,3));
            this->insertarArista(codOrigen, codDestino,costo,duracion);
         }
     }
}

void Grafo::leerTerminales(){
    string line;	
    ifstream myfile("terminales.txt");
     //Terminal terminal;
     if (myfile.is_open())
     {
         while (getline(myfile, line)){
            string cod = line.substr(0,3);
            insertaVertice(cod);
         }
     }
     leerRecorridos();
     
}


bool CostoMinimo(const pair<Vertice*, int>& a, const pair<Vertice*, int>& b)
{
	return a.second < b.second;
}

//Utilizamos el algoritmo dijkstra para obtener los viajes mas baratos.
void Grafo::precioMinimo(string origen,string destino)
{
	Vertice* vorigen = obtenerVertice(origen);
	Vertice* vdestino = obtenerVertice(destino);

	if (vorigen == NULL or vdestino == NULL)
		cout << "No existe alguna de las terminales!" << endl;
	else
	{
		map<Vertice*, map<Vertice*, int>> matriz;
		map<Vertice*, bool> visitados;
		map<Vertice*, Vertice*> rutas;
		map<Vertice*, int> cola;
		map<Vertice*, int> precios;

		Vertice* vi = primero;

		// Mientras exista al menos un vertice se ejecuta el ciclo.
		while (vi != NULL)
		{
			visitados[vi] = false;
			rutas[vi] = NULL;
			precios[vi] = numeric_limits<int>::max();

			Vertice* vj = primero;

			while (vj != NULL)
			{
				matriz[vi][vj] = numeric_limits<int>::max();
				vj = vj->sig;
			}

			Arista* aj = vi->ari;

			while (aj != NULL)
			{
				matriz[vi][aj->dest] = aj->precio;
				aj = aj->sig;
			}

			vi = vi->sig;
		}

		precios[vorigen] = 0;
		visitados[vorigen] = true;
		cola[vorigen] = precios[vorigen];

		while (!cola.empty())
		{
			// Encuentra el vertice con el costo menor en la cola
			map<Vertice*, int>::iterator iter = min_element(cola.begin(), cola.end(), CostoMinimo);
			visitados[iter->first] = true;

			// Recorre todos los vertices que tiene como destino
			Arista* ai = iter->first->ari;

			while (ai != NULL)
			{
				if (!visitados[ai->dest])
				{
					if (precios[ai->dest] > precios[iter->first] + matriz[iter->first][ai->dest])
					{
						precios[ai->dest] = precios[iter->first] + matriz[iter->first][ai->dest];
						rutas[ai->dest] = iter->first;
						cola[ai->dest] = precios[ai->dest];
					}
				}

				ai = ai->sig;
			}

			cola.erase(iter->first);
		}

		// Muestra el precio minimo para el destino buscado.
		for (map<Vertice*, int>::iterator i = precios.begin(); i != precios.end(); i++){
			//i->first->nombre = Devuelve el nombre de la terminal destino
			//i->second = Devuelve el valor del viaje
			if(i->first->nombre == destino){
			    if(i->second == 2147483647){
			        cout << "No hay ruta disponible" <<endl;    
			    }else{
			        cout << "El camino mas barato de " << origen << " a " << i->first->nombre << " es de $" << i->second << endl;    
			        	//Mostrar la ruta de viaje para el precio minimo
            		int indexAux = 0;
            		for (map<Vertice*, Vertice*>::iterator i = rutas.begin(); i != rutas.end(); i++)
            		{
            			Vertice* vAct = i->first;
                        
                        if(vAct->nombre == destino){
                			cout << "La ruta para este viaje es: "<<endl;
                			cout << "Terminal destino: ";
                			while (vAct != NULL)
                			{
                				cout << vAct->nombre << " <- ";
                				vAct = rutas[vAct];
                			}
                			cout << "Terminal origen"<<endl;
                			indexAux++;
                        }
            		}
			    }
			}
		}
	}

}
bool TiempoMinimo(const pair<Vertice*, long>& a, const pair<Vertice*, long>& b)
{
	return a.second < b.second;
}
	
//Utilizamos el algoritmo dijkstra para obtener los viajes mas baratos.
void Grafo::caminoMinimo(string origen,string destino)
{
	Vertice* vorigen = obtenerVertice(origen);
	Vertice* vdestino = obtenerVertice(destino);

	if (vorigen == NULL or vdestino == NULL)
		cout << "No existe alguna de las terminales!" << endl;
	else
	{
		map<Vertice*, map<Vertice*, float>> matriz;
		map<Vertice*, bool> visitados; //Mapa que contiene un puntero al Vertice y un booleano (true si ya fue visitado)
		map<Vertice*, Vertice*> rutas;
		map<Vertice*, float> cola; //Vertices pendientes de visitar
		map<Vertice*, float> duracion; //Mapa donde guardamos el puntero al vertice y la duracion que tenemos hacia el.

		Vertice* vi = primero; //El vertice inicial es el primero en el Grafo.

		//Recorremos las filas de la matriz.
		while (vi != NULL)
		{
			visitados[vi] = false; //Inicialmente seteamos en false ya que no fui visitado aun.
			rutas[vi] = NULL; //Inicialmente seteamos en Null.
			duracion[vi] = numeric_limits<int>::max();

			Vertice* vj = primero;
            //Recorremos las columnas de la matriz.
			while (vj != NULL)
			{
				matriz[vi][vj] = numeric_limits<int>::max(); //Inicialmente lo seteamos con el valor maximo de un entero () (Representa el infinito)
				vj = vj->sig;
			}

			Arista* aj = vi->ari;
            
            //Recorremos las aristas del vertice
			while (aj != NULL)
			{
				matriz[vi][aj->dest] = aj->tiempo; //Guarda el tiempo de la arista en la matriz.
				aj = aj->sig; //Cambia aj al siguiente hasta que llega al final y queda NULL.
			}

			vi = vi->sig; //Pasa el vertice al siguiente - cuando llega al final queda en NULL y sale del ciclo.
		}

		duracion[vorigen] = 0;
		visitados[vorigen] = true;
		cola[vorigen] = duracion[vorigen];

		while (!cola.empty())
		{
			// Encuentra el vertice con el costo menor en la cola
			//Se le pasa como 3er parametro una expresion lamba para que sepa con que elemento dell Map hacer la comparacion.(En este caso el float)
			map<Vertice*, float>::iterator iter = min_element(cola.begin(), cola.end(), TiempoMinimo); 
			visitados[iter->first] = true;

			// Recorre todos los vertices que tiene como destino
			Arista* ai = iter->first->ari;

			while (ai != NULL)
			{
				if (!visitados[ai->dest])
				{
					if (duracion[ai->dest] > duracion[iter->first] + matriz[iter->first][ai->dest])
					{
						duracion[ai->dest] = duracion[iter->first] + matriz[iter->first][ai->dest];
						rutas[ai->dest] = iter->first;
						cola[ai->dest] = duracion[ai->dest];
					}
				}

				ai = ai->sig;
			}

			cola.erase(iter->first);
		}

		// Muestra el precio minimo para el destino buscado.
		for (map<Vertice*, float>::iterator i = duracion.begin(); i != duracion.end(); i++){
			//i->first->nombre = Devuelve el nombre de la terminal destino
			//i->second = Devuelve el valor del viaje
			if(i->first->nombre == destino){
			    if(i->second == 2147483647){
			        cout << "No hay ruta disponible" <<endl;    
			    }else{
			        cout << "El camino mas barato de " << origen << " a " << i->first->nombre << " es de " << i->second <<" Hs"<< endl;    
			        	//Mostrar la ruta de viaje para el precio minimo
            		int indexAux = 0;
            		for (map<Vertice*, Vertice*>::iterator i = rutas.begin(); i != rutas.end(); i++)
            		{
            			Vertice* vAct = i->first;
                        
                        if(vAct->nombre == destino){
                			cout << "La ruta para este viaje es: "<<endl;
                			cout << "Terminal destino: ";
                			while (vAct != NULL)
                			{
                				cout << vAct->nombre << " <- ";
                				vAct = rutas[vAct];
                			}
                			cout << "Terminal origen"<<endl;
                			indexAux++;
                        }
            		}
			    }
			}
		}
	}

}


