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
    string lineaActual="";

public:
    SymbolTable tabla=SymbolTable(); //Tabla inicializada
    fstream archivoEntrada,archivoSalida; // Pendiente de correccion
    Parser(string nomArchivo1,string nomArchivo2);    //abre un flujo/archivo de entrada y lo deja listo para realizar el parsing
    ~Parser();                  //destruye jeje

    bool hayComandos();     // pregunta si el archivo tiene más comandos
    bool esTipoA();
    bool esTipoC();
    bool esTipoL();
    string simbolo();           //retorna el simbolo o el decimal del @____ (solo para comandos A o L)
    string dest();              //retorna el mnemonico del dest (tabla 2)
    string comp();              //retorna el mnemonico del comp (tabla 1)
    string jump();              //retorna el mnemonico del jump (tabla 3)
    string valor();                //retorna el valor del tipo a 
    void aumentarPC();
    int getPC();
    string getLineaActual();
};
#endif