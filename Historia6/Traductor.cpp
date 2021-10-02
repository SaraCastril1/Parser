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

#define DEBUG

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << "\n")
#define DEBUG_STDOUT(x) (std::cout << (x) << "\n")
#else
#define DEBUG_STDERR(x) do{}while(0)
#define DEBUG_STDOUT(x) do{}while(0)
#endif

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
            DEBUG_STDOUT("llego a la primera pasada");
            while (!objetoParser.archivoEntrada.eof()){

                if(objetoParser.hayComandos()){
                    if(objetoParser.esTipoL()){
                        string etiqueta = objetoParser.simbolo();
                        DEBUG_STDOUT("encuentra una etiqueta con simbolo:");
                        DEBUG_STDOUT(etiqueta);
                        if(!objetoParser.tabla.esta(etiqueta)){
                            objetoParser.tabla.anadir(etiqueta,objetoParser.getPC());
                            DEBUG_STDOUT("se ingresa la etiqueta en PC =");
                            DEBUG_STDOUT(objetoParser.getPC());

                        }else{
                            throw "ERROR: no pueden haber dos etiquetas iguales";
                        }
                    }
                    else{
                        DEBUG_STDOUT(objetoParser.getLineaActual());
                        DEBUG_STDOUT(objetoParser.getPC());
                        objetoParser.aumentarPC();
                    }
                }
                else{
                    continue;
                }

            }
                //segunda pasada
            DEBUG_STDOUT("llego a la segunda pasada");
            objetoParser.archivoEntrada.clear();
            objetoParser.archivoEntrada.seekg(0,objetoParser.archivoEntrada.beg);
            while(!objetoParser.archivoEntrada.eof()){
                if(objetoParser.hayComandos()){
                    if(objetoParser.esTipoA()){

                        DEBUG_STDOUT("encuentra una instruccion tipo A con valor:");
                        DEBUG_STDOUT(objetoParser.valor());

                        if(objetoParser.getLineaActual().at(1)<='9'&&objetoParser.getLineaActual().at(1)>='0'){
                            int registroA = atoi(objetoParser.valor().c_str());
                            string registroABin = '0'+Code::value(registroA);
                            DEBUG_STDOUT("La instruccion tipo A en binario es:");
                            DEBUG_STDOUT(registroABin);
                            objetoParser.archivoSalida<<registroABin<<endl;
                        }else{
                            string variable=objetoParser.valor();
                            if(objetoParser.tabla.esta(variable)){
                                int registroA = objetoParser.tabla.direccion(variable);
                                string registroABin = '0'+Code::value(registroA);
                                DEBUG_STDOUT("La instruccion ya estaba en la tabla");
                                DEBUG_STDOUT("La instruccion tipo A en binario es:");
                                DEBUG_STDOUT(registroABin);
                                objetoParser.archivoSalida<<registroABin<<endl;
                            }else{
                                objetoParser.tabla.anadir(variable,objetoParser.tabla.getContador());
                                int registroA = objetoParser.tabla.direccion(variable);
                                string registroABin = '0'+Code::value(registroA);
                                DEBUG_STDOUT("La instruccion no estaba en la tabla");
                                DEBUG_STDOUT("La instruccion se ingresa en con la direccion:");
                                DEBUG_STDOUT(registroA);
                                DEBUG_STDOUT("La instruccion tipo A en binario es:");
                                DEBUG_STDOUT(registroABin);
                                objetoParser.archivoSalida<<registroABin<<endl;
                                objetoParser.tabla.aumentarContador();
                                DEBUG_STDOUT("se aumenta el contador");

                            }
                        }

                    }else if(objetoParser.esTipoC()){

                        string destino=objetoParser.dest();
                        string computational=objetoParser.comp();
                        string salto=objetoParser.jump();

                        DEBUG_STDOUT("Los nemonicos correspondientes (c-d-j) son:");
                        DEBUG_STDOUT(computational);
                        DEBUG_STDOUT(destino);
                        DEBUG_STDOUT(salto);

                        destino= Code::dest(destino);
                        computational= Code::comp(computational);
                        salto= Code::jump(salto);
                        DEBUG_STDOUT("Los binarios correspondientes (c-d-j) son:");
                        DEBUG_STDOUT(computational);
                        DEBUG_STDOUT(destino);
                        DEBUG_STDOUT(salto);

                        string registroCBin= "111"+computational+destino+salto;
                        DEBUG_STDOUT("el registro en binario es:");
                        DEBUG_STDOUT(registroCBin);
                        objetoParser.archivoSalida<<registroCBin<<endl;                 

                    }else{
                        if(objetoParser.getLineaActual().at(0)=='('){
                            continue;
                        }else{
                            
                            DEBUG_STDOUT("LINEA CON ERROR:");
                            DEBUG_STDOUT(objetoParser.getLineaActual());
                            throw "ERROR: no se reconoce la sintaxis de la instruccion";
                            
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
        DEBUG_STDOUT("atrape un error char");
        std::cout<<error<<'\n';

    }catch(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > error)
    {
        DEBUG_STDOUT("atrape un error string");
        std::cout<<error<<'\n';
    }

    //finalizar
    DEBUG_STDERR("llegamos a finalizar");
    //no me deja eliminar objetos porq por alcance ya se eliminaron 
    return 0;
}

