#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <Lums/Window.h>
#import "LMApplication.h"
#import "LMWindow.h"

using namespace lm;

static NSOpenGLPixelFormatAttribute
glAttributes[] = {
    NSOpenGLPFADepthSize, 32,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFADoubleBuffer,
    0
};

Window::Window(int w, int h, const char* name)
{
    static bool appLaunched = false;

    if (!appLaunched)
    {
        [NSAutoreleasePool new];
        [LMApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];
        [[LMApplication sharedApplication] finishLaunching];
        appLaunched = true;
    }
    NSRect frame = NSMakeRect(0, 0, w, h);
    LMWindow* win = [[[LMWindow alloc] initWithContentRect:frame
                    styleMask:NSTitledWindowMask
                    backing:NSBackingStoreBuffered
                    defer:NO] autorelease];
    [win setTitle:[NSString stringWithCString:name encoding:NSASCIIStringEncoding]];
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc]
                                        initWithAttributes:glAttributes];
    NSOpenGLContext* context = [[[NSOpenGLContext alloc]
                                initWithFormat:pixelFormat
                                shareContext:nil] autorelease];
    [context setView:[win contentView]];
    [context makeCurrentContext];
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    [context flushBuffer];
    _windowHandle = win;
    _openGlHandle = context;
    [win makeKeyAndOrderFront:nil];
    [win setWindow:this];
}

void
Window::PushEvent(Event& event)
{
    _events.push(event);
}

void
Window::PollEvent(Event& event)
{
    ExtractEvent(event, false);
}

void
Window::WaitEvent(Event& event)
{
    ExtractEvent(event, true);
}

void
Window::PumpEvent()
{
    [LMApplication pumpEvents];
}

void
Window::Swap()
{
    NSOpenGLContext* context = static_cast<NSOpenGLContext*>(_openGlHandle);

    [context flushBuffer];
}

Window::~Window()
{

}

void
Window::ExtractEvent(Event& event, bool block)
{
    while (true)
    {
        PumpEvent();
        if (!_events.empty())
        {
            event = _events.front();
            _events.pop();
            return;
        }
        else if (!block)
        {
            event.type = Event::Type::None;
            return;
        }
    }
}