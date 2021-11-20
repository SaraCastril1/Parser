#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    if(argc==1){
        cout<<"no se ingreso ningun nombre por terminal";
    }else{
        string nombreArchivo;
        nombreArchivo=argv[1];
        fstream archivo;
        archivo.open(nombreArchivo);
        if(!archivo){
            cout<<"El archivo "<<nombreArchivo<<" no existe";
        }
        archivo.close();
    }

}
