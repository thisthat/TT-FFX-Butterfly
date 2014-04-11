#include "NodeHandler.hpp"
//Sleep thread
#include <chrono>
#include <thread>
//Timer
#include <ctime>

#define DEBUG 1 //Debuging

#define TIMER 1000 //MS before read next node

NodeHandler::NodeHandler(struct listPoint *h){
	head = h;
	std::cout << "Node Handler Started..\n";
	if(DEBUG){
		std::cout << "\tDebug: see xml list" << std::endl;;
		printList();
	}
}

void NodeHandler::printList(){
	listPoint *h = head;
    int i = 0;
    while(h != NULL){
	    fprintf(stderr, "\telement %d - line:%d\n\t\tisButterfly: %d\n\t\tvalue: %d\n",++i,h->point->position.line,h->point->butterfly,h->point->arrow);
	    h = h->next;
    }
}

void NodeHandler::start(){
	listPoint *h = head;
	std::vector<int> out;
	std::chrono::time_point<std::chrono::system_clock> now;
	std::chrono::time_point<std::chrono::system_clock> now2;
	int t;
	while(h != NULL){
		if(DEBUG){
			std::cout << "\tPoint @" << h->point->position.line;
			if(h->point->butterfly){
				std::cout << " -- BUTTERFLY FOUND";
			}
			std::cout << std::endl;
		}
		out = atmt.transition((STATE)h->point->arrow);
		if(DEBUG){
			std::cout << "\t\tStep DC: " << out[0] << "\n\t\tStep Stepper: " << out[1] << std::endl;
		}
		//Sync between motor and wait
		now = std::chrono::system_clock::now();
		handleMotor(out);
		now2 = std::chrono::system_clock::now();
		t = TIMER - std::chrono::duration_cast<std::chrono::milliseconds>(now2 - now).count();
		if(DEBUG){
			std::cout << "\t\tWait " << t << " ms" << std::endl;
		}
		h = h->next;
    	std::this_thread::sleep_for(std::chrono::milliseconds(t));
    	
    }
}

void NodeHandler::handleMotor(std::vector<int> out){
	int stepDC, stepStepper;
	stepDC = abs(out[DC]);
	stepStepper = abs(out[STEPPER]);
	bool sng_dc = (out[DC] > 0) ? true : false;
	bool sng_step = (out[STEPPER] > 0) ? true : false;
	//Scheduling one step from both until reach the position
	while(stepDC > 0 || stepStepper > 0){
		//DC
		if(0 < stepDC--) (sng_dc) ? dcMotor.stepForward() : dcMotor.stepBackward();
		//Stepper
		if(0 < stepStepper--) (sng_step) ? stepperMotor.stepForward() : stepperMotor.stepBackward();
	}
}