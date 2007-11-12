#ifndef MOTORSPORT_H_
#define MOTORSPORT_H_

#include <boost/shared_ptr.hpp>
using namespace boost;

class Motorsport; typedef shared_ptr<Motorsport> pMotorsport;
class Motorsport
{
  public:
    class Options
    {
      public:
        void setRun(bool run);
        bool getRun();
        Options();
        ~Options();
      private:
        bool run;   
    };
    typedef shared_ptr<Options> pOptions;
	int start();
    Motorsport(pOptions options);
	virtual ~Motorsport();
  private:
    pOptions options;
    Motorsport();
};

#endif /*MOTORSPORT_H_*/
