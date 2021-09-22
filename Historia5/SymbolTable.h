#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <map>

using namespace std;

class SymbolTable
{
private:
    map<string,int> Tabla;
    int contadorRAM=16;
public:
    SymbolTable();                              //crea una tabla predefinida
    ~SymbolTable();

    void anadir(string symbol, int adress);     // añade simbolo-dirección a la tabla
    bool esta(string symbol);                   // responde si la tabla contiene el símbolo buscado
    int direccion(string symbol);               // devuelve la dirección del símbolo buscado
};
#endif 