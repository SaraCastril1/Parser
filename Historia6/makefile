Ejecutable: Main.cpp Code.o Parser.o SymbolTable.o
	g++ -g -o $@ Main.cpp Code.o Parser.o SymbolTable.o

Code.o: Code.cpp Code.h
	g++ -g -c Code.cpp

Parser.o: Parser.cpp Parser.h SymbolTable.o
	g++ -g -c Parser.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	g++ -g -c SymbolTable.cpp 

Traductor: Traductor.cpp Parser.cpp SymbolTable.cpp Code.cpp Parser.h Code.h SymbolTable.h 
	g++ -o Traductor Traductor.cpp Parser.cpp SymbolTable.cpp Code.cpp Parser.h Code.h SymbolTable.h