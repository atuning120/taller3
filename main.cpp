/*Nombres: Cristian Nuñez (21.387.541-8)
           Eduardo Erices(21.600.760-3)¨*/
#include <iostream>
#include <string>
#include <vector>
#include "Nodo.h"
#include <fstream>
#include <sstream>
#include <climits>
#include <limits>
using namespace std;
//Clase Grafo
class Grafo {

public:
    vector<Nodo*> nodos;

    void agregarNodo(int id,string nombre,string tipo) {
        Nodo* nuevo= new Nodo(id,nombre,tipo);
        nodos.push_back(nuevo);
    }

    void agregarConexion(Nodo* nodoCliente, Nodo* nodoServidor, int velocidad, int distancia) {
        pair<Nodo*, pair<int, int>> nuevo= make_pair(nodoServidor,make_pair(velocidad,distancia));
        nodoCliente->conexiones.push_back(nuevo);
    }
    int calcularTiempoTransferencia(int tamArchivo, int velocidad, int distancia) {
        // Calcular el tiempo de transferencia (archivo dividido por velocidad multiplicado por distancia)
        while((tamArchivo%velocidad!=0)){
            tamArchivo++;
        }
        int division=(tamArchivo / velocidad);
        int calculo=division * distancia;
        return calculo;
    }

