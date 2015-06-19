#include <iostream>
#include <Lums>

int
main(int argc, char** argv)
{
    if (argc != 2)
        std::cerr << "LOLOLOLO" << std::endl;
    else
    {
        lm::BFile   file;
        file.open(argv[1], false);
    }
}