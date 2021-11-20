#include <fstream>
#include <iostream>
#include <string>

#define DEBUG

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << "\n")
#define DEBUG_STDOUT(x) (std::cout << (x) << "\n")
#else
#define DEBUG_STDERR(x) do{}while(0)
#define DEBUG_STDOUT(x) do{}while(0)
#endif

using namespace std;

int main(int argc, char *argv[])
{
    if(argc==1){
        cout<<"no se ingreso ningun nombre por terminal";
    }else{
        string nombreArchivo, linea;
        nombreArchivo=argv[1];
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
        archivo.close();
    }
}
