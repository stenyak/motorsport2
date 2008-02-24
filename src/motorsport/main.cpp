#include <iostream>
#include <boost/program_options.hpp>
#include "main.h"
#include "Motorsport.h"
#include <Log.h>
using namespace boost;
using namespace std;
using namespace stk;

int main(int argc, char*argv[])
{
    pLog log(new Log("Motorsport Wrapper"));
    int result = 0;
    program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message.")
        ("run", "run Motorsport Simulation.");
    program_options::variables_map vm;
    program_options::store(program_options::parse_command_line(argc, argv, desc), vm);
    program_options::notify(vm);    
    if (vm.count("help"))
    {
        cout<< desc<< endl;
        result = 2;
    }
    else
    {
        if (vm.count("run"))
        {
            log->user("Running Motorsport simulation.");
            pMotorsportConfig config(new MotorsportConfig());
            config->setRun(true);
            pMotorsport motorsport ( new Motorsport(config) );
            result = motorsport->start();
        }
        else
        {
            log->warn("No option was chosen.");
            result = 1;
        }
    }
    return result;
}
