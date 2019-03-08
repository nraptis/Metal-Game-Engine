//
//  MetalView.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "AppDelegate.h"
#import "MetalView.h"
#import "RootViewController.h"
#import "FTouchManager.h"



//TODO: Change contents of non-uniform buffer mid-render and compare results versus un changed non-uniform buffer which remains
//static throughout render pass, can we change the data mid render, or does the binding occur only on commit???... huh?

//TODO: You must CERTAINLY be able to use only one "sprite buffer" and
//share it among all of the different sprites? Or... ?

@interface MetalView() {
    
}

@end

@implementation MetalView

CVReturn displayCallback(CVDisplayLinkRef CV_NONNULL displayLink,
                         const CVTimeStamp * CV_NONNULL inNow,
                         const CVTimeStamp * CV_NONNULL inOutputTime,
                         CVOptionFlags flagsIn,
                         CVOptionFlags * CV_NONNULL flagsOut,
                         void * CV_NULLABLE displayLinkContext ) {
    // For now this does nothing,
    // without semaphore, we could
    // control frame from here..
    
    return kCVReturnSuccess;
}

- (void)setup {
    _screenScale = (int)([NSScreen mainScreen].backingScaleFactor + 0.5f);
    
    printf("Screen Scale = [[%d]]\n", _screenScale);
    
    self.layer = [[CAMetalLayer alloc] init];
    _metalLayer = (CAMetalLayer *)self.layer;
    gMetalLayer = _metalLayer;
    _metalLayer.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    _metalLayer.contentsScale = _screenScale;
    
    //
    // Make the display link... For Mac...
    //
    CGDirectDisplayID displayID = CGMainDisplayID();
    CVReturn error = CVDisplayLinkCreateWithCGDisplay(displayID, &_displayLink);
    NSAssert((kCVReturnSuccess == error), @"Creating Display Link error %d", error);
    error = CVDisplayLinkSetOutputCallback(_displayLink, displayCallback, (__bridge void*)self);
    NSAssert((kCVReturnSuccess == error), @"Setting Display Link callback error %d", error);
    CVDisplayLinkStart(_displayLink);
}

- (CGPoint)correctMousePos: (CGPoint)pos {
    CGPoint aResult = CGPointMake(pos.x, gDeviceHeight - pos.y);
    return aResult;
}

- (void)mouseDown:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseDown(aPoint.x, aPoint.y, MOUSE_BUTTON_LEFT);
}

- (void)mouseDragged:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseMove(aPoint.x, aPoint.y);
}

- (void)mouseUp:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseUp(aPoint.x, aPoint.y, MOUSE_BUTTON_LEFT);
}

- (void)rightMouseDown:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseDown(aPoint.x, aPoint.y, MOUSE_BUTTON_RIGHT);
}

- (void)rightMouseUp:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseUp(aPoint.x, aPoint.y, MOUSE_BUTTON_RIGHT);
}

- (void)rightMouseDragged:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseMove(aPoint.x, aPoint.y);
}

@end
