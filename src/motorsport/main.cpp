#include "main.h"
#include "motorsport.h"
#include <boost/shared_ptr.hpp>
using namespace boost;

int main(int argc, char*argv[])
{
	shared_ptr<Motorsport> mosp ( new Motorsport() );
	mosp->main(argc, argv);
}
