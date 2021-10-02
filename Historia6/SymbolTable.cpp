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
#include <iostream>

#define DEBUG

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << "\n")
#define DEBUG_STDOUT(x) (std::cout << (x) << "\n")
#else
#define DEBUG_STDERR(x) do{}while(0)
#define DEBUG_STDOUT(x) do{}while(0)
#endif

SymbolTable::SymbolTable(){

}
SymbolTable::~SymbolTable(){
    DEBUG_STDERR("-----se llamo el destructor de la tabla de simbolos------");
}

void SymbolTable::anadir(string symbol, int address){
    Tabla.insert({symbol,address});
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

//metodos que no tenian pseudo pero que su nombre dicen su función

void SymbolTable::aumentarContador()
{
    contadorRAM++;
}

int SymbolTable::getContador()
{
    return contadorRAM;
}