// Copyright 2019 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_UI_WRAPPER_LAYOUT_LAYOUT_NODE_H_
#define CORE_RENDERER_UI_WRAPPER_LAYOUT_LAYOUT_NODE_H_

#include <memory>
#include <set>

#include "base/include/string/string_utils.h"
#include "base/include/vector.h"
#include "core/public/layout_node_value.h"
#include "core/renderer/css/computed_css_style.h"
#include "core/renderer/css/css_property.h"
#include "core/renderer/starlight/layout/layout_global.h"
#include "core/renderer/starlight/layout/layout_object.h"
#include "core/renderer/starlight/types/layout_measurefunc.h"
#include "core/renderer/utils/base/base_def.h"

namespace lynx {
namespace tasm {

#define FOREACH_LAYOUT_PROPERTY(V)    \
  V(Top, LAYOUT_ONLY)                 \
  V(Left, LAYOUT_ONLY)                \
  V(Right, LAYOUT_ONLY)               \
  V(Bottom, LAYOUT_ONLY)              \
  V(Width, LAYOUT_ONLY)               \
  V(MaxWidth, LAYOUT_ONLY)            \
  V(MinWidth, LAYOUT_ONLY)            \
  V(Height, LAYOUT_ONLY)              \
  V(MaxHeight, LAYOUT_ONLY)           \
  V(MinHeight, LAYOUT_ONLY)           \
  V(PaddingLeft, LAYOUT_ONLY)         \
  V(PaddingRight, LAYOUT_ONLY)        \
  V(PaddingTop, LAYOUT_ONLY)          \
  V(PaddingBottom, LAYOUT_ONLY)       \
  V(MarginLeft, LAYOUT_ONLY)          \
  V(MarginRight, LAYOUT_ONLY)         \
  V(MarginTop, LAYOUT_ONLY)           \
  V(MarginBottom, LAYOUT_ONLY)        \
  V(BorderLeftWidth, LAYOUT_WANTED)   \
  V(BorderRightWidth, LAYOUT_WANTED)  \
  V(BorderTopWidth, LAYOUT_WANTED)    \
  V(BorderBottomWidth, LAYOUT_WANTED) \
  V(FlexBasis, LAYOUT_ONLY)           \
  V(FlexGrow, LAYOUT_ONLY)            \
  V(FlexShrink, LAYOUT_ONLY)          \
  V(LinearWeightSum, LAYOUT_ONLY)     \
  V(LinearWeight, LAYOUT_ONLY)        \
  V(AspectRatio, LAYOUT_ONLY)         \
  V(RelativeId, LAYOUT_ONLY)          \
  V(RelativeAlignTop, LAYOUT_ONLY)    \
  V(RelativeAlignRight, LAYOUT_ONLY)  \
  V(RelativeAlignBottom, LAYOUT_ONLY) \
  V(RelativeAlignLeft, LAYOUT_ONLY)   \
  V(RelativeTopOf, LAYOUT_ONLY)       \
  V(RelativeRightOf, LAYOUT_ONLY)     \
  V(RelativeBottomOf, LAYOUT_ONLY)    \
  V(RelativeLeftOf, LAYOUT_ONLY)      \
  V(RelativeLayoutOnce, LAYOUT_ONLY)  \
  V(Order, LAYOUT_ONLY)               \
  V(Flex, LAYOUT_ONLY)                \
  V(BorderWidth, LAYOUT_WANTED)       \
  V(Padding, LAYOUT_ONLY)             \
  V(Margin, LAYOUT_ONLY)              \
  V(Border, LAYOUT_WANTED)            \
  V(BorderRight, LAYOUT_WANTED)       \
  V(BorderLeft, LAYOUT_WANTED)        \
  V(BorderTop, LAYOUT_WANTED)         \
  V(BorderBottom, LAYOUT_WANTED)      \
  V(Flex, LAYOUT_ONLY)                \
  V(FlexDirection, LAYOUT_ONLY)       \
  V(FlexWrap, LAYOUT_ONLY)            \
  V(AlignItems, LAYOUT_ONLY)          \
  V(AlignSelf, LAYOUT_ONLY)           \
  V(AlignContent, LAYOUT_ONLY)        \
  V(JustifyContent, LAYOUT_ONLY)      \
  V(LinearOrientation, LAYOUT_ONLY)   \
  V(LinearLayoutGravity, LAYOUT_ONLY) \
  V(LinearGravity, LAYOUT_ONLY)       \
  V(LinearCrossGravity, LAYOUT_ONLY)  \
  V(RelativeCenter, LAYOUT_ONLY)      \
  V(Position, LAYOUT_ONLY)            \
  V(Display, LAYOUT_ONLY)             \
  V(BoxSizing, LAYOUT_ONLY)           \
  V(Content, LAYOUT_ONLY)             \
  V(Direction, LAYOUT_WANTED)         \
  V(GridTemplateColumns, LAYOUT_ONLY) \
  V(GridTemplateRows, LAYOUT_ONLY)    \
  V(GridAutoColumns, LAYOUT_ONLY)     \
  V(GridAutoRows, LAYOUT_ONLY)        \
  V(GridColumnSpan, LAYOUT_ONLY)      \
  V(GridRowSpan, LAYOUT_ONLY)         \
  V(GridColumnStart, LAYOUT_ONLY)     \
  V(GridColumnEnd, LAYOUT_ONLY)       \
  V(GridRowStart, LAYOUT_ONLY)        \
  V(GridRowEnd, LAYOUT_ONLY)          \
  V(GridColumnGap, LAYOUT_ONLY)       \
  V(GridRowGap, LAYOUT_ONLY)          \
  V(JustifyItems, LAYOUT_ONLY)        \
  V(JustifySelf, LAYOUT_ONLY)         \
  V(GridAutoFlow, LAYOUT_ONLY)        \
  V(ListCrossAxisGap, LAYOUT_WANTED)  \
  V(LinearDirection, LAYOUT_ONLY)     \
  V(VerticalAlign, LAYOUT_WANTED)     \
  V(Gap, LAYOUT_ONLY)                 \
  V(ColumnGap, LAYOUT_ONLY)           \
  V(RowGap, LAYOUT_ONLY)

class LayoutContext;

enum ConsumptionStatus { LAYOUT_ONLY = 0, LAYOUT_WANTED = 1, SKIP = 2 };

class LayoutNode {
 public:
  LayoutNode(int id, const starlight::LayoutConfigs& layout_configs,
             const tasm::LynxEnvConfig& envs,
             const starlight::ComputedCSSStyle& init_style);

