//
//  AppDelegate.m
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "AppDelegate.h"
#import "core_app_shell.hpp"
#include "FApp.hpp"

//int kDeviceWidth = 480;
//int kDeviceHeight = 320;

int kDeviceWidth = 1400;
int kDeviceHeight = 760;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    
    float aMonitorWidth = [NSScreen mainScreen].frame.size.width;
    float aMonitorHeight = [NSScreen mainScreen].frame.size.height;
    
    float aMaxWidth = (int)(aMonitorWidth * 0.95f);
    float aMaxHeight = (int)(aMonitorHeight * 0.85f);
    
    //TODO: Sometimes we want to restrict this size, heh...
    //if (kDeviceWidth > aMaxWidth) kDeviceWidth = aMaxWidth;
    //if (kDeviceHeight > aMaxHeight) kDeviceHeight = aMaxHeight;
    
    NSLog(@"Monitor Size: %d x %d\n", (int)aMonitorWidth, (int)aMonitorHeight);
     
    //float aOSVersion = [[[UIDevice currentDevice] systemVersion] floatValue];
    //bool aIsTablet = false;
    
    //kDeviceWidth = [UIScreen mainScreen].bounds.size.width + 0.5f;
    //kDeviceHeight = [UIScreen mainScreen].bounds.size.height + 0.5f;
    
    char aBundlePath[2048];
    
    getcwd(aBundlePath, sizeof(aBundlePath));
    strcat(aBundlePath, "/Assets/");
    
    NSLog(@"Read Bundle Directory: %s", aBundlePath);
    AppShellSetDirectoryBundle(aBundlePath);
    
    char aDocPath[2048];
    getcwd(aDocPath, sizeof(aDocPath));
    strcat(aDocPath, "/Documents/");
    AppShellSetDirectoryDocuments(aDocPath);
    
    NSLog(@"Read Docs Directory: %s", aBundlePath);
    
    
    
    
    
    AppShellInitialize(ENV_MAC);
    
    AppShellSetDeviceSize(kDeviceWidth, kDeviceHeight);
    AppShellSetVirtualFrame(0, 0, kDeviceWidth, kDeviceHeight);
    AppShellSetDeviceSize(kDeviceWidth, kDeviceHeight);
    
    
    AppShellSetImageFileScale(1);

    
    
    _rootViewController = [[RootViewController alloc] init];
    
    CGSize screenSize = [[NSScreen mainScreen] frame].size;
    
    NSWindowStyleMask aWindowStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
    NSRect aWindowFrame = NSMakeRect(14.0, screenSize.height / 2.0 - kDeviceHeight / 2.0 - 14, kDeviceWidth, kDeviceHeight);
    
    _window = [[NSWindow alloc] initWithContentRect: aWindowFrame styleMask: aWindowStyle backing: NSBackingStoreBuffered defer: NO];
    [_window setTitle:@"Robot Reptile Motorcycle Gun"];
    [_window setOpaque: YES];
    [_window setHasShadow: YES];
    [_window setDelegate: self];
    _window.contentViewController = self.rootViewController;
    
    NSColor *aColor = [NSColor colorWithCalibratedRed: 0.0f green: 0.0f blue: 0.0f alpha: 1.0];
    [_window setBackgroundColor: aColor];
    [_window makeKeyAndOrderFront: NSApp];
    
    if ([_rootViewController isViewLoaded] == false) {
        [_rootViewController loadView];
    };
    
    //...
    
    [_rootViewController setup];
    
    AppShellLoad();

    
}

- (void)applicationWillTerminate: (NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    
    if (gAppBase != NULL) {
        gAppBase->BaseQuit();
    }
    
    [_rootViewController.metalViewController teardown];
    
    os_sleep(220);
    return YES;
}

//- (nullable id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(nullable id)client;
- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize {
    
    NSLog(@"App Resize (%f x %f)\n", frameSize.width, frameSize.height);
    
    //Bad thing to do. All textures and render pass need resize.
    
    //gAppBase->ThrottleLock();
    //[_rootViewController resize: frameSize];
    //gAppBase->ThrottleUnlock();
    
    return frameSize;
}


@end
