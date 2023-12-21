#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Nodo {
public:
    int id;
    string nombre;
    string tipo;
    vector<pair<Nodo*, pair<int, int>>> conexiones;

    Nodo(int,string,string);
};
Nodo::Nodo(int id,string nombre,string tipo){
    this->id=id;
    this->nombre=nombre;
    this->tipo=tipo;
}