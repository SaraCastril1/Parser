#ifndef parser_h
#define parser_h

#include <fstream>
#include <string>

using namespace std;

class Parser
{
private:
    
public:
    Parser(fstream archivo);    //abre un flujo/archivo de entrada y lo deja listo para realizar el parsing
    ~Parser();                  //destruye jeje

    bool hasMoreCommands();     // pregunta si el archivo tiene más comandos
    void advance();             // si hasMoreCommands --> siga revisando
    string commandType();       //retorna el tipo de comando(A,C o L) retorno aun no claro jeje 
    string symbol();            //retorna el simbolo o el decimal del @____ (solo para comandos A o L)
    string dest();              //retorna el mnemonico del dest (tabla 2)
    string comp();              //retorna el mnemonico del comp (tabla 1)
    string jump();              //retorna el mnemonico del jump (tabla 3)
};

#endif