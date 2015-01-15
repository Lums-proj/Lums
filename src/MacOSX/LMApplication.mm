#import "LMApplication.h"

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