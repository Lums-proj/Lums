/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    MacOSX/LMApplication.mm                        oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#import "LMApplication.hpp"

@implementation LMApplication

+(void)pumpEvents
{
    NSEvent* event = nil;

    while ((event = [NSApp nextEventMatchingMask:NSAnyEventMask
                     untilDate:[NSDate distantPast]
                     inMode:NSDefaultRunLoopMode
                     dequeue:YES]))
    {
        [NSApp sendEvent:event];
    }
}

@end