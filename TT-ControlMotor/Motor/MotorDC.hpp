#ifndef   Motor_H
#define   Motor_H
#include "Motor.hpp"
#endif


class MotorDC : public Motor
{
public:
	MotorDC();
	virtual void stepForward();
	virtual void stepBackward();
};
