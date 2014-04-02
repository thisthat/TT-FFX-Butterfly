CC = g++
CCFLAGS = -g -O3 -c
PARSER_DIR = ./Parser_XML/

all: compile clean


parser:  
	make -C $(PARSER_DIR)

compile: parser
	${CC} $(PARSER_DIR)Parser.o $(PARSER_DIR)Lexer.o Main.cpp -o Test

clean:
	

demo: compile
	./Test < Parser_XML/input_text.xml 
