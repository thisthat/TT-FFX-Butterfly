#include "logFile.hpp"
using namespace std;

LogFile::LogFile(string name){
	_name = name;
	cout << "File name: " << _name << endl;
}

void LogFile::open(){
	log.open(_name); 
}
void LogFile::close(){
  	log.close();
}
void LogFile::write(string msg){
	log << formatMessage(msg);
	log << "\n";
	fprintf(stderr, "Message: %s\n", msg.c_str());
}