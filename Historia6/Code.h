#ifndef code_h
#define code_h

#include <string>
#include <map>

using namespace std;

class Code
{
private:
    
public:
    Code();
    ~Code();

    //al notar que no necesitamos construir un objeto code se decide definir los metodos estaticos
    
    static string dest(string mnemonic);   // devuelve el binario del dest 
    static string comp(string mnemonic);     // devuelve el binario del comp 
    static string jump(string mnemonic);   // devuelve el binario del jump 
    static string value(int direccion);   // devuelve el binario del valor del tipo A 
};
#endif 