    // Implementación del algoritmo de Bellman-Ford adaptado
    void bellmanFord(Nodo* nodoInicio, Nodo* nodoDestino, int tamArchivo) {
        int n = nodos.size();
        vector<int> tiempoTotal(n, numeric_limits<int>::max());
        tiempoTotal[nodoInicio->id] = 0;
        vector<string> direccion;
        vector<int> tiempoDireccion;
        direccion.push_back(nodoInicio->nombre);
        bool Verificar=true;
        //Analizar el recorrido mas corto
        for (int i = 1; i < n; ++i) {
            for (Nodo* nodo : nodos) {
                for (pair<Nodo*, pair<int, int>> conexion : nodo->conexiones) {
                    int u = nodo->id;
                    int v = conexion.first->id;
                    int velocidad = conexion.second.first;
                    int distancia = conexion.second.second;

                    int tiempo = calcularTiempoTransferencia(tamArchivo, velocidad, distancia);

                    if (tiempoTotal[u] != numeric_limits<int>::max() && tiempoTotal[u] + tiempo < tiempoTotal[v]) {
                        tiempoTotal[v] = tiempoTotal[u] + tiempo;
                        //Guardar recorrido que se realiza desde el nodo origen al nodo destino
                        if(conexion.first->id==nodoDestino->id){
                            direccion.push_back(conexion.first->nombre);
                            tiempoDireccion.push_back(tiempo);
                            Verificar=false;
                        }
                        if(Verificar==true){
                            direccion.push_back(conexion.first->nombre);
                            tiempoDireccion.push_back(tiempo);
                        }
                    }
                }
            }
        }
        
        // Verificar si hay ciclo negativo
        for (Nodo* nodo : nodos) {
            for (pair<Nodo*, pair<int, int>> conexion : nodo->conexiones) {
                int u = nodo->id;
                int v = conexion.first->id;
                int velocidad = conexion.second.first;
                int distancia = conexion.second.second;

                int tiempo = calcularTiempoTransferencia(tamArchivo, velocidad, distancia);

                if (tiempoTotal[u] != numeric_limits<int>::max() && tiempoTotal[u] + tiempo < tiempoTotal[v]) {
                    cout << "Se detectó un ciclo negativo. No es posible continuar." << endl;
                    return;
                }
            }
        }
        //direccion.push_back(nodoDestino->nombre);
        // Calcular el tiempo total
        int tiempoTransferencia = tiempoTotal[nodoDestino->id];

        cout << "Tiempo total estimado para transferir un archivo de tamaño " << tamArchivo
             << " desde Nodo " << nodoInicio->id << " a Nodo " << nodoDestino->id
             << ": " << tiempoTransferencia << " unidades de tiempo." << endl;

        for(int i=0;i<direccion.size();i++){
            if(i==direccion.size()-1){
                cout<<direccion[i]<<endl;
            }else{
                cout<<direccion[i]<<"--("<<tiempoDireccion[i]<<"s)-->";
            }
        }
    }
};
//Modificar CSV
void rellenar(){
    srand(time(NULL));
    ofstream archivo;
    ofstream archivo2;
    archivo2.open("conexiones.csv");
    archivo.open("servidores.csv");
    archivo<<"id,nombre,tipo"<<endl;
    archivo2<<"idCliente,idServidor,velocidad,distancia"<<endl;
    vector<string> cliente;
    vector<string> servidor;
    for (int i = 0; i < 300; i++) {
        int num = i;
        string nombre = "Servidor" + to_string(i);
        int random = rand()%5+1;
        string tipo;
        if(random == 5){
            tipo = "router";
            servidor.push_back(to_string(i));
            for(string client:cliente){
                int random2 = rand()%10+1;
                int velocidadrand = (rand()%3+1)*300;
                archivo2<<client<<","<<i<<","<<velocidadrand<<","<<random2<<endl;
            }
            cliente.clear();
        }else{
            tipo="cliente";
            cliente.push_back(to_string(i));
        }
        archivo << num << "," << nombre << "," << tipo << endl;
    }
    archivo.close();
    for(int i = 0; i< servidor.size(); i++){
        for(int j = i+1; j< servidor.size(); j++){
            if(i!=j){
                int moneda = rand()%4+1;
                if(moneda == 1){
                    int random = rand()%1000+1;
                    int velocidad = (rand()%3+1)*1000;
                    archivo2<<servidor[i]<<","<<servidor[j]<<","<<velocidad<<","<<random<<endl;
                }
            }
        }
    }
    archivo2.close();
}
// Función para leer el archivo de nodos (servidores.csv)
void leerArchivoNodos(string nombreArchivo, Grafo &grafo) {
    //abrir el archivo
    ifstream archivoNodos;
    archivoNodos.open(nombreArchivo,ios::in);
    string linea;
    //Control de apertura del archivo
    if(!archivoNodos.is_open()){
        cout<< "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }
    //leer las lineas del archivo
    getline(archivoNodos, linea);
    while (getline(archivoNodos, linea)) {
        stringstream registro(linea);
        //seccionar en partes
        vector<string> partes;
        for(string dato;getline(registro,dato,',');){
            partes.push_back(dato);
        }
        std::stringstream ss(partes[0]);
        int id;
        ss >> id;
        string nombre= partes[1];
        string tipo=partes[2];
        //crear el nodo y agregarlo al grafo
        grafo.agregarNodo(id,nombre,tipo);
    }
    archivoNodos.close();
}
// Función para leer el archivo de conexiones (conexiones.csv)
void leerArchivoConexiones(string nombreArchivo, Grafo &grafo) {
    ifstream archivoConexiones;
    archivoConexiones.open(nombreArchivo,ios::in);
    string linea;
    //Control de apertura del archivo
    if(!archivoConexiones.is_open()){
        cout<< "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    //leer lineas
    getline(archivoConexiones, linea);
    while (getline(archivoConexiones, linea)) {
        stringstream registro(linea);
        //seccionar en partes
        vector<string> partes;
        for(string dato;getline(registro,dato,',');){
            partes.push_back(dato);
        }
        int idCliente=stoi(partes[0]);
        int idServidor=stoi(partes[1]);
        int velocidad=stoi(partes[2]);
        int distancia=stoi(partes[3]);
        // Buscar nodos correspondientes
        Nodo* nodoCliente = NULL;
        Nodo* nodoServidor = NULL;
        for(int i=0;i<grafo.nodos.size();i++){
            if (grafo.nodos[i]->id == idCliente) {
                nodoCliente = grafo.nodos[i];
            } else if (grafo.nodos[i]->id == idServidor) {
                nodoServidor = grafo.nodos[i];
            }
        }
        //asignar conexion 
        if (nodoCliente != NULL && nodoServidor != NULL) {
            grafo.agregarConexion(nodoCliente, nodoServidor, velocidad, distancia);
            grafo.agregarConexion(nodoServidor, nodoCliente, velocidad, distancia);
        }
    }
    archivoConexiones.close();
}
//Imprimir todos los nodos con sus conexiones
void imprimirConexiones(Grafo& grafo) {
    //recorrer el grafo
    for (Nodo* nodo : grafo.nodos) {
        //Mostrar la informacion de cada nodo del grafo
        cout<<"Nodo "<<nodo->id<<" ("<<nodo->nombre<<") - Tipo: "<<nodo->tipo<<endl;
        cout<<"Conexiones:"<<endl;
        //mostrar las informacion de todas las conecciones del Nodo
        for (pair<Nodo*, pair<int, int>> conexion : nodo->conexiones) {
            Nodo* nodoVecino = conexion.first;
            cout<<"  Conectado a Nodo "<<nodoVecino->id<<" ("<< nodoVecino->nombre<<") - Tipo: "<<nodoVecino->tipo;
            cout<<" | Velocidad: "<<conexion.second.first<<" | Distancia: "<<conexion.second.second<< endl;
        }
        cout << endl;
    }
}
//main
int main() {
    //rellenar();

    Grafo grafo;
    int idCliente, idDestinatario, tamArchivo;

    leerArchivoNodos("servidores.csv", grafo);
    leerArchivoConexiones("conexiones.csv", grafo);
    imprimirConexiones(grafo);

    cout<<"Ingrese el ID del cliente: ";  
    cin>>idCliente;

    while(grafo.nodos[idCliente]->tipo=="router" || idCliente<0 || idCliente >(grafo.nodos.size()-1)){
        cout << "La ID debe existir y corresponder a un cliente"<<endl;
        cout<<"Ingrese el ID del cliente: ";  
        cin>>idCliente;
    }

    cout << "Ingrese el ID del destinatario: ";
    cin >> idDestinatario;

    while(grafo.nodos[idDestinatario]->tipo=="router"|| idDestinatario<0 || idDestinatario >(grafo.nodos.size()-1)){
        cout << "La ID debe existir y corresponder a un cliente"<<endl;
        cout << "Ingrese el ID del destinatario: ";
        cin >> idDestinatario;
    }

    cout << "Ingrese el tamaño del archivo: ";
    cin >> tamArchivo;
    while(tamArchivo<=0){
        cout<<"Ingresa un tamaño valido...."<<endl;
        cout << "Ingrese el tamaño del archivo: ";
        cin >> tamArchivo;
    }

    // Llamar a Bellman-Ford con los nodos de inicio, destino y el tamaño del archivo
    grafo.bellmanFord(grafo.nodos[idCliente], grafo.nodos[idDestinatario], tamArchivo);
}