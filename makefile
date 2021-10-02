verificar: tokens.o verificar.o
	g++ -g -o verificar verificar.o tokens.o

verificar.o: verificar.cpp tokens.o
	g++ -g -c verificar.cpp

tokens.o: tokens.cpp tokens.h
	g++ -g -c tokens.cpp

clean:
	rm -f *.o *.exe *.class
	rm -rf __pycache__/

java: Tokens.java
	javac Tokens.java

MiEJECUTABLE: Main.cpp Code.o Parser.o SymbolTable.o
	g++ -g -o $@ Main.cpp Code.o Parser.o SymbolTable.o

Code.o: Code.cpp Code.h
	g++ -g -c Code.cpp

Parser.o: Parser.cpp Parser.h SymbolTable.o
	g++ -g -c Parser.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	g++ -g -c SymbolTable.cpp 

prueba: Main.cpp Parser.cpp SymbolTable.cpp Code.cpp Parser.h Code.h SymbolTable.h 
	g++ -o prueba Main.cpp Parser.cpp SymbolTable.cpp Code.cpp Parser.h Code.h SymbolTable.h

Traductor: Traductor.cpp Parser.cpp SymbolTable.cpp Code.cpp Parser.h Code.h SymbolTable.h 
	g++ -o Traductor Traductor.cpp Parser.cpp SymbolTable.cpp Code.cpp Parser.h Code.h SymbolTable.h