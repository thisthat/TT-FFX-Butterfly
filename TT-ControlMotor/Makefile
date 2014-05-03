PROJECT = OSX

ifeq ($(PROJECT), RPI)
	CC = g++-4.7
	FLAG_C11 = -std=c++0x
else
	FLAG_C11 = -std=c++11 -stdlib=libc++
	CC = g++
endif
CCFLAGS = -g -O3 -c
PARSER_DIR = ./Parser_XML/

NAME = TT-FFX-Butterfly
all: compile clean


parser:  
	make -C $(PARSER_DIR)

List.o: List.cpp List.hpp
	$(CC) $(FLAG_C11) -c $<

Automata.o: Automata.cpp Automata.hpp
	$(CC) $(FLAG_C11) -c Automata.cpp
NodeHandler.o: NodeHandler.cpp NodeHandler.hpp
	$(CC) $(FLAG_C11) -c NodeHandler.cpp

logFile.o: ./Logger/logFile.cpp ./Logger/logFile.hpp ./Logger/log.hpp
	$(CC) $(FLAG_C11) -c $<
logUDP.o: ./Logger/logUDP.cpp ./Logger/logUDP.hpp ./Logger/log.hpp
	$(CC) $(FLAG_C11) -c $<

MotorDC.o: ./Motor/MotorDC.cpp ./Motor/MotorDC.hpp 
	$(CC) $(FLAG_C11) -c $<
MotorStepper.o: ./Motor/MotorStepper.cpp ./Motor/MotorStepper.hpp
	$(CC) $(FLAG_C11) -c $<

Main.o: Main.cpp Main.hpp NodeHandler.hpp NodeHandler.cpp
	$(CC) $(FLAG_C11) -c $<

Motor: MotorDC.o MotorStepper.o

Log: logFile.o logUDP.o 

compile: parser Automata.o Motor Log Main.o List.o
	$(CC) $(PARSER_DIR)Parser.o $(PARSER_DIR)Lexer.o Automata.o MotorDC.o MotorStepper.o logFile.o logUDP.o List.o Main.o -o $(NAME) $(FLAG_C11)

clean:
	
demo: compile
	./$(NAME) $(PARSER_DIR)input_text.xml -lUDP 192.168.0.255 -port 15150
