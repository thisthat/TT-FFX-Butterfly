#include "logTcp.hpp"
using namespace std;

#define BROADCAST_PORT 1515

LogTcp::LogTcp(string name){
	_addr = name;
	cout << "Log Address: " << _addr << endl;
}

void LogTcp::open(){
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
	Sender_addr.sin_port = htons(BROADCAST_PORT);
	struct hostent *hostPointer;
	hostPointer=gethostbyname(_addr.c_str());
    memcpy((unsigned char * ) &Sender_addr.sin_addr, (unsigned char *) hostPointer -> h_addr, hostPointer -> h_length);
   
}
void LogTcp::close(){
  	 shutdown(_sock,2);
}
void LogTcp::write(string msg){
	msg = formatMessage(msg);
	int message = sendto(_sock, msg.c_str(), msg.size()+1, 0, (struct sockaddr *) &Sender_addr, sizeof(Sender_addr));
   	if (message == -1){
    	perror("Sending message failed");
   	}
}
