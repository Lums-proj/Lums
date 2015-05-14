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
#import <Lums/Application.hpp>
#import <LMApplication.hpp>

using namespace lm;

static NSAutoreleasePool* pool;

void
Application::init()
{
    pool = [NSAutoreleasePool new];
    [LMApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps:YES];
    [[LMApplication sharedApplication] finishLaunching];
}
