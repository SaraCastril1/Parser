/**
 * Clase que maneja la tabla de símbolos del hack
 * 
 * @author Sara María Castrillón Ríos
 * @author Viviana Hoyos Sierra
 * @author Juan Felipe Pinzón Trejo
 */
#include <string>
#include <map>
#include "SymbolTable.h"

SymbolTable::SymbolTable(){

}
SymbolTable::~SymbolTable(){

}

void SymbolTable::anadir(string symbol, int adress){
    Tabla.insert({symbol,adress});
}
bool SymbolTable::esta(string symbol){
    auto busqueda = Tabla.find(symbol);
    if (busqueda!=Tabla.end()){
        return true;
    }else{
        return false;
    }

}
int SymbolTable::direccion(string symbol){
    return Tabla[symbol];
}
void SymbolTable::aumentarContador()
{
    contadorRAM++;
}
int SymbolTable::getContador()
{
    return contadorRAM;
}