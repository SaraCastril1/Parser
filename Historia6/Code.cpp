/**
 * Clase que pasa a binario los mnemónicos que reciba de instrucciones (tipo C) y los valores de instrucciones (tipo A):
 * 
 * @author Sara María Castrillón Ríos
 * @author Viviana Hoyos Sierra
 * @author Juan Felipe Pinzón Trejo
 */
#include <string>
#include <map>
#include "Code.h"
//estatico
string Code::dest(string mnemonic){
    
    map<string,string> Tabla2={{"null","000"},{"M","001"},{"D","010"},{"MD","011"},{"A","100"},{"AM","101"},{"AD","110"},{"AMD","111"}};
    return Tabla2[mnemonic];

}
string Code::comp(string mnemonic){

    map<string,string> Tabla1={{"0","0101010"},{"1","0111111"},{"-1","0111010"},{"D","0001100"},{"A","0110000"},{"!D","0001101"},{"!A","0110001"},{"-D","0001111"},{"-A","0110011"},{"D+1","0011111"},{"A+1","0110111"},{"D-1","0001110"},{"A-1","0110010"},{"D+A","0000010"},{"D-A","0010011"},{"A-D","0000111"},{"D&A","0000000"},{"D|A","0010101"},{"D|M","1010101"},{"D&M","1000000"},{"M-D","1000111"},{"D-M","1010011"},{"D+M","1000010"},{"M-1","1110010"},{"M+1","1110111"},{"-M","1110011"},{"!M","1110001"},{"M","1110000"}};
    return Tabla1[mnemonic];
    
}
string Code::jump(string mnemonic){
    map<string,string> Tabla3={{"null","000"},{"JGT","001"},{"JEQ","010"},{"JGE","011"},{"JLT","100"},{"JNE","101"},{"JLE","110"},{"JMP","111"}};
    return Tabla3[mnemonic];
}
string Code::value(int direccion){
    string registroA="";
    int datoADividir=direccion;
    if(direccion==0){
        registroA+="000000000000000";
    }
    else{
        for(int num=0;num<15;num++){
            registroA=to_string(datoADividir%2)+registroA;
            datoADividir/=2;
        }
    }
    return registroA;
}
//q hacemos con ustedes ah?
Code::~Code(){

}
Code::Code(){
    
}
