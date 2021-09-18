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

int main()
{
    string nombreArchivo,linea;
    cin>>nombreArchivo;
    fstream archivo;
    archivo.open(nombreArchivo);
    if(!archivo){
        cout<<"El archivo "<<nombreArchivo<<" no existe";
    }else{
        while(!archivo.eof()){
            getline(archivo,linea);
            DEBUG_STDOUT(linea);
        }
    }
    //.close??
}
