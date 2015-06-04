/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Test.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "NanoTest.hpp"
#include <Lums>

int main(int argc, char**argv)
{
    std::cout << "Lums version " << LUMS_VERSION << std::endl;
    return nanotest_main(argc, argv);
}
