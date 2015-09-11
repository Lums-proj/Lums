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

#import <fstream>

static std::string appsupport_path;

namespace lm
{
    const std::string&
    resourcePath()
    {
        static std::string path = std::string([[[NSBundle mainBundle] resourcePath]
            cStringUsingEncoding:NSASCIIStringEncoding]) + '/';
        return path;
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

    int
    mkAppDataDir(const char * dirname)
    {
        NSFileManager *fileManager= [NSFileManager defaultManager];
        NSError *error = nil;
        NSString *directory = [NSString stringWithUTF8String:dirname];
        
        if(![fileManager createDirectoryAtPath:directory withIntermediateDirectories:YES attributes:nil error:&error])
        {
            // An error has occurred, do something to handle it
            NSLog(@"Failed to create directory \"%@\". Error: %@", directory, error);
            return -1;
        }
        return 0;
    }
}