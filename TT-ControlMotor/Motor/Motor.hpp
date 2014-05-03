#include <iostream> // per std::cout, std::cin e std::endl
#include <wiringPi.h>
class Motor
{
  public:
    virtual void stepForward() = 0;
    virtual void stepBackward() = 0;
};