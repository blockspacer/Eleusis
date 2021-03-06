#ifdef __APPLE__

#pragma once

#import <Cocoa/Cocoa.h>

#include "Window.h"

@interface EleusisNSWindow : NSWindow
    - (id)initWithOwner:(Eleusis::Window*)owner;
    - (void)show:(CGContextRef)context;
    + (void)populateSpecialKeyState:(Eleusis::SpecialKeysInputParams*)inputParams event:(NSEvent*)event;
@end


#endif
