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

void inicializar(string nomArchivo){
    if(nomArchivo.substr(nomArchivo.find("."),5)==".asm"){
        fstream archivoEntrada;
        archivoEntrada.open(nomArchivo);
        if(archivoEntrada){
            string nomArchivoS=nomArchivo.substr(0,nomArchivo.find("."))+".hack";
            fstream archivoSalida;
            archivoSalida.open(nomArchivoS,std::ios::out);//Se crea archivo.hack vacio.
            Parser objetoParser(nomArchivo,nomArchivoS);
            archivoEntrada.close();
            archivoSalida.close();

        }else{
            throw "ERROR: El archivo "+nomArchivo+" no existe";
        }
    }else{
        throw "ERROR: La extension no es .asm";
    }
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
    {
        inicializar(argv[1]);
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

