// Copyright 2009 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef SRC_GC_GLOBAL_HANDLES_H_
#define SRC_GC_GLOBAL_HANDLES_H_

// #include <vector>

#include "gc/persistent-handle.h"

typedef uintptr_t Addr;

// Global handles hold handles that are independent of stack-state and can have
// callbacks and finalizers attached to them.
class GlobalHandles final {
 public:
  static void EnableMarkingBarrier(LEPUSRuntime* runtime);
  static void DisableMarkingBarrier(LEPUSRuntime* runtime);

  GlobalHandles(const GlobalHandles&) = delete;
  GlobalHandles& operator=(const GlobalHandles&) = delete;

  class NodeBlock;

  static void Destroy(LEPUSValue* location);

  explicit GlobalHandles(LEPUSRuntime* runtime);
  ~GlobalHandles();

  // Creates a new global handle that is alive until Destroy is called.
  LEPUSValue* Create(LEPUSValue value, bool is_weak);

  void IterateAllRoots(int local_idx, int offset);
  void GlobalRootsFinalizer();
  bool IsMarkedLEPUSValue(LEPUSValue* val);
  LEPUSRuntime* runtime() const { return runtime_; }

  size_t TotalSize() const;
  size_t UsedSize() const;
  // Number of global handles.
  size_t handles_count() const;
  void SetWeak(LEPUSValue* location, void* data, void (*cb)(void*));
  void ClearWeak(LEPUSValue* location);
  void SetWeakState(LEPUSValue* location);

 private:
  // Internal node structures.
  class NodeIterator;
  class NodeSpace;

  LEPUSRuntime* const runtime_;
  bool is_marking_ = false;

  NodeSpace* regular_nodes_;
};

#endif  // SRC_GC_GLOBAL_HANDLES_H_
