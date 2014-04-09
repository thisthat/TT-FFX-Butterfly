#include <cstdlib>  // per la macro EXIT_SUCCESS
#include <iostream> // per std::cout, std::cin e std::endl
#include <utility> //Pair 
#include <map>  //e map
#include <vector>
#include "./Parser_XML/Point.h"
#include "NodeHandler.cpp"

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