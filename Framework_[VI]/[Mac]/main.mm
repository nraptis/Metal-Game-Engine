//
//  main.m
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"
#import "GFXApp.hpp"
//#include "core_app_shell.hpp"

int main(int argc, const char * argv[]) {
    
    gDirBundle = "/Users/nraptis/Desktop/Orbital/Assets/";
    gDirDocuments = "/Users/nraptis/Desktop/Orbital/Documents/";
    gDirExport = "/Users/nraptis/Desktop/[[Exports]]/";
    
    gApp = new GFXApp();
    AppShellInitialize(ENV_MAC);
    
    [NSApplication sharedApplication];
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate: appDelegate];
    [NSApp run];
    return 0;
}
