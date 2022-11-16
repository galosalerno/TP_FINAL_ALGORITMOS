#include "terminal.h"
#include <string>
#define HashMod 10
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>

//Funcion que recibe un caracter y devuelve su valor en ASCII
unsigned long long CharAEntero(char entrada)
{
	unsigned long long Salida;
	Salida = entrada;
	return Salida;
}
//Funcion que recibe un string y convierte cada caracter del mismo a ascii y las concatenta. Devuelve el valor del string en ASCCI (Ej COR = 67 79 82)
unsigned long long ObtenerNumero(string entrada)
{
	unsigned long long Salida=0;
	for(int i=0;entrada[i] != '\0';i++)
	{
		if(entrada[1+i] == '\0' && i==0)
			Salida+=CharAEntero(entrada[i]);
		else
		{
			if(i==0)
			{
				Salida += CharAEntero(entrada[i]);
				continue;
			}
			else
			{
				
				int miChar = CharAEntero(entrada[i]);
				if(miChar>99)
				{
					Salida*=1000;
				}
				else if(miChar>9)
				{
					Salida*=100;
				}
				
				Salida += miChar;
			}
				
			
		}
	}
	return Salida;
}

//Recibe un string y devuelve el valor en de la posicion a guardar el mismo.
int  FuncHash(string entrada)
{
	unsigned long long Amodular = ObtenerNumero(entrada);
	int Salida = Amodular%HashMod;
	return Salida;
}


Terminal::Terminal() {
    primero = 0;
    largo = 0;
}

bool Terminal::vacia() {
    return (largo == 0);
}

// altaTerminal: Se dara de alta una terminal, con todos los datos necesarios.(Los datos son pedidos al usuario por consola)
string Terminal::altaTerminal() {
    string codigo;
    string nombre;
    string ciudad;
    string pais;
    float superficie;
    int cantTerminales;
    int cantDestNac;
    int cantDestInter;
    cout << "Ingrese el codigo de la terminal: " << endl;
    getline(cin, codigo);
    cout << "Ingrese el nombre de la terminal: " << endl;
    getline(cin, nombre);
    cout << "Ingrese ciudad: " << endl;
    getline(cin, ciudad);
    cout << "Ingrese pais: " << endl;
    getline(cin, pais);
    cout << "Ingrese superficie: " << endl;
    cin >> superficie;
    cout << "Ingrese cantidad de terminales: " << endl;
    cin >> cantTerminales;
    cout << "Ingrese cantidad de destinos nacionales" << endl;
    cin >> cantDestNac;
    cout << "Ingrese cantidad de destinos internacionales" << endl;
    cin >> cantDestInter;
    
    int pos = FuncHash(codigo); //obtenemos la posicion en la cual guardaremos la terminal en la lista
    string d = codigo + " " + nombre + " "+ciudad+ " "+pais+ " "+to_string(superficie)+ " "+to_string(cantTerminales)+ " "+to_string(cantDestNac)+ " "+to_string(cantDestInter) ;

    Nodo* nuevo = new Nodo(d);

    if (pos == 1) {
        nuevo -> cambiar_siguiente(primero);
        primero = nuevo;
    } 
    else {
        Nodo* anterior = obtener_nodo(pos-1);
        Nodo* siguiente = anterior->obtener_siguiente();
        nuevo->cambiar_siguiente(siguiente);
        anterior->cambiar_siguiente(nuevo);
    }
        largo++;
        return codigo;
}

// altaTerminalHard: Se dara de alta una terminal, con todos los datos necesarios.(Los son pasados por parametros)
// La utilizamos para crear la lista vacia.
void Terminal::altaTerminalHard(string d, int pos){
    Nodo* nuevo = new Nodo(d);
    
    if (pos == 1) {
        nuevo -> cambiar_siguiente(primero);
        primero = nuevo;
    } 
    else {
        Nodo* anterior = obtener_nodo(pos-1);
        Nodo* siguiente = anterior->obtener_siguiente();
        nuevo->cambiar_siguiente(siguiente);
        anterior->cambiar_siguiente(nuevo);
    }
    
        largo++;
}

//Obtenemos el nodo que se encuentra en la posicion indicada en el parametro
Nodo* Terminal::obtener_nodo(int pos) {
    Nodo* aux = primero;
    
    for (int i=1; i<pos; i++) {
        aux = aux->obtener_siguiente();
    }
    return aux;
}

//Obtenemos el dato de la terminal que se encuentra en la posicion pasada por parametros
string Terminal::buscarTerminal(int pos) {
    Nodo* aux = obtener_nodo(pos);
    return aux->obtener_dato();
}

//Obtenemos el dato de la terminal con el codigo pasado por parametros, si lo encuentra.
string Terminal::buscarTerminalPorCodigo(string codigo) {
    int pos = FuncHash(codigo);
    Nodo* aux = obtener_nodo(pos+1);
    cout << "Posicion: " << pos << " -> " << aux->obtener_dato() << endl;
    return aux->obtener_dato();
}

//Damos de baja una terminal con el codigo pasado por parametros.
void Terminal::bajaTerminal(string cod) {
    int pos = FuncHash(cod);
    Nodo* nodoABorrar = obtener_nodo(pos+1);
    nodoABorrar->cambiar_dato("null");
}

//Damos de baja la terminal que se encuentre en la posicion pasada por parametros
void Terminal::bajaTerminalHard(int pos) {
    Nodo* borrar;

    if (pos == 1) {
        borrar = primero;
        primero = borrar->obtener_siguiente();
    }
    else {
        Nodo* anterior = obtener_nodo(pos-1);
        borrar = anterior->obtener_siguiente();
        Nodo* siguiente = borrar->obtener_siguiente();
        anterior->cambiar_siguiente(siguiente);
    }
    delete borrar;
    largo--;
}


Terminal::~Terminal() {
    while (!vacia()) {
        bajaTerminalHard(1);
    }
}

//Obtenemos la cantidad de terminales que tenemos dadas de alta
int Terminal::cantidadDeTerminales() {
    return largo;
}

//Se muestran todas las terminales dadas de altas, junto con los datos de cada una 
void Terminal::mostrarTerminales(){
    cout << "[" << endl;
    if (!vacia()) {
        for (int i=1; i<largo; i++) {
            string terminal = this->buscarTerminal(i);
            if(terminal!="null"){
                cout <<terminal << endl;    
            }
        }
    }
    cout << endl;
    cout << "]" <<endl;
}

//Armamos una lista vacia, del tamaño pasado por parametros 
void Terminal::completarTerminales(int tamano){
    while(this -> largo!= tamano){
        this -> altaTerminalHard("null", this -> largo + 1);
    }
}

//Obtenemos todas las terminales que se encuentran en el txt
//Utilizamos la funcion hash para obtener la posicion en la que se va a guardar, a partir del codigo de cada una 
void Terminal:: leerTerminales(){
    string line;	
    ifstream myfile("terminales.txt");
     //Terminal terminal;
     if (myfile.is_open())
     {
         while (getline(myfile, line)){
            string cod = line.substr(0,3);
            int pos = FuncHash(cod);
            this -> altaTerminalHard(line,pos);
         }
     }
}

//Obtenemos la cantidad de terminales que tenemos dadas de alta
int Terminal:: consultarLargo(){
        return this -> largo;
}


