#ifndef LUMS_LMWINDOW_H
#define LUMS_LMWINDOW_H

#import <Cocoa/Cocoa.h>
#import <Lums/Window.h>

@interface LMWindow : NSWindow

@property lm::Window* window;

-(void)keyDown:(NSEvent*)event;
-(void)keyUp:(NSEvent*)event;

@end

#endif