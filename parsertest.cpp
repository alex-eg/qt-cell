#include "Parser.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc<2) exit(1);
    std::string in = argv[1];
    Parser P;
    P.Parse(in);
    exit(0);
}
