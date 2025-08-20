// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_UI_COMPONENT_LIST_STAGGERED_GRID_LAYOUT_MANAGER_H_
#define CORE_RENDERER_UI_COMPONENT_LIST_STAGGERED_GRID_LAYOUT_MANAGER_H_

#include <vector>

#include "core/renderer/ui_component/list/list_layout_manager.h"

namespace lynx {
namespace tasm {

class StaggeredGridLayoutManager : public ListLayoutManager {
 public:
  class SpanItemInfo {
   public:
    SpanItemInfo(int span_index = list::kInvalidIndex,
                 int item_index = list::kInvalidIndex)
        : span_index_(span_index), item_index_(item_index) {}

    bool IsValid() const {
      return span_index_ != list::kInvalidIndex &&
             item_index_ != list::kInvalidIndex;
    }

    int span_index_{list::kInvalidIndex};
    int item_index_{list::kInvalidIndex};
  };

  class LayoutState {
   public:
    LayoutState(int span_count, list::LayoutDirection layout_direction =
                                    list::LayoutDirection::kLayoutToEnd)
        : layout_direction_(layout_direction) {
      start_lines.resize(span_count);
      start_index.resize(span_count);
      end_lines.resize(span_count);
      end_index.resize(span_count);
    }

    void Reset(int span_count) {
      layout_direction_ = list::LayoutDirection::kLayoutToEnd;
      is_start_full_span_ = false;
      is_end_full_span_ = false;
      start_lines.assign(span_count, 0.f);
      start_index.assign(span_count, 0);
      end_lines.assign(span_count, 0.f);
      end_index.assign(span_count, 0);
    }

    // Layout direction
    list::LayoutDirection layout_direction_{
        list::LayoutDirection::kLayoutToEnd};
    // The latest updated content offset.
    float latest_updated_content_offset_{0.f};

    bool is_start_full_span_{false};
    bool is_end_full_span_{false};
    // Top item_holds at each columns
    std::vector<float> start_lines{};
    std::vector<int> start_index{};
    // Bottom item_holds at each columns
    std::vector<float> end_lines{};
    std::vector<int> end_index{};
  };

  StaggeredGridLayoutManager(ListContainerImpl* list_container_impl);
  ~StaggeredGridLayoutManager() override = default;

  void InitLayoutState() override;
  void OnBatchLayoutChildren() override;
  void OnLayoutChildren(bool is_component_finished = false,
                        int component_index = -1) override;

 protected:
  void ScrollByInternal(float content_offset, float original_offset,
                        bool from_platform) override;
  void LayoutInvalidItemHolder(int first_invalid_index) override;
  float GetTargetContentSize() override;
#if ENABLE_TRACE_PERFETTO
  void UpdateTraceDebugInfo(TraceEvent* event) const override;
#endif

 private:
  // Update layout state
  void UpdateStartAndEndLinesStatus(LayoutState& layout_state);

  void OnLayoutChildrenInternal(ListAnchorManager::AnchorInfo& anchor_info,
                                LayoutState& layout_state);

  // Bind all visible item_holders to create a valid trunk for fill. Return true
  // if a 'componentAtIndex' really called.
  bool BindAllVisibleItemHolders();

  void OnLayoutAfter();
  void OnScrollAfter(float original_offset);
  void HandleLayoutOrScrollResult(bool is_layout);

  // Fill
  void Fill(LayoutState& layout_state);
  void FillToEnd(LayoutState& layout_state);
  void FillToStart(LayoutState& layout_state);
  void LayoutChunkToEnd(int current_index, LayoutState& layout_state,
                        bool skip_bind);
  float CalculateCrossAxisPosition(const ItemHolder* item_holder);
  float CalculateMainAxisPosition(ItemHolder* item_holder,
                                  LayoutState& layout_state);
  // Detect whether this item_holder intersects current visible area.
  bool IntersectVisibleArea(const ItemHolder* item_holder) const;
  // Detect whether current trunk left empty space to fill. Both toStart and
  // toEnd.
  int FindNextIndexToFillStart(LayoutState& layout_state) const;
  bool HasRemainSpaceToFillStart(LayoutState& layout_state) const;
  int GetItemIndexBeforeTargetIndex(const std::vector<int>& span_indexes,
                                    int target_index) const;
  bool HasRemainSpaceToFillEnd(int next_valid_item_index,
                               LayoutState& layout_state) const;
  bool CurrentLineHasRemainSpaceToFillEnd(float end_line) const;
  std::vector<SpanItemInfo> GetMaxEndSpanItemInfoForStartLines(
      LayoutState& layout_state) const;
  SpanItemInfo GetMinEndSpanItemInfoForEndLines(
      LayoutState& layout_state) const;

 private:
  std::vector<std::vector<int>> column_indexes_{};
};

}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_UI_COMPONENT_LIST_STAGGERED_GRID_LAYOUT_MANAGER_H_
