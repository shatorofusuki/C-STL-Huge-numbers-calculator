CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -g -std=c++0x
PROGNAME=shatrale
SRC=./src/

all: $(PROGNAME)  doc

compile: $(PROGNAME) 

$(PROGNAME): $(SRC)main.o $(SRC)CStack.o $(SRC)CElement.o $(SRC)CNumber.o $(SRC)COperator.o $(SRC)CParenthesis.o $(SRC)CTester.o
	$(LD) -o ./$(PROGNAME) $^

CStack.o: $(SRC)CStack.cpp $(SRC)CStack.h $(SRC)CElement/CNumber.h $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h $(SRC)CElement/CParenthesis.h $(SRC)CElement/COperator.h
	$(CXX) $(CXXFLAGS) -c -o $(SRC)$@ $<

CTester.o: $(SRC)CTester.cpp $(SRC)CTester.h $(SRC)CElement/CNumber.h $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h $CStack.h
	$(CXX) $(CXXFLAGS) -c -o $(SRC)$@ $<

$(SRC)CElement.o: $(SRC)CElement/CElement.cpp $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRC)CNumber.o: $(SRC)CElement/CNumber.cpp $(SRC)CElement/CNumber.h $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

main.o: $(SRC)main.cpp $(SRC)CElement/CNumber.h $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h $(SRC)CStack.h $CTester.h
	$(CXX) $(CXXFLAGS) -c -o $(SRC)$@ $<

$(SRC)COperator.o: $(SRC)CElement/COperator.cpp $(SRC)CElement/COperator.h $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRC)CParenthesis.o: $(SRC)CElement/CParenthesis.cpp $(SRC)CElement/CParenthesis.h  $(SRC)CElement/CElement.h $(SRC)CElement/Etype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(PROGNAME) $(SRC)*.o  doc
	
run:
	./shatrale

doc:
	doxygen $(PROGNAME).doxygen
