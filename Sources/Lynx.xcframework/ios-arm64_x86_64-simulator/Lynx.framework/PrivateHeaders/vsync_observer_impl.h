// Copyright 2023 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_SHELL_VSYNC_OBSERVER_IMPL_H_
#define CORE_SHELL_VSYNC_OBSERVER_IMPL_H_

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base/include/closure.h"
#include "base/include/fml/memory/ref_ptr.h"
#include "base/include/fml/task_runner.h"
#include "core/public/vsync_observer_interface.h"
#include "core/runtime/piper/js/lynx_runtime.h"

namespace lynx {

namespace base {
class VSyncMonitor;
}

namespace shell {

class VSyncObserverImpl : public runtime::IVSyncObserver {
 public:
  VSyncObserverImpl(
      const std::shared_ptr<base::VSyncMonitor>& monitor,
      fml::RefPtr<fml::TaskRunner> js_runner,
      const std::shared_ptr<LynxActor<runtime::LynxRuntime>>& runtime_actor)
      : vsync_monitor_(std::move(monitor)),
        js_runner_(js_runner),
        runtime_actor_(runtime_actor) {}

  void RequestAnimationFrame(
      uintptr_t id,
      base::MoveOnlyClosure<void, int64_t, int64_t> callback) override;

  void RequestBeforeAnimationFrame(
      uintptr_t id,
      base::MoveOnlyClosure<void, int64_t, int64_t> callback) override;

  void RegisterAfterAnimationFrameListener(
      base::MoveOnlyClosure<void, int64_t, int64_t> callback) override;

 private:
  using VSyncCallback = base::MoveOnlyClosure<void, int64_t, int64_t>;
  using VSyncCallbackMap = std::unordered_map<uintptr_t, VSyncCallback>;

  std::shared_ptr<base::VSyncMonitor> vsync_monitor_{nullptr};
  fml::RefPtr<fml::TaskRunner> js_runner_{nullptr};
  std::shared_ptr<LynxActor<runtime::LynxRuntime>> runtime_actor_;

  bool has_pending_vsync_request_{false};
  VSyncCallbackMap vsync_callbacks_;
  VSyncCallbackMap before_animation_frame_callbacks_;
  std::vector<VSyncCallback> after_animation_frame_callbacks_;

  VSyncCallbackMap& vsync_callbacks() { return vsync_callbacks_; }
  void SwapVSyncCallbacks(std::vector<VSyncCallback>& swap_callbacks);
  void RequestVSync();
  void DoFrame(int64_t frame_start_time, int64_t frame_end_time);
};

}  // namespace shell
}  // namespace lynx

#endif  // CORE_SHELL_VSYNC_OBSERVER_IMPL_H_
