/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Test.cpp                                     &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <NanoTest.h>
#include <Lums/Lums.h>

int main(int argc, char**argv)
{
    std::cout << "Lums version " << LUMS_VERSION << std::endl;
    return nanotest_main(argc, argv);
}