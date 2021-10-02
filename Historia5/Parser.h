#ifndef parser_h
#define parser_h

#include <fstream>
#include <string>
#include "SymbolTable.h"

using namespace std;

class Parser
{
private:
    int PC=0;
    fstream archivoEntrada,archivoSalida;
    string lineaActual="";

public:
    SymbolTable tabla;

    Parser(string nomArchivo);      //abre un flujo/archivo de entrada y lo deja listo para realizar el parsing
    ~Parser();                      //destruye 

    bool hayComandos();             // pregunta si el archivo tiene más comandos
    bool esTipoA();
    bool esTipoC();
    bool esTipoL();
    string simbolo();               //retorna el simbolo o el decimal del @____ (solo para comandos A o L)
    string dest();                  //retorna el mnemonico del dest (tabla 2)
    string comp();                  //retorna el mnemonico del comp (tabla 1)
    string jump();                  //retorna el mnemonico del jump (tabla 3)
    int valor();                    //retorna el valor del tipo a 
};
#endif