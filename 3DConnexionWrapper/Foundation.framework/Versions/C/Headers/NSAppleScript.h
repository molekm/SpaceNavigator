/*
	NSAppleScript.h
	Copyright (c) 2002-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>


@class NSAppleEventDescriptor, NSDictionary, NSString, NSURL;

// If the result of -initWithContentsOfURL:error:, -compileAndReturnError:, -executeAndReturnError:, or -executeAppleEvent:error:, signals failure (nil, NO, nil, or nil, respectively), a pointer to an autoreleased dictionary is put at the location pointed to by the error parameter.  The error info dictionary may contain entries that use any combination of the following keys, including no entries at all.
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorMessage NS_AVAILABLE(10_2, NA); // NSString
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorNumber NS_AVAILABLE(10_2, NA); // NSNumber
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorAppName NS_AVAILABLE(10_2, NA); // NSString
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorBriefMessage NS_AVAILABLE(10_2, NA); // NSString
FOUNDATION_EXPORT NSString *const NSAppleScriptErrorRange NS_AVAILABLE(10_2, NA); // NSValue containing an NSRange

@interface NSAppleScript : NSObject<NSCopying> {
    @private
    NSString *_source;
    unsigned int _compiledScriptID;
    void *_reserved1;
    void *_reserved2;
}

// Given a URL that locates a script, in either text or compiled form, initialize.  Return nil and a pointer to an error information dictionary if an error occurs.  This is a designated initializer for this class.
- (instancetype)initWithContentsOfURL:(NSURL *)url error:(NSDictionary **)errorInfo NS_DESIGNATED_INITIALIZER;

// Given a string containing the AppleScript source code of a script, initialize.  Return nil if an error occurs.  This is also a designated initializer for this class.
- (instancetype)initWithSource:(NSString *)source NS_DESIGNATED_INITIALIZER;

// Return the source code of the script if it is available, nil otherwise.  It is possible for an NSAppleScript that has been instantiated with -initWithContentsOfURL:error: to be a script for which the source code is not available, but is nonetheless executable.
@property (readonly, copy) NSString *source;

// Return yes if the script is already compiled, no otherwise.
@property (readonly, getter=isCompiled) BOOL compiled;

// Compile the script, if it is not already compiled.  Return yes for success or if the script was already compiled, no and a pointer to an error information dictionary otherwise.
- (BOOL)compileAndReturnError:(NSDictionary **)errorInfo;

// Execute the script, compiling it first if it is not already compiled.  Return the result of executing the script, or nil and a pointer to an error information dictionary for failure.
- (NSAppleEventDescriptor *)executeAndReturnError:(NSDictionary **)errorInfo;

// Execute an Apple event in the context of the script, compiling the script first if it is not already compiled.  Return the result of executing the event, or nil and a pointer to an error information dictionary for failure.
- (NSAppleEventDescriptor *)executeAppleEvent:(NSAppleEventDescriptor *)event error:(NSDictionary **)errorInfo;

@end

