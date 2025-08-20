// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#import <Lynx/LynxGenericResourceFetcher.h>
#import <Lynx/LynxGroup.h>
#import <Lynx/LynxMediaResourceFetcher.h>
#import <Lynx/LynxModule.h>
#import <Lynx/LynxResourceProvider.h>
#import <Lynx/LynxRuntimeLifecycleListener.h>
#import <Lynx/LynxTemplateData.h>
#import <Lynx/LynxTemplateResourceFetcher.h>

NS_ASSUME_NONNULL_BEGIN

@class LynxBackgroundRuntime;

@protocol LynxBackgroundRuntimeLifecycle <NSObject>

@optional

/**
 * Notify that runtime encounters error. May be called on UI Thread
 * @param runtime which runtime meets the error.
 * @param error the error object which should be a LynxError instance.
 * @see LynxError for error domain and error code.
 */
- (void)runtime:(LynxBackgroundRuntime *)runtime didRecieveError:(NSError *)error;

/**
 * Notify that runtime evaluates javascript end. May be called on UI Thread
 * @param runtime which runtime meets the error.
 * @param url the url of the script
 */
@optional
- (void)runtime:(LynxBackgroundRuntime *)runtime didEvaluateJavaScriptEnd:(NSString *)url;

@end

// Lynx background js runtime engine type.
typedef NS_ENUM(NSInteger, LynxBackgroundJsRuntimeType) {
  // default is jsc
  LynxBackgroundJsRuntimeTypeJSC = 0,
  // quickjs
  LynxBackgroundJsRuntimeTypeQuickjs = 1,
  // v8: Currently unavailable
  LynxBackgroundJsRuntimeTypeV8 = 2,
};

@interface LynxBackgroundRuntimeOptions : NSObject

@property(nonatomic, nullable) LynxGroup *group;
// background js runtime engine type.
@property(nonatomic, assign) LynxBackgroundJsRuntimeType backgroundJsRuntimeType;
// Readonly data for LynxBackgroundRuntime, FE can access this data
// via `lynx.__presetData`
@property(nonatomic, nullable) LynxTemplateData *presetData;

// Only when backgroundJsRuntimeType == LynxBackgroundJsRuntimeTypeQuickjs,it will take effect.
// enable bytecode for quickjs.
@property(nonatomic, assign) BOOL enableBytecode;

// Only when enableBytecode is YES, it will take effect.
// Set bytecode key for current lynxview.
@property(nonatomic, strong, nullable) NSString *bytecodeUrl;

// generic resource fetcher api.
@property(nonatomic, nonnull) id<LynxGenericResourceFetcher> genericResourceFetcher;
@property(nonatomic, nonnull) id<LynxMediaResourceFetcher> mediaResourceFetcher;
@property(nonatomic, nonnull) id<LynxTemplateResourceFetcher> templateResourceFetcher;

// Pending lynx_core.js load
@property(nonatomic, assign) BOOL pendingCoreJsLoad;

- (instancetype)init;
// @deprecated use LynxGenericResourceFetcher/LynxMediaResourceFetcher/LynxTemplateResourceFetcher
// instead
- (void)addLynxResourceProvider:(NSString *)resType provider:(id<LynxResourceProvider>)provider;
- (void)registerModule:(Class<LynxModule>)module;
- (void)registerModule:(Class<LynxModule>)module param:(nullable id)param;

@end

@interface LynxBackgroundRuntime : NSObject

@property(atomic, nullable, readonly) NSString *lastScriptUrl;

/**
 * Create a LynxBackgroundRuntime, can be called from any thread
 * @param options configuration for the runtime
 */

- (instancetype)initWithOptions:(LynxBackgroundRuntimeOptions *)options;

/**
 * Add LynxBackgroundRuntimeClient, client that listens to runtime's callback,  can be called from
 * any thread Call before other API to ensure callback won't be missed
 * @param lifecycleClient client to be added
 */
- (void)addLifecycleClient:(nonnull id<LynxBackgroundRuntimeLifecycle>)lifecycleClient;

/**
 * Remove LynxBackgroundRuntimeClient
 * @param lifecycleClient client to be removed
 */
- (void)removeLifecycleClient:(nonnull id<LynxBackgroundRuntimeLifecycle>)lifecycleClient;

/**
 * Execute a Background Script, can be called from any thread, valid until LynxBackgroundRuntime is
 * destroyed or attached.
 * @param url unique identifier for each script, will be used to track the script and related
 *     reports
 * @param sources content of the script
 */
- (void)evaluateJavaScript:(NSString *)url withSources:(NSString *)sources;

/**
 * Send GlobalEvent to Background Script, can be called from any thread, valid until
 * LynxBackgroundRuntime is destroyed or attached.
 * @param name event name
 * @param params event params
 */
- (void)sendGlobalEvent:(nonnull NSString *)name withParams:(nullable NSArray *)params;

/**
 * Add a listener for runtime lifecycle
 * @param listener the listener
 */
- (void)addRuntimeLifecycleListener:(nonnull id<LynxRuntimeLifecycleListener>)listener;

#pragma mark - Storage
/**
 * Set data on session storage, will always run on Lynx_JS thread
 * @param key data key
 * @param data storage data
 */
- (void)setSessionStorageItem:(nonnull NSString *)key
             withTemplateData:(nullable LynxTemplateData *)data;

/**
 * Get data on session storage, will always run on Lynx_JS thread
 * @param key data key
 * @param callback callback with data, will always run on Lynx_JS thread
 */
- (void)getSessionStorageItem:(nonnull NSString *)key
                 withCallback:(void (^_Nullable)(id<NSObject> _Nullable))callback;

/**
 * Subscribe a listener to listen data change on session storage,
 * will always run on Lynx_JS thread, this call may block on Lynx_JS
 * @param key data key
 * @param callback listener with data, will always run on Lynx_JS thread
 * @return listener id, used to unsubscribe
 */
- (double)subscribeSessionStorage:(nonnull NSString *)key
                     withCallback:(void (^_Nullable)(id<NSObject> _Nullable))callback;

/**
 * Unsubscribe a listener to listen data change on session storage, will always run on Lynx_JS
 * thread
 * @param key data key
 * @param callbackId listener with id to be erased
 */
- (void)unSubscribeSessionStorage:(nonnull NSString *)key withId:(double)callbackId;

/**
 * When setting pendingCoreJsLoad, this can load lynx_core.js when the user calls it.
 */
- (void)transitionToFullRuntime;

@end

NS_ASSUME_NONNULL_END
