/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    MacOSX/LMWindow.hpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_LMWINDOW_H
#define LUMS_LMWINDOW_H

#import <Cocoa/Cocoa.h>
#import <IOKit/hid/IOHIDLib.h>
#import <Lums/Window.hpp>

@interface LMWindow : NSWindow

@property lm::Window* window;

@property IOHIDManagerRef hidManager;

-(void)keyDown:(NSEvent*)event;
-(void)keyUp:(NSEvent*)event;
-(void)mouseDown:(NSEvent*)event;
-(void)mouseUp:(NSEvent*)event;
-(void)rightMouseDown:(NSEvent*)event;
-(void)rightMouseUp:(NSEvent*)event;
-(void)mouseMoved:(NSEvent*)event;
-(void)setupHid;

@end

#endif