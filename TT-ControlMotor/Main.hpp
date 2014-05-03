#include <cstdlib>  // per la macro EXIT_SUCCESS
#include <iostream> // per std::cout, std::cin e std::endl
#include <utility> //Pair 
#include <map>  //e map
#include <sys/stat.h> //File stat
#include <vector>
#include <cstring>
#include <wiringPi.h>
#include "./Parser_XML/Point.h"
#include "NodeHandler.cpp"
#include "./Logger/logFile.hpp"
#include "./Logger/logUDP.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
extern FILE * yyin;
int yyparse (void);
void deallocate();
extern struct listPoint *headList;
extern int n_point;

#ifdef __cplusplus
}
#endif