  static ConsumptionStatus ConsumptionTest(CSSPropertyID id);
  inline static bool IsLayoutOnly(CSSPropertyID id) {
    return ConsumptionTest(id) == LAYOUT_ONLY;
  }
  inline static bool IsLayoutWanted(CSSPropertyID id) {
    return ConsumptionTest(id) == LAYOUT_WANTED;
  }

  // interface of  inline view
  FloatSize UpdateMeasureByPlatform(const starlight::Constraints& constraints,
                                    bool final_measure);
  void AlignmentByPlatform(float offset_top, float offset_left);
  void CalculateLayout(const SLNodeSet* fixed_node_set = nullptr);
  void CalculateLayoutWithConstraints(
      starlight::Constraints& constraints,
      const SLNodeSet* fixed_node_set = nullptr);
  void SetMeasureFunc(std::unique_ptr<MeasureFunc> measure_func);
  void InsertNode(LayoutNode* child, int index = -1);
  LayoutNode* RemoveNodeAtIndex(unsigned int index);
  void MoveNode(LayoutNode* child, int from_index, unsigned int to_index);
  void ConsumeFontSize(double cur_node_font_size, double root_node_font_size,
                       double font_scale);
  void ConsumeStyle(CSSPropertyID id, const tasm::CSSValue& value,
                    bool reset = false);
  void ConsumeAttribute(const starlight::LayoutAttribute key,
                        const lepus::Value& value, bool reset = false);

  inline LayoutNode* parent() const { return parent_; }
  inline SLNode* slnode() { return &sl_node_; }
  inline const auto& children() { return children_; }
  inline bool is_virtual() { return type_ & LayoutNodeType::VIRTUAL; }
  inline bool is_common() { return type_ & LayoutNodeType::COMMON; }
  inline bool is_custom() { return type_ & LayoutNodeType::CUSTOM; }
  inline bool is_inline_view() { return type_ & LayoutNodeType::INLINE; };
  inline MeasureFunc* measure_func() { return measure_func_.get(); };
  inline int id() { return id_; }
  inline bool is_list_container() const { return is_list_container_; }
  void set_type(LayoutNodeType type);
  bool IsDirty();
  void MarkDirty();
  void MarkDirtyAndRequestLayout();
  void CleanDirty();
  void MarkUpdated();
  void UpdateLynxEnv(const tasm::LynxEnvConfig& config);
  LayoutNode* FindNonVirtualNode();
  LayoutNode* FindNextNonVirtualChild(size_t before_index) const;

  void SetTag(const base::String& tag);
  starlight::ComputedCSSStyle* GetCSSMutableStyle() { return css_style_.get(); }

 protected:
  int id_;
  LayoutNodeType type_;

  bool is_dirty_{false};
  // Whether node is a native list element which needs to invoke
  // OnListElementUpdated() callback after layout.
  bool is_list_container_{false};

  base::InlineVector<LayoutNode*, starlight::kChildrenInlineVectorSize>
      children_;
  LayoutNode* parent_ = nullptr;
  std::unique_ptr<MeasureFunc> measure_func_;

  base::String tag_;
  std::unique_ptr<starlight::ComputedCSSStyle> css_style_;

  SLNode sl_node_;

 private:
  LayoutNode(const LayoutNode&) = delete;
  LayoutNode& operator=(const LayoutNode&) = delete;
  void MarkDirtyInternal(bool request_layout);
};

}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_UI_WRAPPER_LAYOUT_LAYOUT_NODE_H_
