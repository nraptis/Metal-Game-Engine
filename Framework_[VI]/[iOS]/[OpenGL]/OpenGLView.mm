//
//  OpenGLView.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "core_includes.h"
#import "core_app_shell.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "OpenGLViewController.h"
#import "OpenGLView.h"
#import "FMatrix.h"
#import "FImage.hpp"
#import "FApp.hpp"


//TODO: Change contents of non-uniform buffer mid-render and compare results versus un changed non-uniform buffer which remains
//static throughout render pass, can we change the data mid render, or does the binding occur only on commit???... huh?

//TODO: You must CERTAINLY be able to use only one "sprite buffer" and
//share it among all of the different sprites? Or... ?

//static unsigned int gGLBufferRender = 0;
//static unsigned int gGLBufferDepth = 0;


@interface OpenGLView() {
    
}

@end

@implementation OpenGLView

- (void)setup {
    gOpenGLView = self;
    //
    //
    //
    ///////////////////
    //
    //
    //
    _screenScale = (int)([UIScreen mainScreen].scale + 0.5f);
    printf("SCREEN SCALE: [[%d]]\n", _screenScale);
    //

    
    
    
    
    self.multipleTouchEnabled = YES;
    
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
    gOpenGLLayer = _eaglLayer;
    
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    
    _context = [[EAGLContext alloc] initWithAPI:api];
    
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext: _context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
    
    /*
    glGenRenderbuffers(1, &gGLBufferDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, gGLBufferDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
    
    glGenRenderbuffers(1, &gGLBufferRender);
    glBindRenderbuffer(GL_RENDERBUFFER, gGLBufferRender);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
    */
    //
    //
    //[self active];
    //
    //
}

+ (id)layerClass {
    return [CAEAGLLayer class];
}

- (void)displayCallback {
    
}

- (void)active {
    if (_displayLink == NULL) {
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(displayCallback)];
        [_displayLink setPreferredFramesPerSecond: 60];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode: NSDefaultRunLoopMode];
    }
}

- (void)inactive {
    if (_displayLink != NULL) {
        [_displayLink invalidate];
        _displayLink = nil;
    }
}

- (void)setContext {
    if (_context) {
        [EAGLContext setCurrentContext: _context];
    }
}

- (void)commit {
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
        if ([aTouch phase] == UITouchPhaseBegan) {
            CGPoint aLocation = [aTouch locationInView:self];
            AppShellTouchDown(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase] == UITouchPhaseMoved) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchMove(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase] == UITouchPhaseEnded) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchUp(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase]  == UITouchPhaseCancelled) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchCanceled(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

@end
