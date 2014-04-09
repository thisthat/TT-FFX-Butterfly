#ifndef   Motor_H
#define   Motor_H
#include "Motor.hpp"
#endif

class MotorStepper : public Motor
{
public:
	MotorStepper();
	virtual void stepForward();
	virtual void stepBackward();
};
