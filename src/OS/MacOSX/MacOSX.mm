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
static std::string  appsupport_path;

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

    const std::string&
    userDataPath()
    {
        if (!appsupport_path.empty())
            return appsupport_path;

        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
        NSString *applicationSupportDirectory = [paths firstObject];

        appsupport_path = [applicationSupportDirectory cStringUsingEncoding:NSASCIIStringEncoding];
        appsupport_path += "/";
        return appsupport_path;
    }
}