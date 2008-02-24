#include <Core.h>
#include <Group.h>
using namespace motorsport;

int main(int argc, char**argv)
{
    shared_ptr<Group> world(new Group("world"));
    shared_ptr<Core> core(new Core(world));
    return 0;
}
