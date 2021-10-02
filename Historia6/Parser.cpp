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
#include <iostream>

#define DEBUG

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << "\n")
#define DEBUG_STDOUT(x) (std::cout << (x) << "\n")
#else
#define DEBUG_STDERR(x) do{}while(0)
#define DEBUG_STDOUT(x) do{}while(0)
#endif

Parser::Parser(string nomArchivo1, string nomArchivo2)
{
    archivoEntrada.open(nomArchivo1, ios::in); //Tretamiento de lectura
    archivoSalida.open(nomArchivo2, ios::app); //Tratamiento append.
}

Parser::~Parser()
{
    DEBUG_STDERR("-----se llamo el destructor del parser------");
    tabla.~SymbolTable();
    archivoEntrada.close();
    archivoSalida.close();
}

bool Parser::hayComandos()
{
    getline(archivoEntrada, lineaActual);
    if (lineaActual.find("//") >= 0 && lineaActual.find("//") < lineaActual.length())
    {
        lineaActual.erase(lineaActual.find("//")); //Borra todo lo que hay del "//"" en adelante
    }

    //respecto al pseudo cambia que se borran solo los espacios laterales y no todos como se pensaba

    lineaActual.erase(0,lineaActual.find_first_not_of(' '));//borra los espacios antes
    lineaActual.erase(lineaActual.find_last_not_of(' ')+1);//borra los espacios despues

    if (lineaActual.empty()) //Verifica si la linea actual está vacia o no.
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Parser::esTipoA()
{
    if (lineaActual.at(0) == '@')
    {
        int c = 1;
        if (lineaActual.length()>1 && lineaActual.at(1) >= '0' && lineaActual.at(1) <= '9')
        {
           
            string registroANumerico = "@";

            while (c < lineaActual.length() && lineaActual.at(c) >= '0' && lineaActual.at(c) <= '9' )
            {
                registroANumerico += lineaActual.at(c);
                c += 1;
            }

            //respecto al pseudo cambia que se pregunta si son iguales, notando así si hay siguiente o no como se pensaba en el pseudo

            if (lineaActual == registroANumerico)
            {
                return true;
            }
            else
            {
                DEBUG_STDOUT("LINEA CON ERROR:");
                DEBUG_STDOUT(lineaActual);
                throw "ERROR: Es una instruccion A mal escrita";
            }
        }
        else
        { 
            string registroAlfanumerico="@";

            while(c<lineaActual.length() && lineaActual.at(c)!=' ' ){
                registroAlfanumerico += lineaActual.at(c);
                c += 1;
            }

            //respecto al pseudo cambia que se pregunta si son iguales, notando así si hay siguiente o no como se pensaba en el pseudo
            //y se verifica que no haya una @ vacia

            if(registroAlfanumerico.length()>1 && registroAlfanumerico==lineaActual){
                return true;
            }
            else{
                DEBUG_STDOUT("LINEA CON ERROR:");
                DEBUG_STDOUT(lineaActual);
                throw "ERROR: Es una instruccion A mal escrita";
            }
            
        }
    }
    else
    {
        return false;
    }
}
bool Parser::esTipoC()
{
    int buscarIgual = lineaActual.find("=");
    int buscarPuntoYComa = lineaActual.find(";");

    //se añade el control de que debe ser <lineaActual.length() por retornos del metodo

    if (buscarIgual > 0 && buscarIgual < lineaActual.length() && buscarPuntoYComa > 0 && buscarPuntoYComa < lineaActual.length())
    {
        DEBUG_STDOUT("LINEA CON ERROR:");
        DEBUG_STDOUT(lineaActual);
        throw "ERROR: Las instrucciones tipo c no pueden tener ambos operadores (= y ;)";
    }
    else if (buscarIgual > 0 && buscarIgual < lineaActual.length())
    {
        string destino = dest();
        string listaDest[] = {"M", "D", "MD", "A", "AM", "AD", "AMD"};
        bool verificador = false;
        for (string i : listaDest)
        {
            if (destino == i)
            {
                verificador = true;
                break;
            }
        }
        if (verificador)
        {
            string computational = comp();
            string listaComp[] = {"0", "1", "-1", "D", "A", "!D", "!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A","D|M","D&M","M-D","D-M","D+M","M-1","M+1","-M","!M","M"};
            bool verificador2 = false;
            for (string i : listaComp)
            {
                if (computational == i)
                {
                    verificador2= true;
                    break;
                }
            }
            if (verificador2)
            {
                return true;
            }
            else
            {
                DEBUG_STDOUT("LINEA CON ERROR:");
                DEBUG_STDOUT(lineaActual);
                throw "ERROR: El computational no coincide con ninguno de los posibles";
            }
        }
        else
        {
            DEBUG_STDOUT("LINEA CON ERROR:");
            DEBUG_STDOUT(lineaActual);
            throw "ERROR: El Destino no coincide con ninguno de los posibles";
        }
    }
    else if (buscarPuntoYComa > 0 && buscarPuntoYComa < lineaActual.length())
    {
        string salto = jump();
        string listaJump[] = {"JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
        bool verificador = false;
        for (string i : listaJump)
        {
            if (salto == i)
            {
                verificador = true;
                break;
            }
        }
        if (verificador)
        {
            string computational = comp();
            string listaComp[] = {"0", "1", "-1", "D", "A", "!D", "!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A","D|M","D&M","M-D","D-M","D+M","M-1","M+1","-M","!M","M"};
            bool verificador2 = false;
            for (string i : listaComp)
            {
                if (computational == i)
                {
                    verificador2= true;
                    break;
                }
            }
            if (verificador2)
            {
                return true;
            }
            else
            {
                DEBUG_STDOUT("LINEA CON ERROR:");
                DEBUG_STDOUT(lineaActual);
                throw "ERROR: El computational no coincide con ninguno de los posibles";
            }
        }
        else
        {
            DEBUG_STDOUT("LINEA CON ERROR:");
            DEBUG_STDOUT(lineaActual);
            throw "ERROR: El salto no coincide con ninguno de los posibles";
        }
    }
    else
    {
        return false;
    }
}

bool Parser::esTipoL()
{   
    if (lineaActual.at(0) == '(')
    {   
        //cambia respecto al pseudo que la segunda pregunta que hacemos es que su segundo caracter no puede ser numero

        if (!(lineaActual.at(1) >= '0' && lineaActual.at(1) <= '9'))
        {
            //cambia respecto al pseudo que luego verificamos si termina correctamente la etiqueta
            
            if (lineaActual.at(lineaActual.length() - 1) == ')')
            {
                //cambia respecto al pseudo que vamos a revisar solo lo que está entre parentesis
                
                string posibleEtiqueta= simbolo();
                
                
                string registroetiqueta="";
                int c =0;

                //cambia respecto al pseudo que el ciclo parara si se llega a la longitud final, ve un espacio o un parentesis

                while(c<posibleEtiqueta.length()&&posibleEtiqueta.at(c)!=' '&&posibleEtiqueta.at(c)!='('&&posibleEtiqueta.at(c)!=')'){
                    
                    registroetiqueta += posibleEtiqueta.at(c);
                    
                    c += 1;
                }

                //cambia respecto al pseudo que se verificara si la cadena es vacía o si no es igual a lo que hay entre parentesis
               
                if(!posibleEtiqueta.empty() && registroetiqueta==posibleEtiqueta){
                    return true;
                }
                else{

                    DEBUG_STDOUT("LINEA CON ERROR:");
                    DEBUG_STDOUT(lineaActual);
                    throw ("ERROR: Es una etiqueta mal escrita");
                    
                }
            }
            else
            {
                DEBUG_STDOUT("LINEA CON ERROR:");
                DEBUG_STDOUT(lineaActual);
                throw "ERROR: Las etiquetas deben de finalizar con parentesis";
            }
        }
        else
        {
            DEBUG_STDOUT("LINEA CON ERROR:");
            DEBUG_STDOUT(lineaActual);
            throw "ERROR: Es una instruccion tipo L mal escrita, No se puede escribir etiquetas iniciando con numeros ";
        }
    }
    else
    {
        return false;
    }
}
string Parser::simbolo()
{
    string etiqueta =lineaActual.substr(1, lineaActual.length() - 2);

    //cambia respecto al pseudo que se quitan los espacios que puede tener en los bordes la etiqueta

    etiqueta.erase(0,etiqueta.find_first_not_of(' '));
    etiqueta.erase(etiqueta.find_last_not_of(' ')+1);
    return etiqueta; //( LOOP )
}
string Parser::dest()
{
    if (lineaActual.find("=") > 0 && lineaActual.find("=") < lineaActual.length())
    {
        string destino = lineaActual.substr(0, lineaActual.find("="));

        //cambia respecto al pseudo que se eliminan los espacios previos al igual

        destino.erase(destino.find_last_not_of(' ')+1);
        return destino; //MD   =1
    }
    else
    {
        return "null";
    }
}
string Parser::comp()
{
    if (lineaActual.find("=") > 0 && lineaActual.find("=") < lineaActual.length())
    {
        string computational = lineaActual.substr(lineaActual.find("=") + 1);

        //cambia respecto al pseudo que se eliminan los espacios en su totalidad

        while (computational.find(" ") >= 0 && computational.find(" ") < computational.length())
            {
                computational.erase(computational.find(" "), 1); //Borra solo el espacio (1 es la cantidad de caracteres a borrar, es decir longitud)
            }
        return computational;
    }
    else if (lineaActual.find(";") > 0 && lineaActual.find(";") < lineaActual.length())
    {
        string computational = lineaActual.substr(0, lineaActual.find(";"));
        
        //cambia respecto al pseudo que se eliminan los espacios en su totalidad
        
        while (computational.find(" ") >= 0 && computational.find(" ") < computational.length())
            {
                computational.erase(computational.find(" "), 1); //Borra solo el espacio (1 es la cantidad de caracteres a borrar, es decir longitud)
            }
        return computational;
    }
    else
    {
        return "null";
    }
    
}
string Parser::jump()
{
    if (lineaActual.find(";") > 0 && lineaActual.find(";") < lineaActual.length())
    {
        string salto = lineaActual.substr(lineaActual.find(";") + 1);
        
        //cambia respecto al pseudo que se eliminan los espacios posteriores al ;
       
        salto.erase(0,salto.find_first_not_of(' '));
        return salto; //D+1 ; JUMP
    }
    else
    {
        return "null";
    }
}

string Parser::valor()
{
    return lineaActual.substr(1);
}

//metodos que no tienen pseudo pero que su nombre expresa su funcion

void Parser::aumentarPC()
{
    PC++;
}

int Parser::getPC()
{
    return PC;
}

string Parser::getLineaActual()
{
    return lineaActual;
}