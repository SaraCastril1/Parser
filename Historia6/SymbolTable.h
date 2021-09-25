#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <map>

using namespace std;

class SymbolTable
{
private:
    map<string,int> Tabla={ {"SP",0},{"LCL",1},{"ARG",2},{"THIS",3},{"THAT",4},{"R0",0},{"R1",1},{"R2",2},{"R3",3},{"R4",4},{"R5",5},{"R6",6},{"R7",7},{"R8",8},{"R9",9},{"R10",10},{"R11",11},{"R12",12},{"R13",13},{"R14",14},{"R15",15},{"SCREEN",16384},{"KBD",24576} };
    int contadorRAM=16;
public:
    SymbolTable();                              //crea una tabla predefinida
    ~SymbolTable();

    void anadir(string symbol, int adress);     // añade simbolo-dirección a la tabla
    bool esta(string symbol);                   // responde si la tabla contiene el símbolo buscado
    int direccion(string symbol);               // devuelve la dirección del símbolo buscado
    int getContador();
    void aumentarContador();
};
#endif 