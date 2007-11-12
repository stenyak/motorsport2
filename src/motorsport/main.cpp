#include "main.h"
#include "motorsport.h"
#include <boost/program_options.hpp>
#include <iostream>
using namespace boost;
using namespace std;

int main(int argc, char*argv[])
{
    int result = 0;
    program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("run", "run motorsport simulation");
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
            cout<< "Running Motorsport simulation."<< endl;
            Motorsport::pOptions opt(new Motorsport::Options);
            opt->setRun(true);
            pMotorsport mosp ( new Motorsport(opt) );
            mosp->start();
            //result = mosp->main(argc, argv);
        }
        else
        {
            cout<< "No option was chosen."<< endl;
            result = 1;
        }
    }
    cin.get();
    return result;
}
