#include "./Motor/MotorDC.hpp"
#include "./Motor/MotorStepper.hpp"
#include "Automata.hpp"
#ifndef   LOG_H
#define   LOG_H
#include "./Logger/log.hpp"
#endif


class NodeHandler {
	public:
		NodeHandler(struct listPoint *h,Log *l);
		void printList(); //Debug Purpose
		void start();

	private:
		struct listPoint *head;
		MotorDC dcMotor;
		MotorStepper stepperMotor;
		Automata *atmt;
		Log *logger;
		void handleMotor(std::vector<int>);
};