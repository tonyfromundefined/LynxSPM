// Inspired by S.js by Adam Haile, https://github.com/adamhaile/S
/**
The MIT License (MIT)

Copyright (c) 2017 Adam Haile

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_SIGNAL_SCOPE_H_
#define CORE_RENDERER_SIGNAL_SCOPE_H_

#include <list>

#include "core/runtime/vm/lepus/ref_counted_class.h"
#include "core/runtime/vm/lepus/ref_type.h"

namespace lynx {

namespace lepus {
class Context;
}

namespace tasm {

enum class ScopeType : int32_t {
  kPureScope = 0,
  kPureComputation,
  kMemoComputation,
};

enum class ScopeState : int32_t {
  kStateNone = 0,
  kStateStale,
  kStatePending,
};

class SignalContext;
class Computation;

class BaseScope : public lepus::RefCounted {
 public:
  BaseScope(SignalContext* context, lepus::Context* vm_context);
  virtual ~BaseScope();

  SignalContext* signal_context() const { return signal_context_; }
  lepus::Context* vm_context() const { return vm_context_; }

  void SetScopeType(ScopeType type) { scope_type_ = type; }
  ScopeType GetScopeType() { return scope_type_; };

  void SetState(ScopeState state) { scope_state_ = state; }
  ScopeState GetState() { return scope_state_; }

  void SetUpdatedTime(int32_t updated_time) { updated_time_ = updated_time; }
  int32_t GetUpdatedTime() { return updated_time_; }

  virtual void CleanUp();

  void OnCleanUp(const lepus::Value& block);

  void AdoptComputation(fml::RefPtr<Computation>&& computation);

  BaseScope* GetOwner();

 protected:
  ScopeType scope_type_{ScopeType::kPureScope};
  ScopeState scope_state_;

  int32_t updated_time_{-1};

  SignalContext* signal_context_{nullptr};
  lepus::Context* vm_context_{nullptr};

  BaseScope* owner_{nullptr};

  std::list<fml::RefPtr<Computation>> owned_computation_;

  std::list<lepus::Value> clean_up_callbacks_;
};

class Scope : public BaseScope {
 public:
  Scope(SignalContext* signal_context, lepus::Context* vm_context,
        const lepus::Value& closure);
  virtual ~Scope();

  lepus::RefType GetRefType() const { return lepus::RefType::kScope; }

  lepus::Value ObtainResult();

  void WillDestroy();

 private:
  bool will_destroy_{false};

  lepus::Value result_;
};

}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_SIGNAL_SCOPE_H_
