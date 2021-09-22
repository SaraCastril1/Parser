#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string nombreArchivo;
    nombreArchivo=argv[1];
    fstream archivo;
    archivo.open(nombreArchivo);
    if(!archivo){
        cout<<"El archivo "<<nombreArchivo<<" no existe";
    }
    archivo.close();
}
