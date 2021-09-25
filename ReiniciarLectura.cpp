#include <fstream>
#include <iostream>
#include <string>

//diferencia entre string y string.h

#define DEBUG

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << "\n")
#define DEBUG_STDOUT(x) (std::cout << (x) << "\n")
#else
#define DEBUG_STDERR(x) do{}while(0)
#define DEBUG_STDOUT(x) do{}while(0)
#endif

using namespace std;
//  --> método main que toma las lineas sin espaciones, sin comentarios y sin lineas vacías y las añade a un texto nuevo 
int main(int argc, char *argv[])
{   /*
    //ojo el metodo substring trabaja con los parámetros (punto inicial(inclusivo) , longitud del stringNuevo)
    //si me paso del final no importa, no me sale error jeje 
    string texto="si empezra asi no da (texto con @de todito) //si o que?";
    cout<<"Texto completo: "<<texto<<endl<<endl;
    cout<<"indice primer parentesis: "<<texto.find('(')<<"y el indice segundo parentesis: "<<texto.find(')')<<endl;
    string textoEntreParentesis=texto.substr(texto.find('(')+1,(texto.find(')')-texto.find('(')-1));
    cout<<"Texto entre parentesis: "<<textoEntreParentesis<<endl<<endl;

    string nombreArchivo,linea;
    nombreArchivo=argv[1];
    fstream archivo;
    archivo.open(nombreArchivo);
    if(!archivo){
        cout<<"El archivo "<<nombreArchivo<<" no existe";
    }else{

        
        //elimina los comentarios
        string texto = "luego de esto hay un comentario //jejejejje";
        cout<<"-"<<texto<<"-"<<endl;
        texto.erase(texto.find("//"));
        cout<<"-"<<texto<<"-"<<endl;
        

        
        //elimina los espacios
        string texto = "     ";
        cout<<"-"<<texto<<"-"<<endl;
        int a=1;
        while((texto.find(' ',0)<texto.length())&&(texto.find(' ',0)>=0)&&(texto.length()>0)){
            cout<<a<<" el espacio esta en: "<<(texto.find(' ',0))<<endl;
            texto.erase(texto.find(' ',0),1);
            cout<<texto<<endl;
            a++;
        }
        cout<<"-"<<texto<<"-"<<endl;
        

        
        //revisar la longitud de un string
        cout<<endl<<"paso 1"<<endl;
        
        getline(archivo,linea);
        cout<<"linea actual:--"<<linea<<"--Longitud:"<<linea.length()<<endl;
        getline(archivo,linea);
        cout<<"linea actual:--"<<linea<<"--Longitud:"<<linea.length()<<endl;
        getline(archivo,linea);
        cout<<"linea actual:--"<<linea<<"--Longitud:"<<linea.length()<<endl;
        linea.erase(0);
        cout<<"linea borrada:--"<<linea<<"--Longitud:"<<linea.length()<<endl;
        
        
        
        //mostrar el texto nuevamente sin cerrar el archivo --> puntero seekg
        cout<<endl<<"paso 2"<<endl;
        while(!archivo.eof()){
            getline(archivo,linea);
            cout<<linea<<endl;
        }

        archivo.clear();
        archivo.seekg(0, archivo.beg);
        cout<<endl<<"paso 3"<<endl;
        while(!archivo.eof()){
            getline(archivo,linea);
            cout<<linea<<endl;
        }
        

       fstream nuevito;
       nuevito.open("nuevo.txt",ios::out);
       nuevito.close();

       cout<<endl<<"paso completo"<<endl;
        while(!archivo.eof()){
            getline(archivo,linea);
            cout<<linea<<endl;
        }

        archivo.clear();
        archivo.seekg(0, archivo.beg);
        
        fstream nuevito;
        nuevito.open("nuevo.txt",ios::out);
        nuevito.close();
        
        nuevito.open("nuevo.txt",ios::app);
        cout<<endl<<"paso sin comentarios ni espacios"<<endl;
        while(!archivo.eof()){
            getline(archivo,linea);
                                            //para evitar el .end
                if((linea.find("//")>=0)&&(linea.find("//")<=linea.length())){
                    linea.erase(linea.find("//"));
                }
                                            //para evitar el .end
                while((linea.find(" ")>=0)&&(linea.find(" ")<=linea.length())){
                    linea.erase(linea.find(" "),1);
                }
                if(!linea.empty()){
                    cout<<linea<<endl;
                    nuevito<<linea<<endl;
                }
            
        }
        nuevito.close();
    }
    archivo.close();

    system("pause");*/

    //revisar si hay tokens:
    string texto1="yo no tengo espacios";
    string texto2="     yo tengo espacios al principio";
    string texto3="yo tengo espacios al final          ";
    string texto4="        yo tengo por parte y parte       ";
    string texto5="          ";

    cout<<texto1.find_first_not_of(' ');
    texto1.erase(0,texto1.find_first_not_of(' '));
    cout<<texto1.find_last_not_of(' ');
    texto1.erase(texto1.find_last_not_of(' ')+1);

    cout<<"el texto resultante es: -"<<texto1<<"-"<<endl;

    cout<<texto2.find_first_not_of(' ');
    texto2.erase(0,texto2.find_first_not_of(' '));
    cout<<texto2.find_last_not_of(' ');
    texto2.erase(texto2.find_last_not_of(' ')+1);

    cout<<"el texto resultante es: -"<<texto2<<"-"<<endl;

    cout<<texto3.find_first_not_of(' ');
    texto3.erase(0,texto3.find_first_not_of(' '));
    cout<<texto3.find_last_not_of(' ');
    texto3.erase(texto3.find_last_not_of(' ')+1);

    cout<<"el texto resultante es: -"<<texto3<<"-"<<endl;

    cout<<texto4.find_first_not_of(' ');
    texto4.erase(0,texto4.find_first_not_of(' '));
    cout<<texto4.find_first_not_of(' ');
    texto4.erase(texto4.find_last_not_of(' ')+1);

    cout<<"el texto resultante es: -"<<texto4<<"-"<<endl;

    cout<<texto5.find_first_not_of(' ');
    texto5.erase(0,texto5.find_first_not_of(' '));
    cout<<texto5.find_first_not_of(' ');
    texto5.erase(texto5.find_last_not_of(' ')+1);

    cout<<"el texto resultante es: -"<<texto5<<"-"<<endl;

    //para hacer el trim de una cadena 
    texto1.erase(0,texto1.find_first_not_of(' '));
    texto1.erase(texto1.find_last_not_of(' ')+1);
}


