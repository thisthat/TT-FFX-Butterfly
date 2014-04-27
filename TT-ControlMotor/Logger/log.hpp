#include <iostream> // per std::cout, std::cin e std::endl
#include <string>
#include <ctime>
#include <sys/time.h>

class Log
{
  public:
    virtual void open() = 0;
    virtual void write(std::string msg) = 0;
    virtual void close() = 0;

   protected:
   	std::string formatMessage(std::string message){
   		char buffer[300];
   		time_t now = time(0);
   		tm *ltm = localtime(&now);
   		timeval curTime;
		gettimeofday(&curTime, NULL);
		int milli = curTime.tv_usec / 1000;
   		sprintf(buffer,"%d/%d/%d %d:%d:%d:%d\t :: %s\n",ltm->tm_mday,1 + ltm->tm_mon,1900 + ltm->tm_year,1 + ltm->tm_hour,1 + ltm->tm_min,1 + ltm->tm_sec, milli, message.c_str());
   		std::string r = buffer;
   		return r;
   	}
};