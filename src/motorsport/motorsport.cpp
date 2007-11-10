#include "motorsport.h"
//#include <log/log.h>
#include <boost/program_options.hpp>
#include <iostream>

using namespace boost;
using namespace std;
//using namespace stk;

Motorsport::Motorsport()
{
//	Log *l = new Log();
//	delete l;
}

int Motorsport::main(int argc, char*argv[])
{
	// Declare the supported options.
	program_options::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "produce help message")
	    ("compression", program_options::value<int>(), "set compression level")
	;

	program_options::variables_map vm;
	program_options::store(program_options::parse_command_line(argc, argv, desc), vm);
	program_options::notify(vm);    

	if (vm.count("help")) {
	    cout << desc << "\n";
	    return 1;
	}

	if (vm.count("compression")) {
	    cout << "Compression level was set to " 
	 << vm["compression"].as<int>() << ".\n";
	} else {
	    cout << "Compression level was not set.\n";
	}
	return 0;
}

Motorsport::~Motorsport()
{
}
