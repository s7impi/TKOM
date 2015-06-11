OBJECTS=Array.o BinaryExpression.o Choice.o Definition.o Field.o Number.o Reference.o String.o
LIBRARIES=ast.a
CXXFLAGS=-std=c++1y -Wall

.PHONY: all clean

all: $(OBJECTS) $(LIBRARIES)
clean:
	$(RM) ${OBJECTS} $(LIBRARIES)

ast.a: $(OBJECTS)
	$(AR) -rcs ast.a $(OBJECTS)