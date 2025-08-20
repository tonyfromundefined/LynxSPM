// Copyright 2021 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#import <Lynx/LynxListScrollEventEmitter.h>
#import <Lynx/LynxUICollection.h>

NS_ASSUME_NONNULL_BEGIN

@interface LynxUICollection (Delegate) <UICollectionViewDelegate,
                                        LynxListScrollEventEmitterDelegate>
- (void)sendLayoutCompleteEvent;
@end

NS_ASSUME_NONNULL_END
