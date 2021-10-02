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

    string dest(string mnemonic);   // devuelve el binario del dest 
    string comp(string mnemonic);     // devuelve el binario del comp 
    string jump(string mnemonic);   // devuelve el binario del jump 

    //se implementa un metodo que traduce a binario pues la api no lo incluia
    string value(int direccion);   // devuelve el binario del valor del tipo A 
};
#endif 