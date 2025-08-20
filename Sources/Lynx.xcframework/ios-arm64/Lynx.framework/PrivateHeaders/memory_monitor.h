// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_SERVICES_PERFORMANCE_MEMORY_MONITOR_MEMORY_MONITOR_H_
#define CORE_SERVICES_PERFORMANCE_MEMORY_MONITOR_MEMORY_MONITOR_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/public/pub_value.h"
#include "core/services/performance/memory_monitor/memory_record.h"
#include "core/value_wrapper/value_impl_lepus.h"

namespace lynx {
namespace tasm {
namespace performance {

// @class MemoryMonitor
// @brief A class for monitoring memory usage and managing memory records.
//
// The MemoryMonitor class provides functionality to allocate, deallocate,
// and update memory usage records. It maintains a mapping of categories to
// their respective MemoryRecord instances, allowing for efficient tracking
// of memory utilization.
class MemoryMonitor {
  friend class PerformanceController;

 public:
  class Delegate {
   public:
    virtual ~Delegate() = default;
    virtual void OnPerformanceEvent(
        const std::unique_ptr<lynx::pub::Value> entry) = 0;
    virtual const std::unique_ptr<pub::PubValueFactory>& GetValueFactory() = 0;
    virtual int32_t GetInstanceId() = 0;
  };

  // Increments memory usage and sends a PerformanceEntry.
  // This interface will increase the total memory usage for the category found
  // in the record.
  void AllocateMemory(MemoryRecord&& record);

  // Decrements memory usage and sends a PerformanceEntry.
  // This interface will decrease the total memory usage for the category found
  // in the record.
  void DeallocateMemory(MemoryRecord&& record);

  // Overwrites the memory usage and sends a PerformanceEntry.
  // This interface will overwrite the record corresponding to the category in
  // the record, effectively updating the memory usage information.
  void UpdateMemoryUsage(MemoryRecord&& record);

  // Checks if memory monitoring is enabled.
  // Modules can call this before collecting data to avoid unnecessary
  // collection.
  static bool Enable();

  // Checks if memory monitoring is enabled.
  // Modules can call this before collecting data to avoid unnecessary
  // collection.
  static void SetForceEnable(bool force_enable);

  // The threshold for memory increase and decrease that triggers collection, in
  // MB. This is configured through Settings.
  static uint32_t MemoryChangeThresholdMb();

  /// @brief Generates a bitmask for scripting engine memory monitoring
  /// configuration This method combines memory monitoring status and memory
  /// increment threshold into a uint32_t bitmask:
  /// - Bit 0 (LSB)  : Whether memory monitoring is enabled (1=enabled,
  /// 0=disabled)
  /// - Bits 1-8      : Memory increment threshold in MB (capped at 100MB)
  /// @return uint32_t Combined configuration bitmask
  static uint32_t ScriptingEngineMode();

  explicit MemoryMonitor(Delegate* delegate) : delegate_(delegate){};
  ~MemoryMonitor();
  MemoryMonitor(const MemoryMonitor& timing) = delete;
  MemoryMonitor& operator=(const MemoryMonitor&) = delete;
  MemoryMonitor(MemoryMonitor&& other);
  MemoryMonitor& operator=(MemoryMonitor&& other);

 private:
  void ReportMemory();

  Delegate* delegate_;
  std::unordered_map<MemoryCategory, MemoryRecord> memory_records_;
};

}  // namespace performance
}  // namespace tasm
}  // namespace lynx

#endif  // CORE_SERVICES_PERFORMANCE_MEMORY_MONITOR_MEMORY_MONITOR_H_
