#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>

using namespace std;

class SymbolTable
{
private:
    
public:
    SymbolTable();//crea una tabla vacía
    ~SymbolTable();

    void addEntry(string symbol, int adress);   // añade simbolo-dirección a la tabla
    bool contains(string symbol);               // responde si la tabla contiene el símbolo buscado
    int GetAddress(string symbol);              // devuelve la dirección del símbolo buscado
};
#endif 