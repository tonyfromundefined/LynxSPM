// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RUNTIME_BINDINGS_JSI_TEXT_CODEC_HELPER_H_
#define CORE_RUNTIME_BINDINGS_JSI_TEXT_CODEC_HELPER_H_

#include <vector>

#include "core/runtime/jsi/jsi.h"

namespace lynx {
namespace piper {

class TextCodecHelper : public HostObject {
 public:
  TextCodecHelper() = default;

  virtual Value get(Runtime*, const PropNameID& name) override;
  virtual std::vector<PropNameID> getPropertyNames(Runtime& rt) override;
};

}  // namespace piper
}  // namespace lynx
#endif  // CORE_RUNTIME_BINDINGS_JSI_TEXT_CODEC_HELPER_H_
