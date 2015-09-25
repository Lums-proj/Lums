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
    NSOpenGLPFANoRecovery,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFAColorSize, 32,
    NSOpenGLPFAAlphaSize, 8,
    NSOpenGLPFADepthSize, 24,
    NSOpenGLPFAStencilSize, 8,
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAMinimumPolicy,
    kCGLPFAOpenGLProfile,
    kCGLOGLPVersion_3_2_Core,
    0
};

Window::Window(int w, int h, const char* name, bool fullscreen)
: _fullscreen(false)
, _fbo()
, _texBuffer()
{
    _size = {w, h};
    NSRect frame = NSMakeRect(0, 0, w, h);
    LMWindow* win = [[[LMWindow alloc] initWithContentRect:frame
                    styleMask:NSTitledWindowMask
                    backing:NSBackingStoreBuffered
                    defer:NO] autorelease];
    [win setCollectionBehavior:[win collectionBehavior] | NSWindowCollectionBehaviorFullScreenPrimary];
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _windowHandle = win;
    _openGlHandle = context;
    glGenFramebuffers(1, &_fbo);
    glGenTextures(2, _texBuffer);
    glGenTextures(1, &_depthBuffer);
    for (int i = 0; i < 2; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, _texBuffer[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    }
    glBindTexture(GL_TEXTURE_2D, _depthBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    [win setWindow:this];
    [win setupHid];
    resize(w, h, fullscreen);
}

void
Window::resize(int w, int h, bool fullscreen)
{
    _size = {w, h};
    auto screenSize = maxSize();
    LMWindow* win = (LMWindow*)_windowHandle;
    NSOpenGLContext* context = (NSOpenGLContext*)_openGlHandle;
    
    if (fullscreen != _fullscreen)
    {
        _fullscreen = fullscreen;
        [win toggleFullScreen:win];
    }
    NSRect oldFrame = [[win contentView] convertRectToBacking:[win frame]];
    NSRect frame;

    if (!fullscreen)
        frame = NSMakeRect(oldFrame.origin.x, oldFrame.origin.y, w, h);
    else
        frame = NSMakeRect(0, 0, screenSize.x, screenSize.y);

    NSRect retinaFrame = [[win contentView] convertRectFromBacking:frame];

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glBindTexture(GL_TEXTURE_2D, _texBuffer[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texBuffer[0], 0);
    glBindTexture(GL_TEXTURE_2D, _texBuffer[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _texBuffer[1], 0);
    glBindTexture(GL_TEXTURE_2D, _depthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    frame = [win frameRectForContentRect:retinaFrame];
    [win setFrame:frame display:YES animate:YES];
    [context update];
    [win makeKeyAndOrderFront:nil];
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
    NSRect screen = [[NSScreen mainScreen] frame];

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