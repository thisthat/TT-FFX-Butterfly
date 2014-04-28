#include "logUDP.hpp"

#define BROADCAST_PORT 15150

LogUDP::LogUDP(string addr,int port){
	_addr = addr;
	_port = port;
	cout << "Log Address: " << addr << ":" << port << endl;
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
   
}
void LogUDP::close(){
  	 shutdown(_sock,2);
}
void LogUDP::write(string msg){
	msg = formatMessage(msg);
	int message = sendto(_sock, msg.c_str(), msg.size()+1, 0, (struct sockaddr *) &Sender_addr, sizeof(Sender_addr));
	fprintf(stderr, "Message: %s\n", msg.c_str());
   	if (message == -1){
    	perror("Sending message failed");
   	}
}
