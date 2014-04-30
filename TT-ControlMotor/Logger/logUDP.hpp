#ifndef   LOG_H
#define   LOG_H
#include "log.hpp"
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>
#include <mutex>
#include <chrono>
#include "../List.hpp"

using namespace std;

class LogUDP : public Log
{
public:
	LogUDP(string addr,int port);
	virtual void open();
	virtual void write(string msg);
	virtual void close();
	void join();
private:
	string _addr;
	int _port;
	int _sock;
	struct sockaddr_in Sender_addr;
	std::thread fThread;
	List *queue;
	void send_thread();
	mutex fMutex;
	bool running;


};