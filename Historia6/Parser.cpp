/**
 * Clase que se encarga de verificar que las instrucciones en el archivo leído sean correctas tanto sintactica como semánticamente:
 * 
 * @author Sara María Castrillón Ríos
 * @author Viviana Hoyos Sierra
 * @author Juan Felipe Pinzón Trejo
 */
#include <fstream>
#include <string.h>
#include "SymbolTable.h"
#include "Parser.h"
//#include <iostream>

Parser::Parser(string nomArchivo){

    if(nomArchivo.substr(nomArchivo.find("."),5)==".asm"){
        archivoEntrada.open(nomArchivo);
        if(archivoEntrada){
            string nomArchivoS=nomArchivo.substr(0,nomArchivo.find("."))+".hack";
            archivoSalida.open(nomArchivoS,std::ios::out);
        }else{
            throw "ERROR: El archivo "+nomArchivo+" no existe";
        }
    }else{
        throw "ERROR: La extension no es .asm";
    }
}    
Parser::~Parser(){

}                  

bool Parser::hayComandos(){
    return true;
}     
bool Parser::esTipoA(){
    return true;
}
bool Parser::esTipoC(){
    return true;
}
bool Parser::esTipoL(){
    return true;
}
string Parser::simbolo(){
    return"";
}          
string Parser::dest(){
    return"";
}           
string Parser::comp(){
    return"";
}              
string Parser::jump(){
    return"";
}              
int Parser::valor(){
    return 1;
}  