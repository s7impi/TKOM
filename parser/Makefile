OBJECTS=parser.tab.o lexer.o
LIBRARIES=parser.a
GENERATED=parser.tab.cc parser.tab.hh lexer.cc location.hh position.hh stack.hh
CXXFLAGS=-I../ -std=c++1y -Wall
BISON=bison
SED=sed
FLEX=flex

.PHONY: all clean

all: $(OBJECTS) $(LIBRARIES)
clean:
	$(RM) ${GENERATED} ${OBJECTS} $(LIBRARIES)

parser.tab.o: parser.tab.cc
lexer.o: lexer.cc
parser.tab.cc: parser.yy
	$(BISON) parser.yy
	$(SED) -i -e 's/vector/deque/' stack.hh
lexer.cc: parser.tab.cc lexer.l
	$(FLEX) -o lexer.cc lexer.l

parser.a: $(OBJECTS)
	$(AR) -rcs parser.a $(OBJECTS)