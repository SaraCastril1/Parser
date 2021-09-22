/**
 * Main a ejecutar (relaciona todos los métodos creados)
 * 
 * @author Sara María Castrillón Ríos
 * @author Viviana Hoyos Sierra
 * @author Juan Felipe Pinzón Trejo
 */
#include "Code.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <iostream>

using namespace std;

void inicializar(){

};
void primeraPasada(){

};
void segundaPasada(){

};
void finalizar(){
    
};
 
int main(int argc, char const *argv[])
{
    try
    {// pa que parseas sin abrir el archivo
        Parser parserito(argv[1]);
        inicializar();
        primeraPasada();
        segundaPasada();//cambiar puntero || abrir y volver a cerrar
    }
    catch(const char* error)
    {
        std::cout << error << '\n';
    }catch(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > error)
    {
        std::cout << error << '\n';
    }

    finalizar();
    return 0;
}

