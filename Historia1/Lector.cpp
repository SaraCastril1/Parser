#include <fstream>
#include <iostream>
#include <string>
//diferencia entre string y string.h
using namespace std;

int main()
{
    string nombreArchivo;
    cin>>nombreArchivo;
    fstream archivo;
    archivo.open(nombreArchivo);
    if(!archivo){
        cout<<"El archivo "<<nombreArchivo<<" no existe";
    }
}
