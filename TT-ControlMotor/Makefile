CC = g++
CCFLAGS = -g -O3 -c
PARSER_DIR = ./Parser_XML/
FLAG_C11 = -std=c++11 -stdlib=libc++
all: compile clean


parser:  
	make -C $(PARSER_DIR)

Automata.o: Automata.cpp Automata.hpp
	$(CC) $(FLAG_C11) -c Automata.cpp
NodeHandler.o: NodeHandler.cpp NodeHandler.hpp
	$(CC) $(FLAG_C11) -c NodeHandler.cpp

MotorDC.o: ./Motor/MotorDC.cpp ./Motor/MotorDC.hpp 
	$(CC) $(FLAG_C11) -c $<
MotorStepper.o: ./Motor/MotorStepper.cpp ./Motor/MotorStepper.hpp
	$(CC) $(FLAG_C11) -c $<

Main.o: Main.cpp Main.hpp NodeHandler.hpp NodeHandler.cpp
	$(CC) $(FLAG_C11) -c $<

Motor: MotorDC.o MotorStepper.o

compile: parser Automata.o Motor Main.o
	${CC} $(PARSER_DIR)Parser.o $(PARSER_DIR)Lexer.o Automata.o MotorDC.o MotorStepper.o Main.o -o Test $(FLAG_C11)

clean:
	
demo: compile
	./Test
