// Copyright 2022 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef DARWIN_COMMON_LYNX_ENGINE_PROXY_H_
#define DARWIN_COMMON_LYNX_ENGINE_PROXY_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class LynxEvent;
@class LynxTouchEvent;
@class LynxCustomEvent;

@interface LynxEngineProxy : NSObject

/**
 * Dispatch a given task to be executed on the LynxEngine's running thread.
 * @param task The block to be dispatched
 */
- (void)dispatchTaskToLynxEngine:(dispatch_block_t)task;

/**
 * Invoke lepus function
 *  @param data function params
 *  @param callbackID the key of invoke task
 */
- (void)invokeLepusFunc:(NSDictionary *)data callbackID:(int32_t)callbackID;

/**
 * Synchronously send touch event to runtime
 *  @param event touch param
 */
- (void)sendSyncTouchEvent:(LynxTouchEvent *)event;
- (void)sendSyncMultiTouchEvent:(LynxTouchEvent *)event;

/**
 * Synchronously send gesture event to runtime
 * @param event custom event param
 */
- (void)sendGestureEvent:(int)gestureId event:(LynxCustomEvent *)event;

/**
 * Synchronously send custom event to runtime
 *  @param event custom event param
 */
- (void)sendCustomEvent:(LynxCustomEvent *)event;

/**
 * Notify css pseudo status change
 *  @param tag pseudo tag
 *  @param preStatus previous pseudo status
 *  @param currentStatus current pseudo status
 */
- (void)onPseudoStatusChanged:(int32_t)tag
                fromPreStatus:(int32_t)preStatus
              toCurrentStatus:(int32_t)currentStatus;

- (void)startEventGenerate:(LynxEvent *)event;
- (void)startEventCapture:(int64_t)eventID;
- (void)startEventBubble:(int64_t)eventID;
- (void)startEventFire:(BOOL)isStop withEventID:(int64_t)eventID;

@end

NS_ASSUME_NONNULL_END

#endif  // DARWIN_COMMON_LYNX_ENGINE_PROXY_H_
