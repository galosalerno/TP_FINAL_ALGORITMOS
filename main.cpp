#include <iostream>
#include "nodo.h"
#include "terminal.h"
#include <string>
using namespace std;
#include <iostream>
#include <sstream>
#include <iostream>
#include "Grafo.h"
#include <fstream>

class AgenciaDeViaje
{
private:
  void metodoPrivado (){}
  Terminal terminales = Terminal ();
  Grafo *recorridos = new Grafo ();
public:
  AgenciaDeViaje (){
    this->metodoPrivado ();
    this->terminales.completarTerminales (10);
    this->terminales.leerTerminales ();
    this->recorridos->leerTerminales();
  }
  void consultarEstacion (){
    string cod;
    cout << "Ingrese el codigo " << endl;
    cin >> cod;
    this->terminales.buscarTerminalPorCodigo(cod);
  }
  void saveTerminalesInTxt(){
    ofstream file;
    file.open("terminales.txt");
    int largo = this -> terminales.consultarLargo();
    bool isEmpty = this -> terminales.vacia();
    if (!isEmpty) {
        for (int i=1; i<largo; i++) {
            string terminal = this->terminales.buscarTerminal(i);
            if(terminal!="null"){
                file <<terminal <<"\n";
            }
        }
        file.close();   
    }
}
  void altaTerminal(){
    string cod;
    cod = this->terminales.altaTerminal();
    this->recorridos->insertaVertice(cod);
    saveTerminalesInTxt();
  }
  void bajaTerminal(){
    string cod;
    cout << "Ingrese el codigo de la terminal" << endl;
    cin >> cod;
    this->terminales.bajaTerminal(cod);
    saveTerminalesInTxt();
  }

  void mostrarMenuPrincipal(){
    int numero;
    cout << endl;
    cout << "--------------------------------" << endl;
    cout << "---------MENU PRINCIPAL---------" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Ver viajes" << endl;
    cout << "2. Terminales de omnibus" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese una opcion: ";
    cin >> numero;
    cout << endl;

    switch (numero){
      case 1:
	      mostrarMenuViajes();
	      break;
      case 2:
	      mostrarMenuTerminales();
	      break;
      
      case 3:
        cout << "Adios!" << endl;
        return;
    }
  }
  void buscarPrecioMinimo(){
      string origen;
      string dest;
      cout<<"Ingrese el codigo de origen"<<endl;
      cin>>origen;
      cout<<"Ingrese el codigo de destino"<<endl;
      cin>>dest;
      this->recorridos->precioMinimo(origen,dest);
  }
  void buscarCaminoMinimo(){
      string origen;
      string destino;
      cout<<"Ingrese el codigo de origen"<<endl;
      cin>>origen;
      cout<<"Ingrese el codigo de destino"<<endl;
      cin>>destino;
      this->recorridos->caminoMinimo(origen,destino);
  }
  void mostrarMenuViajes(){
    int opc;
    cout << "--------------------------------" << endl;
    cout << "----------MENU VIAJES-----------" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Flash travel" << endl;
    cout << "2. Low cost" << endl;
    cout << "3. Ver recorridos" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << endl;
    cout << "Ingrese una opcion del menu: ";
    cin >> opc;
    cout << endl;
  
    switch (opc){
      case 1:{
        //Camino minimo
        buscarCaminoMinimo();
        mostrarMenuViajes();
        break;
      }
      case 2:{
            buscarPrecioMinimo();
            mostrarMenuViajes();
            break;
      }
      case 3:{
        if (recorridos->estaVacio ()){
	        cout << "No hay recorridos" << endl;
	      }
        else{
	        this ->recorridos->mostrarRecorridos();
	      }
      mostrarMenuViajes();
      }
      case 4:{
        mostrarMenuPrincipal();
        break;
      }
  }
  cin.get ();
  }
  void mostrarMenuTerminales(){
    int cont = 0;
    int numero;
    cout << "--------------------------------" << endl;
    cout << "---------MENU TERMINALES--------" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Consultar por una terminal en particular" << endl;
    cout << "2. Dar de alta una nueva terminal" << endl;
    cout << "3. Dar de baja alguna terminal" << endl;
    cout << "4. Mostrar todas las terminales" << endl;
    cout << "5. Volver al menu principal" << endl;
    cout << "Ingrese un numero entre 1 y 5 segun desee: ";
    cin >> numero;
    // Ignoramos el salto de linea para que no lo tome ningun 'cin' siguiente.
    cin.ignore ();
    switch (numero){
      case 1:
        consultarEstacion ();
      	mostrarMenuTerminales();
      case 2:
      	altaTerminal ();
	      mostrarMenuTerminales();
      case 3:
      	bajaTerminal ();
      	mostrarMenuTerminales();
      case 4:
      	this->terminales.mostrarTerminales();
	      mostrarMenuTerminales();
      case 5:
      	mostrarMenuPrincipal();
      default:
      	cout << "Opcion incorrecta";
      	;
    }
  }
};

int main ()
{
  AgenciaDeViaje agencia = AgenciaDeViaje ();
  agencia.mostrarMenuPrincipal();
  return 0;

}
