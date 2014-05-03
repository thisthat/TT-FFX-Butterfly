CC = gcc
CCFLAGS = -g -O3 -c
FLEX = flex
BISON = bison

all: compile clean


Lexer.c: Lexer.l 
	${FLEX} -f -o$@ $<

Parser.c: Parser.y
	${BISON} -v -t --defines=Parser.h -rall $< -o $@

Lexer.o: Lexer.c 
	${CC} $(CCFLAGS) Lexer.c 

Parser.o:  Parser.c	
	${CC} $(CCFLAGS) Parser.c 

compile: Lexer.c Parser.c	
	 
clean:
	

demo: compile
	./Test < input_text.xml
