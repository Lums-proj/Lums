/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    MacOSX/LMApplication.hpp                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_LMAPPLICATION_HPP
#define LUMS_LMAPPLICATION_HPP

#import <Cocoa/Cocoa.h>

@interface LMApplication : NSApplication
+(void)pumpEvents;
@end

#endif