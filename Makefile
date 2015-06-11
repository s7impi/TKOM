SUBDIRS = ast parser
PROGRAMS=main
CXXFLAGS=-I. -std=c++1y

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS) $(PROGRAMS)

main: main.cpp parser/parser.a ast/ast.a
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MAKECMDGOALS): $(SUBDIRS)

$(SUBDIRS):
	 $(MAKE) -C $@ $(MAKECMDGOALS)