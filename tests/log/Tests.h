#ifndef TESTS_H_
#define TESTS_H_


/** Entry point.
@param argc Number of args. Not used.
@param argv Parameters strings. Not used.
@returns 0 */
int main (int argc, char *argv[]);

/** Log unit testing class */
class Tests
{
  public:
    /** Constructor */
    Tests();
    /** Destructor */
    virtual ~Tests();
    /** Launches all tests, then waits for the user to press enter.*/
    void testAll();
};

#endif /*TESTS_H_*/
