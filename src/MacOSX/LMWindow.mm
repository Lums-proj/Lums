#import <Lums/Event.h>
#import "LMWindow.h"

@implementation LMWindow

-(void)keyDown:(NSEvent*)event
{
    lm::Event e;

    e.type = lm::Event::Type::KeyDown;
    e.key = static_cast<lm::Key>([event keyCode]);
    [self window]->pushEvent(e);
}

-(void)keyUp:(NSEvent*)event
{
    lm::Event e;

    e.type = lm::Event::Type::KeyUp;
    e.key = static_cast<lm::Key>([event keyCode]);
    [self window]->pushEvent(e);
}

@synthesize window = _window;

@end