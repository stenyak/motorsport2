#ifndef LOG_H_
#define LOG_H_

#include <string>

namespace stk
{
	class Log
	{
	  public:
		Log(std::string name);
		virtual ~Log();
		void info(std::string name);
	  private:
		std::string name;
	};
}

#endif /*LOG_H_*/
