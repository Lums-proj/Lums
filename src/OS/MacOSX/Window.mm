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
#import <OpenGL/gl3.h>
#import <LumsInclude/Graphics/Window.hpp>
#import "LMApplication.hpp"
#import "LMWindow.hpp"

using namespace lm;

static NSOpenGLPixelFormatAttribute
glAttributes[] = {
    NSOpenGLPFADepthSize, 24,
    NSOpenGLPFAStencilSize, 8,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAClosestPolicy,
    kCGLPFAOpenGLProfile,
    kCGLOGLPVersion_3_2_Core,
    0
};

Window::Window(int w, int h, const char* name, bool fullscreen)
: _fullscreen(false)
{
    NSRect frame = NSMakeRect(0, 0, w, h);
    LMWindow* win = [[[LMWindow alloc] initWithContentRect:frame
                    styleMask:NSTitledWindowMask
                    backing:NSBackingStoreBuffered
                    defer:NO] autorelease];
    [win setTitle:[NSString stringWithCString:name encoding:NSASCIIStringEncoding]];
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc]
                                        initWithAttributes:glAttributes];
    NSOpenGLView* view = [[NSOpenGLView alloc] initWithFrame:frame pixelFormat:pixelFormat];
    NSOpenGLContext* context = [[[NSOpenGLContext alloc]
                                initWithFormat:pixelFormat
                                shareContext:nil] autorelease];
    [view setWantsBestResolutionOpenGLSurface:YES];
    [win setContentView:view];
    [view setOpenGLContext:context];
    [context makeCurrentContext];
    int vsync = 1;
    [context setValues:&vsync forParameter:NSOpenGLCPSwapInterval];
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    _windowHandle = win;
    _openGlHandle = context;
    [win setWindow:this];
    resize(w, h, fullscreen);
    [win makeKeyAndOrderFront:nil];
    [win setupHid];
}

void
Window::resize(int w, int h, bool fullscreen)
{
    LMWindow* win = (LMWindow*)_windowHandle;
    NSOpenGLContext* context = (NSOpenGLContext*)_openGlHandle;

    [win setFrame:NSMakeRect(0, 0, w, h) display:YES animate:NO];
    if (fullscreen != _fullscreen)
    {
        _fullscreen = fullscreen;
        [win setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
        [win toggleFullScreen:win];
        [win setCollectionBehavior:0];
        if (fullscreen)
            [win setStyleMask:NSBorderlessWindowMask];
        else
            [win setStyleMask:0];
    }
    NSView* view = [win contentView];
    NSRect viewport = [view bounds];
    viewport = [view convertRectToBacking:[view bounds]];
    [context update];
}

bool
Window::visible() const
{
    LMWindow* win = (LMWindow*)_windowHandle;

    return [win occlusionState] & NSWindowOcclusionStateVisible;
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