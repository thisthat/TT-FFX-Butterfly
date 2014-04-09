#include "MotorDC.hpp"

MotorDC::MotorDC(){
	std::cout << "Init MotorDC \n";
}
void MotorDC::stepForward()
{
	std::cout << "AVANTI_DC" << std::endl;
}
void MotorDC::stepBackward()
{
	std::cout << "INDIETRO_DC" << std::endl;
}