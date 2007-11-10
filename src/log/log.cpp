#include "log.h"
#include <iostream.h>
/*
void _init()
{
	printf("Inside _init()\n"); 
} 
void _fini()
{
	printf("Inside _fini()\n"); 
}
*/
namespace stk
{
	Log::Log(std::string name)
	{
		this->name = name;
	}
	
	Log::~Log()
	{
	}
	
	void Log::info(std::string msg)
	{
		std::cout << msg << std::endl;
	}
}
