// Copyright 2020 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
#ifndef CORE_RUNTIME_VM_LEPUS_TABLE_API_H_
#define CORE_RUNTIME_VM_LEPUS_TABLE_API_H_

#include "core/runtime/vm/lepus/builtin.h"

namespace lynx {
namespace lepus {

void RegisterTableAPI(Context* ctx);

}  // namespace lepus
}  // namespace lynx
#endif  // CORE_RUNTIME_VM_LEPUS_TABLE_API_H_
