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
#include <stdlib.h>

using namespace std;
 
int main(int argc, char const *argv[])
{
    try
    {
            //inicializar
        string nomArchivo =argv[1];
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

                //primera pasada
            while (!objetoParser.archivoEntrada.eof()){

                if(objetoParser.hayComandos()){
                    if(objetoParser.esTipoL()){
                        string etiqueta = objetoParser.simbolo();
                        if(!objetoParser.tabla.esta(etiqueta)){
                            objetoParser.tabla.anadir(etiqueta,objetoParser.getPC());
                        }else{
                            throw "ERROR: no pueden haber dos etiquetas iguales";
                        }
                    }
                    else{
                        objetoParser.aumentarPC();
                    }
                }
                else{
                    continue;
                }

            }
                //segunda pasada
            objetoParser.archivoEntrada.clear();
            objetoParser.archivoEntrada.seekg(0,objetoParser.archivoEntrada.beg);
            while(!objetoParser.archivoEntrada.eof()){
                if(objetoParser.hayComandos()){
                    if(objetoParser.esTipoA()){

                        if(objetoParser.getLineaActual().at(1)<='9'&&objetoParser.getLineaActual().at(1)<='0'){
                            int registroA = atoi(objetoParser.valor().c_str());
                            string registroABin = '0'+Code::value(registroA);
                            objetoParser.archivoSalida<<registroABin<<endl;
                        }else{
                            string variable=objetoParser.valor();
                            if(objetoParser.tabla.esta(variable)){
                                int registroA = objetoParser.tabla.direccion(variable);
                                string registroABin = '0'+Code::value(registroA);
                                objetoParser.archivoSalida<<registroABin<<endl;
                            }else{
                                objetoParser.tabla.anadir(variable,objetoParser.tabla.getContador());
                                int registroA = objetoParser.tabla.direccion(variable);
                                string registroABin = '0'+Code::value(registroA);
                                objetoParser.archivoSalida<<registroABin<<endl;
                                objetoParser.tabla.aumentarContador();
                            }
                        }

                    }else if(objetoParser.esTipoC()){

                        string destino=objetoParser.dest();
                        string computational=objetoParser.comp();
                        string salto=objetoParser.jump();

                        destino= Code::dest(destino);
                        computational= Code::comp(computational);
                        salto= Code::dest(salto);

                        string registroCBin= "111"+computational+destino+salto;
                        objetoParser.archivoSalida<<registroCBin<<endl;                 

                    }else{
                        if(objetoParser.getLineaActual().at(0)=='('){
                            continue;
                        }else{
                            throw "ERROR: no se reconoce la sintaxis de la instrucción";
                        }
                    }
                }else{
                    continue;
                }
            }

        }else{
            throw "ERROR: El archivo "+nomArchivo+" no existe";
        }
    }else{
        throw "ERROR: La extension no es .asm";
    }
        
    }
    catch(const char* error)
    {
        std::cout << error << '\n';
    }catch(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > error)
    {
        std::cout << error << '\n';
    }

    //finalizar
    return 0;
}

