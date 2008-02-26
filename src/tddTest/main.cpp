#include <string.h>
#include <unittest++/UnitTest++.h>

int sum(int v1, int v2)
{
    return v1 + v2;
}
int absolute(float v1)
{
    int v = (int)v1;
    if (v<0)
        v--;
    return v;
}
int absolute(double v1)
{
    int v = (int)v1;
    if (v<0) v--;
    return v;
}
int max(int v1, int v2)
{
    if (v1 > v2)
        return v1;
    else if (v2 > v1)
        return v2;
    else return 0;
}
unsigned int nat(int v1)
{
    if (v1 <= 0) throw std::string("Can't convert to natural.");
    return v1;
}

TEST(nat)
{
    CHECK_EQUAL(nat(2), 2);
    CHECK_EQUAL(nat(1), 1);
    CHECK_THROW(nat(-1), std::string);
    CHECK_THROW(nat(0), std::string);

    CHECK_EQUAL(absolute(0.0), 0);
    CHECK_EQUAL(absolute(-5.5), -6);
}
TEST(absolute)
{
    CHECK_EQUAL(absolute(1.3), 1);
    CHECK_EQUAL(absolute(0.0), 0);
    CHECK_EQUAL(absolute(-5.5), -6);
    CHECK_EQUAL(absolute(1.3f), 1);
    CHECK_EQUAL(absolute(-0.1f), -1);
}
TEST(sum)
{
    CHECK_EQUAL(sum(1,3), 4);
    CHECK_EQUAL(sum(0,0), 0);
    CHECK_EQUAL(sum(-5,5), 0);
}
TEST(max)
{
    CHECK_EQUAL(max(1,3), 3);
    CHECK_EQUAL(max(5,3), 5);
    CHECK_EQUAL(max(-5,3), 3);
    CHECK_EQUAL(max(0,0), 0);
}
int main (int argc, char*argv[])
{
    return UnitTest::RunAllTests();
}
