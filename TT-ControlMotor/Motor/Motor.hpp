#include <iostream> // per std::cout, std::cin e std::endl
class Motor
{
  public:
    virtual void stepForward() = 0;
    virtual void stepBackward() = 0;
};