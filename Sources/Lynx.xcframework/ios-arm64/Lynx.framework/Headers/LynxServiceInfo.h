// Copyright 2022 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#import <Foundation/Foundation.h>

@class LynxContext;
NS_ASSUME_NONNULL_BEGIN
@interface LynxServiceInfo : NSObject

@property(nonatomic, weak) LynxContext *context;
@property(nonatomic, strong) NSDictionary *extra;

@end

NS_ASSUME_NONNULL_END
