#include <cstdlib>  // per la macro EXIT_SUCCESS
#include <iostream> // per std::cout, std::cin e std::endl
#include <utility> //Pair 
#include <map>  //e map
#include <vector>
#include "./Parser_XML/Point.h"
#include "Automata.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

int yyparse (void);
void deallocate();
extern struct listPoint *headList;

#ifdef __cplusplus
}
#endif

int main()
{
  
  std::cout << "Avvio Parser" << std::endl;
 
  yyparse();
  /* DEBUG AREA */
  
  struct listPoint *h = headList;
  int i = 0;
  while(h != NULL){
    fprintf(stderr, "element %d - line:%d\n\tisButterfly: %d\n\tvalue: %d\n",++i,h->point->position.line,h->point->butterfly,h->point->arrow);
    h = h->next;
  }
  
  /* END DEBUG AREA */

  std::cout << "FINE PARSER" << std::endl;
  std::cout << "Inizio Deallocazione" << std::endl;
  deallocate();
  std::cout << "FINE Deallocazione" << std::endl;

  return EXIT_SUCCESS;
}