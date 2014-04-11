#include "./Motor/MotorDC.hpp"
#include "./Motor/MotorStepper.hpp"
#include "Automata.hpp"

class NodeHandler {
	public:
		NodeHandler(struct listPoint *h);
		void printList();
		void start();

	private:
		struct listPoint *head;
		MotorDC dcMotor;
		MotorStepper stepperMotor;
		Automata atmt;
		void handleMotor(std::vector<int>);
};