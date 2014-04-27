#ifndef   LOG_H
#define   LOG_H
#include "log.hpp"
#endif
#include <fstream>

using namespace std;

class LogFile : public Log
{
public:
	LogFile(string name);
	virtual void open();
	virtual void write(string msg);
	virtual void close();
private:
	string _name;
	ofstream log;
};