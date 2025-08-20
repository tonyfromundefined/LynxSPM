// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

/**
 * This enum is used to define size measure mode of LynxView.
 * If mode is Undefined, the size will be determined by the content.
 * If mode is Exact, the size will be the size set by outside.
 * If mode is Max, the size will be determined by the content, but not exceed
 * the maximum size.
 */
typedef NS_ENUM(NSInteger, LynxViewSizeMode) {
  LynxViewSizeModeUndefined = 0,
  LynxViewSizeModeExact,
  LynxViewSizeModeMax
};

// now only support LynxThreadStrategyForRenderAllOnUI!
typedef NS_ENUM(NSInteger, LynxThreadStrategyForRender) {
  LynxThreadStrategyForRenderAllOnUI = 0,
  LynxThreadStrategyForRenderMostOnTASM = 1,
  LynxThreadStrategyForRenderPartOnLayout = 2,
  LynxThreadStrategyForRenderMultiThreads = 3,
};

/**
 * Embedded mode is an experimental switch
 * When embeddedMode is set, we offer optimal performance for embedded scenarios.
 * But it will restrict business flexibility.
 * Please DO NOT enable this switch on your own for now.
 * Contact the Lynx team for more information.
 * Embedded mode configuration options using bitwise operations for multiple selections
 *
 * Usage:
 * 1. Basic usage:
 *    - Use UNSET for no options selected
 *    - Use EMBEDDED_MODE_BASE for basic optimizations
 *    - Use EMBEDDED_MODE_ALL for all optimizations
 *
 * 2. Combine options:
 *    - Use bitwise OR (|) to combine options
 *    - Example: EMBEDDED_MODE_BASE | ENGINE_POOL
 *
 * 3. Check options:
 *    - Use bitwise AND (&) to check if an option is enabled
 *    - Example: (mode & ENGINE_POOL) != 0
 */
typedef NS_OPTIONS(NSInteger, EmbeddedMode) {
  /**
   * No optimization options selected
   */
  UNSET = 0,

  /**
   * Basic embedded mode with minimal optimizations
   */
  EMBEDDED_MODE_BASE = 1 << 0,

  /**
   * Engine pool optimization for better instance reuse
   */
  ENGINE_POOL = 1 << 1,

  /**
   * Combination of all optimization options
   *
   * Note: When adding new optimization options, update this value
   */
  EMBEDDED_MODE_ALL = EMBEDDED_MODE_BASE | ENGINE_POOL
};
