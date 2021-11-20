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

//#define DEBUG

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << "\n")
#define DEBUG_STDOUT(x) (std::cout << (x) << "\n")
#else
#define DEBUG_STDERR(x) do{}while(0)
#define DEBUG_STDOUT(x) do{}while(0)
#endif

using namespace std;

Parser* inicializar(string nomArchivo){
    if(nomArchivo.substr(nomArchivo.find("."),5)==".asm"){
        fstream archivoEntrada;
        archivoEntrada.open(nomArchivo);
        if(archivoEntrada){
            string nomArchivoS=nomArchivo.substr(0,nomArchivo.find("."))+".hack";
            fstream archivoSalida;
            archivoSalida.open(nomArchivoS,std::ios::out);//Se crea archivo.hack vacio.
            Parser* objetoParser= new Parser(nomArchivo,nomArchivoS);
            archivoEntrada.close();
            archivoSalida.close();
            return objetoParser;
        }else{
            throw "ERROR: El archivo "+nomArchivo+" no existe";
        }
    }else{
        throw "ERROR: La extension no es .asm";
    }
};

Parser* primeraPasada(Parser* objetoParser){
    
    while (! objetoParser->archivoEntrada.eof()){

        if(objetoParser->hayComandos()){
            if(objetoParser->esTipoL()){
                string etiqueta = objetoParser->simbolo();
                DEBUG_STDOUT("encuentra una etiqueta con simbolo:");
                DEBUG_STDOUT(etiqueta);
                if(!objetoParser->tabla.esta(etiqueta)){
                    objetoParser->tabla.anadir(etiqueta,objetoParser->getPC());
                    DEBUG_STDOUT("se ingresa la etiqueta en PC =");
                    DEBUG_STDOUT(objetoParser->getPC());

                }else{
                    throw "ERROR: no pueden haber dos etiquetas iguales";
                }
            }
            else{
                DEBUG_STDOUT(objetoParser->getLineaActual());
                DEBUG_STDOUT(objetoParser->getPC());
                objetoParser->aumentarPC();
            }
        }
        else{
            continue;
        }

    }

    return objetoParser;

};

Parser* segundaPasada(Parser* objetoParser){

    //segunda pasada
    DEBUG_STDOUT("llego a la segunda pasada");
    objetoParser->archivoEntrada.clear();
    objetoParser->archivoEntrada.seekg(0,objetoParser->archivoEntrada.beg);
    while(!objetoParser->archivoEntrada.eof()){
        if(objetoParser->hayComandos()){
            if(objetoParser->esTipoA()){

                DEBUG_STDOUT("encuentra una instruccion tipo A con valor:");
                DEBUG_STDOUT(objetoParser->valor());

                if(objetoParser->getLineaActual().at(1)<='9'&&objetoParser->getLineaActual().at(1)>='0'){
                    int registroA = atoi(objetoParser->valor().c_str());
                    string registroABin = '0'+Code::value(registroA);
                    DEBUG_STDOUT("La instruccion tipo A en binario es:");
                    DEBUG_STDOUT(registroABin);
                    objetoParser->archivoSalida<<registroABin<<endl;
                }else{
                    string variable=objetoParser->valor();
                    if(objetoParser->tabla.esta(variable)){
                        int registroA = objetoParser->tabla.direccion(variable);
                        string registroABin = '0'+Code::value(registroA);
                        DEBUG_STDOUT("La instruccion ya estaba en la tabla");
                        DEBUG_STDOUT("La instruccion tipo A en binario es:");
                        DEBUG_STDOUT(registroABin);
                        objetoParser->archivoSalida<<registroABin<<endl;
                    }else{
                        objetoParser->tabla.anadir(variable,objetoParser->tabla.getContador());
                        int registroA = objetoParser->tabla.direccion(variable);
                        string registroABin = '0'+Code::value(registroA);
                        DEBUG_STDOUT("La instruccion no estaba en la tabla");
                        DEBUG_STDOUT("La instruccion se ingresa en con la direccion:");
                        DEBUG_STDOUT(registroA);
                        DEBUG_STDOUT("La instruccion tipo A en binario es:");
                        DEBUG_STDOUT(registroABin);
                        objetoParser->archivoSalida<<registroABin<<endl;
                        objetoParser->tabla.aumentarContador();
                        DEBUG_STDOUT("se aumenta el contador");

                    }
                }

            }else if(objetoParser->esTipoC()){

                string destino=objetoParser->dest();
                string computational=objetoParser->comp();
                string salto=objetoParser->jump();

                //cambia respecto al pseudo que se eliminan varias comparaciones pues siembre debemos incluir el dest, comp y jump, son esos mismos metodos los que se encargan de retornar los null en caso de tenerlos

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
                objetoParser->archivoSalida<<registroCBin<<endl;                 

            }else{
                if(objetoParser->getLineaActual().at(0)=='('){
                    continue;
                }else{
                    
                    DEBUG_STDOUT("LINEA CON ERROR:");
                    DEBUG_STDOUT(objetoParser->getLineaActual());
                    throw "ERROR: no se reconoce la sintaxis de la instruccion";
                    
                }
            }
        }else{
            continue;
        }
    }

    return objetoParser;

};

void finalizar(Parser* objetoParser){

    objetoParser->~Parser();
    
};
 
int main(int argc, char const *argv[])
{
    try
    {
        if(argc!=2){
            cout<<"hubo un problema con los datos ingresados por terminal\npor favor verificar que este ingresando el nombre del archivo \ny que este mismo no este separado por espacios";
        }else{
            finalizar(segundaPasada(primeraPasada(inicializar(argv[1]))));
        }

        //inicializar(argv[1]);
    }
    catch(const char* error)
    {
        std::cout << error << '\n';
    }catch(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > error)
    {
        std::cout << error << '\n';
    }

    return 0;
}

