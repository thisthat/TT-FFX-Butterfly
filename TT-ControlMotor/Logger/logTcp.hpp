#ifndef   LOG_H
#define   LOG_H
#include "log.hpp"
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

class LogTcp : public Log
{
public:
	LogTcp(string addr);
	virtual void open();
	virtual void write(string msg);
	virtual void close();
private:
	string _addr;
	int _sock;
	struct sockaddr_in Sender_addr;
};