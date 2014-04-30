#include "logUDP.hpp"

#define TIMER 300

#define DEBUG 1

LogUDP::LogUDP(string addr,int port){
	_addr = addr;
	_port = port;
	cout << "Log Address: " << addr << ":" << port << endl;
	queue = new List();
}

void LogUDP::open(){
	//Open the socket
	_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (_sock < 0)
	{
	    perror("Socket creation error");
	    return;
	}
	int enabled = 1;
	//Set broadcast enabled
	if (setsockopt(_sock, SOL_SOCKET, SO_BROADCAST, &enabled, sizeof(enabled)) < 0)
	{
	    perror("Broadcast options error");
	    shutdown(_sock, 2);
	    return;
	}
	//Bind structure to broadcast ip	
	Sender_addr.sin_family = AF_INET;
	Sender_addr.sin_port = htons(_port);
	struct hostent *hostPointer;
	hostPointer=gethostbyname(_addr.c_str());
    memcpy((unsigned char * ) &Sender_addr.sin_addr, (unsigned char *) hostPointer -> h_addr, hostPointer -> h_length);
    running = true;
    fThread = std::thread(&LogUDP::send_thread, this);
}

void LogUDP::send_thread(){
	int message;
	string msg;
	std::chrono::milliseconds dura( TIMER );
	while(running){
		std::this_thread::sleep_for(dura);
		//Enter critical section
		fMutex.lock();
		//Get message
		if(!queue->isEmpty()){
			msg = queue->take();
			fprintf(stderr, "\033[255;0;31mMessage: %s\033[0m\n\n", msg.c_str());
			message = sendto(_sock, msg.c_str(), msg.size()+1, 0, (struct sockaddr *) &Sender_addr, sizeof(Sender_addr));
			if (message == -1){
	    		perror("Sending message failed");
	   		}
		}
	    fMutex.unlock();
	}
	while(!queue->isEmpty()){
		msg = queue->take();
		fprintf(stderr, "\033[255;0;31mMessage: %s\033[0m\n\n", msg.c_str());
		message = sendto(_sock, msg.c_str(), msg.size()+1, 0, (struct sockaddr *) &Sender_addr, sizeof(Sender_addr));
		if (message == -1){
    		perror("Sending message failed");
   		}
   		std::this_thread::sleep_for(dura);
	}
	//std::terminate();
}

void LogUDP::close(){
	running = false;
	fprintf(stderr, "\033[1;;32mSending last messages....\033[0m\n\n");
	fThread.join();
  	shutdown(_sock,2);
}
void LogUDP::write(string msg){
	msg = formatMessage(msg);
	fMutex.lock();
	queue->add(msg);
	fMutex.unlock();
}
