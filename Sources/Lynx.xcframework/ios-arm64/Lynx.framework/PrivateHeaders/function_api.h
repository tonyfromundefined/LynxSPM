// Copyright 2023 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
#ifndef CORE_RUNTIME_VM_LEPUS_FUNCTION_API_H_
#define CORE_RUNTIME_VM_LEPUS_FUNCTION_API_H_

#include "core/runtime/vm/lepus/builtin.h"
namespace lynx {
namespace lepus {
void RegisterFunctionAPI(Context* ctx);
}  // namespace lepus
}  // namespace lynx
#endif  // CORE_RUNTIME_VM_LEPUS_FUNCTION_API_H_
