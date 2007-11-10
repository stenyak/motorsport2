#include "log.h"

#include <stdio.h>

void _init()
{
	printf("Inside _init()\n"); 
} 
void _fini()
{
	printf("Inside _fini()\n"); 
}
namespace stk
{
	Log::Log()
	{
		int test = 0;
		test += 2;
	}
	
	Log::~Log()
	{
	}
}
