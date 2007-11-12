#include "tests.h"
#include "log.h"
#include <iostream>
using namespace stk;
using namespace std;

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
    log->log(Log::Trace, __FILE__, __LINE__, "test %i", 1337);
    string msg = log->trace("test of trace logs %i", 1203);
    delete log;
    cin.get();
}
