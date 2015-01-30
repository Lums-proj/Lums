/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Windows/Windows.cpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <windows.h>
#include <Lums/OperatingSystem.hpp>

static std::string  res_path;

namespace lm
{
    const std::string&
    resourcePath()
    {
        if (res_path.empty())
        {
            res_path = ".";
        }
        return res_path;
    }
}

extern "C" int main(int, char**);

int WINAPI
WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lp, int n)
{
    char* argv[] = {"", 0};
    
    return 0;//main(1, argv);
}
