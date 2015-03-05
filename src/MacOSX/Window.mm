/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    MacOSX/Window.mm                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <Lums/Window.hpp>
#import "LMApplication.hpp"
#import "LMWindow.hpp"

using namespace lm;

static NSAutoreleasePool* pool;

static NSOpenGLPixelFormatAttribute
glAttributes[] = {
    NSOpenGLPFADepthSize, 24,
    NSOpenGLPFAStencilSize, 8,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAClosestPolicy,
    0
};

Window::Window(int w, int h, const char* name)
{
    static bool appLaunched = false;

    if (!appLaunched)
    {
        pool = [NSAutoreleasePool new];
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
    _windowHandle = win;
    _openGlHandle = context;
    [win makeKeyAndOrderFront:nil];
    [win setWindow:this];
    [win setupHid];
}

void
Window::pumpEvent()
{
	[LMApplication pumpEvents];
}

void
Window::swap()
{
    NSOpenGLContext* context = static_cast<NSOpenGLContext*>(_openGlHandle);

    [context flushBuffer];
}

Window::~Window()
{

}