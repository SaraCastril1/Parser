#ifndef parser_h
#define parser_h

#include <fstream>
#include <string>
#include "SymbolTable.h"

using namespace std;

class Parser
{
private:

    //se ven necesarios los siguientes atributos
    int PC=0;
    fstream archivoEntrada,archivoSalida;
    string lineaActual="";

public:
    SymbolTable tabla;

    //debido a los problemas se decide cambiar los parametros del costructor

    Parser(string nomArchivo);      //abre un flujo/archivo de entrada y lo deja listo para realizar el parsing
    ~Parser();                      //destruye 

    //se decide prescindir de advance, pues su funcionalidad es tomada por un ciclo
    //se decide cambiar algunos nombres
    //se decide dividir commandType en los tres esTipoX()
    //se decide separar symbol en simbolo y en valor para una implementacion separada 
    
    bool hayComandos();         //pregunta si el archivo tiene más comandos
    bool esTipoA();
    bool esTipoC();
    bool esTipoL();
    string simbolo();           //retorna el simbolo  L
    string dest();              //retorna el mnemonico del dest (tabla 2)
    string comp();              //retorna el mnemonico del comp (tabla 1)
    string jump();              //retorna el mnemonico del jump (tabla 3)
    int valor();                //retorna el valor del tipo a 
};
#endif