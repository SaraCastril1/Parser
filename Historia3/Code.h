#ifndef code_h
#define code_h

#include <string>

using namespace std;

class Code
{
private:
    
public:
    Code();//ta vacío?
    ~Code();

    short dest(string mnemonic);   // devuelve el binario del dest (char[3]?)
    int comp(string mnemonic);     // devuelve el binario del comp (char[7]?)
    short jump(string mnemonic);   // devuelve el binario del jump (char[3]?)
};
#endif 