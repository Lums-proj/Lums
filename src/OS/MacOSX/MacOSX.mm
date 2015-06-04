/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    MacOSX/MacOSX.mm                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#import <Cocoa/Cocoa.h>
#import <LumsInclude/OperatingSystem.hpp>

static std::string  res_path;

namespace lm
{
    const std::string&
    resourcePath()
    {
        if (!res_path.empty())
            return res_path;
        res_path = [[[NSBundle mainBundle] resourcePath]
                    cStringUsingEncoding:NSASCIIStringEncoding];
        if (res_path.empty())
            res_path = ".";
        res_path += "/";
        return res_path;
    }
}