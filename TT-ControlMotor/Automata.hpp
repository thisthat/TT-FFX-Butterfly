#include <cstdlib>  // per la macro EXIT_SUCCESS
#include <iostream> // per std::cout, std::cin e std::endl
#include <utility> //Pair 
#include <map>  //e map
#include <vector>

#define DEBUG 1 //Debuging

//MAPPING MOTOR IN VECTOR
#define DC 		0
#define STEPPER 1

//Enum of states
enum STATE { 
	NOPE 		= 0, 
	UP 	 		= 1, 
	DOWN 		= 2, 
	LEFT 		= 4, 
	RIGHT 		= 8, 
	UP_LEFT 	= 5, 
	UP_RIGHT 	= 9, 
	DOWN_LEFT 	= 6, 
	DOWN_RIGHT 	= 10
};
typedef std::map<enum STATE, std::vector<int> > Map;

class Automata {

	public:
        Automata();
        ~Automata();
 		std::vector<int> transition(STATE s);
 		void seeMap();
 		std::string convertArrow(int);
    private:
    	Map distance;
    	STATE state;
    	void initAutomata();
    	std::vector<int> calcDistance(STATE s1, STATE s2);
    	std::vector<int> createValue(int[]);

};