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

Parser::Parser(string nomArchivo1, string nomArchivo2)
{
    archivoEntrada.open(nomArchivo1, ios::in); //Tretamiento de lectura
    archivoSalida.open(nomArchivo2, ios::app); //Tratamiento append.
}
Parser::~Parser()
{
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
        if (lineaActual.at(1) >= '0' && lineaActual.at(1) <= '9')
        {
           
            string registroNumerico = "@";

            while (lineaActual.at(c) >= '0' && lineaActual.at(c) <= '9' && c < lineaActual.length())
            {
                registroNumerico += lineaActual.at(c);
                c += 1;
            }
            if (lineaActual == registroNumerico)
            {
                return true;
            }
            else
            {
                throw "ERROR: Es una instruccion A mal escrita";
            }
        }
        else
        { 
            string registroAlfanumerico="@";

            while(lineaActual.at(c)!=' ' && c<lineaActual.length()){
                registroAlfanumerico += lineaActual.at(c);
                c += 1;
            }

            if(registroAlfanumerico.length()>1 && registroAlfanumerico==lineaActual){
                return true;
            }
            else{
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
    if (buscarIgual > 0 && buscarIgual < lineaActual.length() && buscarPuntoYComa > 0 && buscarPuntoYComa < lineaActual.length())
    {
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
                throw "ERROR: El computational no coincide con ninguno de los posibles";
            }
        }
        else
        {
            throw "ERROR: El Destino no coincide con ninguno de los posibles";
        }
    }
    else if (buscarPuntoYComa > 0 && buscarPuntoYComa < lineaActual.length())
    {
        string salto = jump();
        string listaJump[] = {"JGT", "JEQ", "JGE", "JLT", "JME", "JLE", "JMP"};
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
                throw "ERROR: El computational no coincide con ninguno de los posibles";
            }
        }
        else
        {
            throw "ERROR: El salto no coincide con ninguno de los posibles";
        }
    }
    else
    {
        return false;
    }
}
bool Parser::esTipoL()
{ //( soyunaetiqueta )
    //- soyun aetiqueta -
    //-soyun aetiqueta-
    if (lineaActual.at(0) == '(')
    {
        if (!(lineaActual.at(1) >= '0' && lineaActual.at(1) <= '9'))
        {
            if (lineaActual.at(lineaActual.length() - 1) == ')')
            {
                string posibleEtiqueta= simbolo();
                
                string registroetiqueta="";
                int c =0;
                while(posibleEtiqueta.at(c)!=' ' && c<posibleEtiqueta.length()){
                    registroetiqueta += posibleEtiqueta.at(c);
                    c += 1;
                }

                if(registroetiqueta==posibleEtiqueta){
                    return true;
                }
                else{
                    throw "ERROR: Es una etiqueta mal escrita";
                }
            }
            else
            {
                throw "ERROR: Las etiquetas deben de finalizar con parentesis";
            }
        }
        else
        {
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
    etiqueta.erase(0,etiqueta.find_first_not_of(' '));
    etiqueta.erase(etiqueta.find_last_not_of(' ')+1);
    return etiqueta; //( LOOP )
}
string Parser::dest()
{
    if (lineaActual.find("=") > 0 && lineaActual.find("=") < lineaActual.length())
    {
        string destino = lineaActual.substr(0, lineaActual.find("="));
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
    {//D  + 1->D+1
        string computational = lineaActual.substr(lineaActual.find("=") + 1);;
        while (computational.find(" ") >= 0 && computational.find(" ") < computational.length())
            {
                computational.erase(computational.find(" "), 1); //Borra solo el espacio (1 es la cantidad de caracteres a borrar, es decir longitud)
            }
        return computational;
    }
    else if (lineaActual.find(";") > 0 && lineaActual.find(";") < lineaActual.length())
    {
        string computational = lineaActual.substr(0, lineaActual.find(";"));
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