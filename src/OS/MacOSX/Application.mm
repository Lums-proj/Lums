/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    MacOSX/Application.hpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#import <Cocoa/Cocoa.h>
#import <LumsInclude/Application.hpp>
#import "LMApplication.hpp"

using namespace lm;

static NSAutoreleasePool* pool;

void
Application::init()
{
    pool = [NSAutoreleasePool new];
    [LMApplication sharedApplication];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"ApplePersistenceIgnoreState"];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps:YES];
    [[LMApplication sharedApplication] finishLaunching];
}
