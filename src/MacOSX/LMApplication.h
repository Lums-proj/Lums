#ifndef LUMS_LMAPPLICATION_H
#define LUMS_LMAPPLICATION_H

#import <Cocoa/Cocoa.h>

@interface LMApplication : NSApplication
+(void)pumpEvents;
@end

#endif