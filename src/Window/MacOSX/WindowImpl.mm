/* ************************************************************************** */
/*                                                                            */
/*    Window/MacOSX/WindowImpl.mm                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#import "WindowImpl.hpp"

using namespace lm;

WindowImpl::WindowImpl(Window* parent, unsigned width, unsigned height, const char* name)
: _parent(parent)
{
    NSWindow* win = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
        styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO];
    [win makeKeyAndOrderFront:nil];
    _window = win;
}

void
lm::initApplication()
{
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp finishLaunching];
}
