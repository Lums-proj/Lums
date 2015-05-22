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
, _fbo()
, _texBuffer()
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
    glGenFramebuffers(2, _fbo);
    glGenTextures(2, _texBuffer);
    glGenTextures(2, _depthBuffer);
    for (int i = 0; i < 2; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, _texBuffer[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glBindTexture(GL_TEXTURE_2D, _depthBuffer[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    }
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
    int styleMask = fullscreen ? NSBorderlessWindowMask : 0;

    if (fullscreen != _fullscreen)
    {
        _fullscreen = fullscreen;
        [win setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
        [win toggleFullScreen:win];
        [win setCollectionBehavior:0];
        [win setStyleMask:styleMask];
    }
    NSRect oldFrame = [[win contentView] convertRectToBacking:[win frame]];
    NSRect frame = NSMakeRect(oldFrame.origin.x, oldFrame.origin.y, w, h);
    frame = [[win contentView] convertRectFromBacking:frame];
    frame = [win frameRectForContentRect:frame];
    [win setFrame:frame display:YES animate:YES];
    [context update];
    for (int i = 0; i < 2; ++i)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo[i]);
        glBindTexture(GL_TEXTURE_2D, _texBuffer[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.size.width, frame.size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texBuffer[i], 0);
        glBindTexture(GL_TEXTURE_2D, _depthBuffer[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, frame.size.width, frame.size.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer[i], 0);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool
Window::visible() const
{
    LMWindow* win = (LMWindow*)_windowHandle;

    return [win occlusionState] & NSWindowOcclusionStateVisible;
}

Vector2i
Window::maxSize() const
{
    NSRect screen = [[NSScreen mainScreen] visibleFrame];

    screen = [(NSWindow*)_windowHandle convertRectToBacking:screen];
    return {screen.size.width, screen.size.height};
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