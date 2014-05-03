#include "Automata.hpp"

Automata::Automata(Log *l){
    if(DEBUG){
        std::cout << "\tDebug: Starting automata...\n";
    }
    this->logger = l;
    this->state = NOPE;
    initAutomata();
}

Automata::~Automata(){
    if(DEBUG){
        std::cout << "\tDebug: Stopping automata...\n";
    }
}

std::vector<int> Automata::transition(STATE const s){
    std::vector<int> out = calcDistance(this->state,s);
    this->state = s;
    return out;
}

std::vector<int> Automata::calcDistance(STATE s1, STATE s2){
    if(DEBUG){
        char buffer[300];
        sprintf(buffer,"\tDebug: Transition S1 = %s -> S2 = %s",convertArrow(s1).c_str(),convertArrow(s2).c_str() );
        logger->write(buffer);
    }
    std::vector<int> v1 = distance[s1];
    std::vector<int> v2 = distance[s2];
    std::vector<int> r ({
                v2[DC] - v1[DC], 
                v2[STEPPER] - v1[STEPPER]
            });
    return r;
    
}

//Initializating the value of the motor
void Automata::initAutomata(){
    if(DEBUG){
        std::cout << "\tDebug: Initializating automata...\n";
    }
                                      //  DC      STEPPER
    std::vector<int> none           ({   0      ,   0    });
    std::vector<int> up             ({   0      ,  20    });
    std::vector<int> down           ({   0      , -20    });
    std::vector<int> left           ({ -20      ,   0    });
    std::vector<int> right          ({  20      ,   0    });
    std::vector<int> up_left        ({ -10      ,  10    });
    std::vector<int> up_right       ({  10      ,  10    });
    std::vector<int> down_left      ({ -10      , -10    });
    std::vector<int> down_right     ({  10      , -10    });

    distance[NOPE]          = none;
    distance[UP]            = up;
    distance[DOWN]          = down;
    distance[LEFT]          = left;
    distance[RIGHT]         = right;
    distance[UP_LEFT]       = up_left;
    distance[UP_RIGHT]      = up_right;
    distance[DOWN_LEFT]     = down_left;
    distance[DOWN_RIGHT]    = down_right;
    if(DEBUG){
        std::cout << "\tDebug: See stepper...\n";
        seeMap();
    }
}

//Debug purpose
void Automata::seeMap(){
    std::cout << "\tMap\n";
    std::cout << "\t\tValue " << convertArrow(NOPE)       << " : \t" << distance[NOPE][DC]          << ";\t" << distance[NOPE][STEPPER]       << std::endl;
    std::cout << "\t\tValue " << convertArrow(UP)         << " : \t" << distance[UP][DC]            << ";\t" << distance[UP][STEPPER]         << std::endl;
    std::cout << "\t\tValue " << convertArrow(DOWN)       << " : \t" << distance[DOWN][DC]          << ";\t" << distance[DOWN][STEPPER]       << std::endl;
    std::cout << "\t\tValue " << convertArrow(LEFT)       << " : \t" << distance[LEFT][DC]          << ";\t" << distance[LEFT][STEPPER]       << std::endl;
    std::cout << "\t\tValue " << convertArrow(RIGHT)      << " : \t" << distance[RIGHT][DC]         << ";\t" << distance[RIGHT][STEPPER]      << std::endl;
    std::cout << "\t\tValue " << convertArrow(UP_LEFT)    << " : \t" << distance[UP_LEFT][DC]       << ";\t" << distance[UP_LEFT][STEPPER]    << std::endl;
    std::cout << "\t\tValue " << convertArrow(UP_RIGHT)   << " : \t" << distance[UP_RIGHT][DC]      << ";\t" << distance[UP_RIGHT][STEPPER]   << std::endl;
    std::cout << "\t\tValue " << convertArrow(DOWN_LEFT)  << " : \t" << distance[DOWN_LEFT][DC]     << ";\t" << distance[DOWN_LEFT][STEPPER]  << std::endl;
    std::cout << "\t\tValue " << convertArrow(DOWN_RIGHT) << " : \t" << distance[DOWN_RIGHT][DC]    << ";\t" << distance[DOWN_RIGHT][STEPPER] << std::endl;
}
//Better see a string instead of a number :p
std::string Automata::convertArrow(int a){
    if(! (a ^ UP)){
        return "UP";
    }
    if(! (a ^ DOWN)){
        return "DOWN";
    }
    if(! (a ^ LEFT)){
        return "LEFT";
    }
    if(! (a ^ RIGHT)){
        return "RIGHT";
    }
    if(! (a ^ UP_LEFT)){
        return "UP_LEFT";
    }
    if(! (a ^ UP_RIGHT)){
        return "UP_RIGHT";
    }
    if(! (a ^ DOWN_LEFT)){
        return "DOWN_LEFT";
    }
    if(! (a ^ DOWN_RIGHT)){
        return "DOWN_RIGHT";
    }
    return "NOPE";
}
