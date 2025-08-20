// Copyright 2023 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#import <Lynx/LynxView.h>

NS_ASSUME_NONNULL_BEGIN

@interface LynxView (Identify)

@property(nonatomic, copy) NSString *containerID;
@property(nonatomic, copy, nullable) NSString *namescope;

@end

NS_ASSUME_NONNULL_END
