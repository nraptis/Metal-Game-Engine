//
//  RootViewController.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#define METAL_MODE 1
//#undef METAL_MODE

#import "RootViewController.h"
#import "AppDelegate.h"

#ifdef METAL_MODE
#import "MetalViewController.h"
#else
#import "OpenGLViewController.h"
#endif

#import "FApp.hpp"

RootViewController *gRootBase = NULL;

@interface RootViewController ()

#ifdef METAL_MODE
@property (nonatomic, strong) MetalViewController *metalViewController;
#else
@property (nonatomic, strong) OpenGLViewController *openGLViewController;
#endif

@end

@implementation RootViewController

- (void)viewDidLoad {
    
    gRootBase = self;
    
    [super viewDidLoad];
    
    self.view.opaque = true;
    self.view.backgroundColor = [UIColor blackColor];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        //gAppBase->MainRunLoop();
    });
}


- (void)setup {
    
    self.view.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    
#ifdef METAL_MODE
    _metalViewController = [[MetalViewController alloc] init];
    [_metalViewController loadViewIfNeeded];
    [self.view addSubview:_metalViewController.view];
    [_metalViewController setup];
#else
    _openGLViewController = [[OpenGLViewController alloc] init];
    [_openGLViewController loadViewIfNeeded];
    [self.view addSubview:_openGLViewController.view];
    [_openGLViewController setup];
#endif
    
    
}



/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (BOOL)isLandscape {
    return false;
}

- (BOOL)prefersStatusBarHidden {
    return true;
}

- (void) active {
    
#ifdef METAL_MODE
    [gMetalView startAnimating];
#else
    
#endif
    

}

- (void) inactive {
#ifdef METAL_MODE
    [gMetalView stopAnimating];
#else
    
#endif
}


@end
