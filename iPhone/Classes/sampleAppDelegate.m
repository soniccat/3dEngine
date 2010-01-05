//
//  sampleAppDelegate.m
//  sample
//
//  Created by alexey on 1/4/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "sampleAppDelegate.h"
#import "EAGLView.h"

@implementation sampleAppDelegate

@synthesize window;
@synthesize glView;

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
	[glView startAnimation];
}

- (void) applicationWillResignActive:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
	[glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) dealloc
{
	[window release];
	[glView release];
	
	[super dealloc];
}

@end
