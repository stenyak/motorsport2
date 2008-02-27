#include "Tests.h"
#include "Log.h"
#include <testsoon.hpp>
#include <iostream>
using namespace stk;
using namespace std;

TEST(compiler_check) {
    Equals(1, 1);
}
TEST(log_logCheck)
{
    Log *log = new Log("id");
    Equals("d : (id):0: ", log->log(Log::Dev, "", 0, ""));
    Equals("t : (id):0: ", log->log(Log::Trace, "", 0, ""));
    Equals("d : (id):0: ", log->log(Log::Dev, "", 0, ""));
    Equals("CC: (id):0: ", log->log(Log::Cont, "", 0, ""));
    Equals("II: (id):0: ", log->log(Log::User, "", 0, ""));
    Equals("WW: (id):0: ", log->log(Log::Warn, "", 0, ""));
    Equals("EE: (id):0: ", log->log(Log::Error, "", 0, ""));
    delete log;
}
TEST(log_macroCheck)
{
    Log *log = new Log("id");
    Equals("t : tests.cpp(id):26: ", log->trace(""));
    Equals("d : tests.cpp(id):27: ", log->dev(""));
    Equals("CC: tests.cpp(id):28: ", log->cont(""));
    Equals("II: tests.cpp(id):29: ", log->user(""));
    Equals("WW: tests.cpp(id):30: ", log->warn(""));
    Equals("EE: tests.cpp(id):31: ", log->error(""));
    delete log;
}
TEST(log_genericCheck)
{
    Log *log = new Log("id");
    Equals("t : main.cpp(id):15: message 5", log->log(Log::Trace, "main.cpp", 15, "message %i", 5));
    Equals("d : main.cpp(id):15: message 5", log->log(Log::Dev, "main.cpp", 15, "message %i", 5));
    delete log;
}
TEST_REGISTRY
int main (int argc, char *argv[])
{
    Tests*tests = new Tests();
    delete tests;
    return 0;
}
Tests::Tests()
{
    testsoon::default_reporter rep(std::cout);
    testsoon::tests().run(rep);
    cin.get();
}
Tests::~Tests()
{
}
