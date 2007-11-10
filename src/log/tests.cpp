#include "tests.h"
#include "log.h"
using namespace stk;

int main (int argc, char *argv[])
{
	Tests*tests = new Tests();
	tests->testAll();
	delete tests;
	
	return 0;
}

Tests::Tests()
{
}

Tests::~Tests()
{
}

void Tests::testAll()
{
	Log *log = new Log("test log");
	log->info("prueba");
	delete log;
}
