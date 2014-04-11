#include "Automata.hpp"

Automata::Automata(){
    if(DEBUG){
        std::cout << "\tDebug: Starting automata...\n";
    }
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
    std::cout << "\tDebug: Transition S1 = " << convertArrow(s1) << " -> S2 = " << convertArrow(s2) << "\n";
    std::vector<int> v1 = distance[s1];
    std::vector<int> v2 = distance[s2];
    return createValue(
            new int[2]{
                v2[DC] - v1[DC], 
                v2[STEPPER] - v1[STEPPER]
            });
}

void Automata::initAutomata(){
    if(DEBUG){
        std::cout << "\tDebug: Initializating automata...\n";
    }
                                                    //  DC      STEPPER
    distance[NOPE]          = createValue(new int[2]{   0      ,   0    });
    distance[UP]            = createValue(new int[2]{   0      ,  20    });
    distance[DOWN]          = createValue(new int[2]{   0      , -20    });
    distance[LEFT]          = createValue(new int[2]{ -20      ,   0    });
    distance[RIGHT]         = createValue(new int[2]{  20      ,   0    });
    distance[UP_LEFT]       = createValue(new int[2]{ -10      ,  10    });
    distance[UP_RIGHT]      = createValue(new int[2]{  10      ,  10    });
    distance[DOWN_LEFT]     = createValue(new int[2]{ -10      , -10    });
    distance[DOWN_RIGHT]    = createValue(new int[2]{  10      , -10    });
    if(DEBUG){
        std::cout << "\tDebug: See stepper...\n";
        seeMap();
    }
}

void Automata::seeMap(){
    std::cout << "\tMap\n";
    std::cout << "\t\tValue " << NOPE       << " : " << distance[NOPE][DC]          << ";" << distance[NOPE][STEPPER]       << std::endl;
    std::cout << "\t\tValue " << UP         << " : " << distance[UP][DC]            << ";" << distance[UP][STEPPER]         << std::endl;
    std::cout << "\t\tValue " << DOWN       << " : " << distance[DOWN][DC]          << ";" << distance[DOWN][STEPPER]       << std::endl;
    std::cout << "\t\tValue " << LEFT       << " : " << distance[LEFT][DC]          << ";" << distance[LEFT][STEPPER]       << std::endl;
    std::cout << "\t\tValue " << RIGHT      << " : " << distance[RIGHT][DC]         << ";" << distance[RIGHT][STEPPER]      << std::endl;
    std::cout << "\t\tValue " << UP_LEFT    << " : " << distance[UP_LEFT][DC]       << ";" << distance[UP_LEFT][STEPPER]    << std::endl;
    std::cout << "\t\tValue " << UP_RIGHT   << " : " << distance[UP_RIGHT][DC]      << ";" << distance[UP_RIGHT][STEPPER]   << std::endl;
    std::cout << "\t\tValue " << DOWN_LEFT  << " : " << distance[DOWN_LEFT][DC]     << ";" << distance[DOWN_LEFT][STEPPER]  << std::endl;
    std::cout << "\t\tValue " << DOWN_RIGHT << " : " << distance[DOWN_RIGHT][DC]    << ";" << distance[DOWN_RIGHT][STEPPER] << std::endl;
}
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

std::vector<int>  Automata::createValue(int *arrayValue){
    std::vector<int> vect (arrayValue, arrayValue + sizeof(arrayValue) / sizeof(int) );
    return vect;
}