// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_CSS_CSS_PROPERTY_ID_H_
#define CORE_RENDERER_CSS_CSS_PROPERTY_ID_H_
// A macro helps to generate property enums and names.
// Warning: You can only add css property into the last line if you want to add
// new css property otherwise it will cause break change! Don't make break
// change!
// AUTO INSERT, DON'T CHANGE IT!

namespace lynx {
namespace tasm {

// This defines the maximum value for CSS Property IDs. The range 0~999 is
// reserved for CSS Property IDs, while values greater than 999 are used for
// other IDs, such as built-in attribute IDs. Defining these ID ranges helps
// prevent conflicts, allowing them to coexist in the map buffer and
// facilitating future data transmission optimizations.
#define CSS_PROPERTY_MAX_ID 999

#define FOREACH_ALL_PROPERTY(V)                                               \
  V(Top, "top", "auto")                                                       \
  V(Left, "left", "auto")                                                     \
  V(Right, "right", "auto")                                                   \
  V(Bottom, "bottom", "auto")                                                 \
  V(Position, "position", "relative")                                         \
  V(BoxSizing, "box-sizing", "auto")                                          \
  V(BackgroundColor, "background-color", "transparent")                       \
  V(BorderLeftColor, "border-left-color", "black")                            \
  V(BorderRightColor, "border-right-color", "black")                          \
  V(BorderTopColor, "border-top-color", "black")                              \
  V(BorderBottomColor, "border-bottom-color", "black")                        \
  V(BorderRadius, "border-radius", "0px")                                     \
  V(BorderTopLeftRadius, "border-top-left-radius", "0px")                     \
  V(BorderBottomLeftRadius, "border-bottom-left-radius", "0px")               \
  V(BorderTopRightRadius, "border-top-right-radius", "0px")                   \
  V(BorderBottomRightRadius, "border-bottom-right-radius", "0px")             \
  V(BorderWidth, "border-width", "0px")                                       \
  V(BorderLeftWidth, "border-left-width", "0px")                              \
  V(BorderRightWidth, "border-right-width", "0px")                            \
  V(BorderTopWidth, "border-top-width", "0px")                                \
  V(BorderBottomWidth, "border-bottom-width", "0px")                          \
  V(Color, "color", "black")                                                  \
  V(Opacity, "opacity", "1")                                                  \
  V(Display, "display", "auto")                                               \
  V(Overflow, "overflow", "hidden")                                           \
  V(Height, "height", "auto")                                                 \
  V(Width, "width", "auto")                                                   \
  V(MaxWidth, "max-width", "auto")                                            \
  V(MinWidth, "min-width", "auto")                                            \
  V(MaxHeight, "max-height", "auto")                                          \
  V(MinHeight, "min-height", "auto")                                          \
  V(Padding, "padding", "0px")                                                \
  V(PaddingLeft, "padding-left", "0px")                                       \
  V(PaddingRight, "padding-right", "0px")                                     \
  V(PaddingTop, "padding-top", "0px")                                         \
  V(PaddingBottom, "padding-bottom", "0px")                                   \
  V(Margin, "margin", "0px")                                                  \
  V(MarginLeft, "margin-left", "0px")                                         \
  V(MarginRight, "margin-right", "0px")                                       \
  V(MarginTop, "margin-top", "0px")                                           \
  V(MarginBottom, "margin-bottom", "0px")                                     \
  V(WhiteSpace, "white-space", "normal")                                      \
  V(LetterSpacing, "letter-spacing", "0px")                                   \
  V(TextAlign, "text-align", "start")                                         \
  V(LineHeight, "line-height", "")                                            \
  V(TextOverflow, "text-overflow", "clip")                                    \
  V(FontSize, "font-size", "medium")                                          \
  V(FontWeight, "font-weight", "normal")                                      \
  V(Flex, "flex", "0")                                                        \
  V(FlexGrow, "flex-grow", "0")                                               \
  V(FlexShrink, "flex-shrink", "1")                                           \
  V(FlexBasis, "flex-basis", "auto")                                          \
  V(FlexDirection, "flex-direction", "row")                                   \
  V(FlexWrap, "flex-wrap", "nowrap")                                          \
  V(AlignItems, "align-items", "stretch")                                     \
  V(AlignSelf, "align-self", "stretch")                                       \
  V(AlignContent, "align-content", "stretch")                                 \
  V(JustifyContent, "justify-content", "stretch")                             \
  V(Background, "background", "transparent, transparent")                     \
  V(BorderColor, "border-color", "black")                                     \
  V(FontFamily, "font-family", "")                                            \
  V(FontStyle, "font-style", "normal")                                        \
  V(Transform, "transform", "")                                               \
  V(Animation, "animation", "")                                               \
  V(AnimationName, "animation-name", "")                                      \
  V(AnimationDuration, "animation-duration", "")                              \
  V(AnimationTimingFunction, "animation-timing-function", "linear")           \
  V(AnimationDelay, "animation-delay", "0s")                                  \
  V(AnimationIterationCount, "animation-iteration-count", "1")                \
  V(AnimationDirection, "animation-direction", "normal")                      \
  V(AnimationFillMode, "animation-fill-mode", "none")                         \
  V(AnimationPlayState, "animation-play-state", "running")                    \
  V(LineSpacing, "line-spacing", "0px")                                       \
  V(BorderStyle, "border-style", "solid")                                     \
  V(Order, "order", "0")                                                      \
  V(BoxShadow, "box-shadow", "")                                              \
  V(TransformOrigin, "transform-origin", "")                                  \
  V(LinearOrientation, "linear-orientation", "vertical")                      \
  V(LinearWeightSum, "linear-weight-sum", "0")                                \
  V(LinearWeight, "linear-weight", "0")                                       \
  V(LinearGravity, "linear-gravity", "none")                                  \
  V(LinearLayoutGravity, "linear-layout-gravity", "none")                     \
  V(LayoutAnimationCreateDuration, "layout-animation-create-duration", "0s")  \
  V(LayoutAnimationCreateTimingFunction,                                      \
    "layout-animation-create-timing-function", "linear")                      \
  V(LayoutAnimationCreateDelay, "layout-animation-create-delay", "0s")        \
  V(LayoutAnimationCreateProperty, "layout-animation-create-property",        \
    "opacity")                                                                \
  V(LayoutAnimationDeleteDuration, "layout-animation-delete-duration", "0s")  \
  V(LayoutAnimationDeleteTimingFunction,                                      \
    "layout-animation-delete-timing-function", "linear")                      \
  V(LayoutAnimationDeleteDelay, "layout-animation-delete-delay", "0s")        \
  V(LayoutAnimationDeleteProperty, "layout-animation-delete-property",        \
    "opacity")                                                                \
  V(LayoutAnimationUpdateDuration, "layout-animation-update-duration", "0s")  \
  V(LayoutAnimationUpdateTimingFunction,                                      \
    "layout-animation-update-timing-function", "linear")                      \
  V(LayoutAnimationUpdateDelay, "layout-animation-update-delay", "0s")        \
  V(AdaptFontSize, "adapt-font-size", "0")                                    \
  V(AspectRatio, "aspect-ratio", "")                                          \
  V(TextDecoration, "text-decoration", "")                                    \
  V(TextShadow, "text-shadow", "")                                            \
  V(BackgroundImage, "background-image", "")                                  \
  V(BackgroundPosition, "background-position", "")                            \
  V(BackgroundOrigin, "background-origin", "border-box")                      \
  V(BackgroundRepeat, "background-repeat", "no-repeat")                       \
  V(BackgroundSize, "background-size", "")                                    \
  V(Border, "border", "")                                                     \
  V(Visibility, "visibility", "visible")                                      \
  V(BorderRight, "border-right", "")                                          \
  V(BorderLeft, "border-left", "")                                            \
  V(BorderTop, "border-top", "")                                              \
  V(BorderBottom, "border-bottom", "")                                        \
  V(Transition, "transition", "")                                             \
  V(TransitionProperty, "transition-property", "")                            \
  V(TransitionDuration, "transition-duration", "")                            \
  V(TransitionDelay, "transition-delay", "")                                  \
  V(TransitionTimingFunction, "transition-timing-function", "")               \
  V(Content, "content", "")                                                   \
  V(BorderLeftStyle, "border-left-style", "")                                 \
  V(BorderRightStyle, "border-right-style", "")                               \
  V(BorderTopStyle, "border-top-style", "")                                   \
  V(BorderBottomStyle, "border-bottom-style", "")                             \
  V(ImplicitAnimation, "implicit-animation", "true")                          \
  V(OverflowX, "overflow-x", "hidden")                                        \
  V(OverflowY, "overflow-y", "hidden")                                        \
  V(WordBreak, "word-break", "normal")                                        \
  V(BackgroundClip, "background-clip", "border-box")                          \
  V(Outline, "outline", "medium none black")                                  \
  V(OutlineColor, "outline-color", "black")                                   \
  V(OutlineStyle, "outline-style", "black")                                   \
  V(OutlineWidth, "outline-width", "medium")                                  \
  V(VerticalAlign, "vertical-align", "default")                               \
  V(CaretColor, "caret-color", "auto")                                        \
  V(Direction, "direction", "normal")                                         \
  V(RelativeId, "relative-id", "-1")                                          \
  V(RelativeAlignTop, "relative-align-top", "-1")                             \
  V(RelativeAlignRight, "relative-align-right", "-1")                         \
  V(RelativeAlignBottom, "relative-align-bottom", "-1")                       \
  V(RelativeAlignLeft, "relative-align-left", "-1")                           \
  V(RelativeTopOf, "relative-top-of", "-1")                                   \
  V(RelativeRightOf, "relative-right-of", "-1")                               \
  V(RelativeBottomOf, "relative-bottom-of", "-1")                             \
  V(RelativeLeftOf, "relative-left-of", "-1")                                 \
  V(RelativeLayoutOnce, "relative-layout-once", "true")                       \
  V(RelativeCenter, "relative-center", "none")                                \
  V(EnterTransitionName, "enter-transition-name", "")                         \
  V(ExitTransitionName, "exit-transition-name", "")                           \
  V(PauseTransitionName, "pause-transition-name", "")                         \
  V(ResumeTransitionName, "resume-transition-name", "")                       \
  V(FlexFlow, "flex-flow", "row nowrap")                                      \
  V(ZIndex, "z-index", "0")                                                   \
  V(TextDecorationColor, "text-decoration-color", "black")                    \
  V(LinearCrossGravity, "linear-cross-gravity", "none")                       \
  V(MarginInlineStart, "margin-inline-start", "0px")                          \
  V(MarginInlineEnd, "margin-inline-end", "0px")                              \
  V(PaddingInlineStart, "padding-inline-start", "0px")                        \
  V(PaddingInlineEnd, "padding-inline-end", "0px")                            \
  V(BorderInlineStartColor, "border-inline-start-color", "black")             \
  V(BorderInlineEndColor, "border-inline-end-color", "black")                 \
  V(BorderInlineStartWidth, "border-inline-start-width", "0px")               \
  V(BorderInlineEndWidth, "border-inline-end-width", "0px")                   \
  V(BorderInlineStartStyle, "border-inline-start-style", "")                  \
  V(BorderInlineEndStyle, "border-inline-end-style", "")                      \
  V(BorderStartStartRadius, "border-start-start-radius", "0px")               \
  V(BorderEndStartRadius, "border-end-start-radius", "0px")                   \
  V(BorderStartEndRadius, "border-start-end-radius", "0px")                   \
  V(BorderEndEndRadius, "border-end-end-radius", "0px")                       \
  V(RelativeAlignInlineStart, "relative-align-inline-start", "-1")            \
  V(RelativeAlignInlineEnd, "relative-align-inline-end", "-1")                \
  V(RelativeInlineStartOf, "relative-inline-start-of", "-1")                  \
  V(RelativeInlineEndOf, "relative-inline-end-of", "-1")                      \
  V(InsetInlineStart, "inset-inline-start", "0px")                            \
  V(InsetInlineEnd, "inset-inline-end", "0px")                                \
  V(MaskImage, "mask-image", "")                                              \
  V(GridTemplateColumns, "grid-template-columns", "")                         \
  V(GridTemplateRows, "grid-template-rows", "")                               \
  V(GridAutoColumns, "grid-auto-columns", "")                                 \
  V(GridAutoRows, "grid-auto-rows", "")                                       \
  V(GridColumnSpan, "grid-column-span", "")                                   \
  V(GridRowSpan, "grid-row-span", "")                                         \
  V(GridColumnStart, "grid-column-start", "")                                 \
  V(GridColumnEnd, "grid-column-end", "")                                     \
  V(GridRowStart, "grid-row-start", "")                                       \
  V(GridRowEnd, "grid-row-end", "")                                           \
  V(GridColumnGap, "grid-column-gap", "")                                     \
  V(GridRowGap, "grid-row-gap", "")                                           \
  V(JustifyItems, "justify-items", "stretch")                                 \
  V(JustifySelf, "justify-self", "auto")                                      \
  V(GridAutoFlow, "grid-auto-flow", "row")                                    \
  V(Filter, "filter", "")                                                     \
  V(ListMainAxisGap, "list-main-axis-gap", "0px")                             \
  V(ListCrossAxisGap, "list-cross-axis-gap", "0px")                           \
  V(LinearDirection, "linear-direction", "column")                            \
  V(Perspective, "perspective", "none")                                       \
  V(Cursor, "cursor", "default")                                              \
  V(TextIndent, "text-indent", "0px")                                         \
  V(ClipPath, "clip-path", "")                                                \
  V(TextStroke, "text-stroke", "0px black")                                   \
  V(TextStrokeWidth, "text-stroke-width", "0px")                              \
  V(TextStrokeColor, "text-stroke-color", "black")                            \
  V(XAutoFontSize, "-x-auto-font-size", "false")                              \
  V(XAutoFontSizePresetSizes, "-x-auto-font-size-preset-sizes", "")           \
  V(Mask, "mask", "")                                                         \
  V(MaskRepeat, "mask-repeat", "")                                            \
  V(MaskPosition, "mask-position", "")                                        \
  V(MaskClip, "mask-clip", "")                                                \
  V(MaskOrigin, "mask-origin", "")                                            \
  V(MaskSize, "mask-size", "")                                                \
  V(Gap, "gap", "0px")                                                        \
  V(ColumnGap, "column-gap", "0px")                                           \
  V(RowGap, "row-gap", "0px")                                                 \
  V(ImageRendering, "image-rendering", "auto")                                \
  V(Hyphens, "hyphens", "manual")                                             \
  V(XAppRegion, "-x-app-region", "none")                                      \
  V(XAnimationColorInterpolation, "-x-animation-color-interpolation", "auto") \
  V(XHandleSize, "-x-handle-size", "0px")                                     \
  V(XHandleColor, "-x-handle-color", "transparent")                           \
  V(OffsetDistance, "offset-distance", "0")                                   \
  V(OffsetPath, "offset-path", "")                                            \
  V(OffsetRotate, "offset-rotate", "")

#define DECLARE_PROPERTY_NAME(name, c, value) \
  static constexpr const char kPropertyName##name[] = c;
FOREACH_ALL_PROPERTY(DECLARE_PROPERTY_NAME)
#undef DECLARE_PROPERTY_NAME

enum CSSPropertyID : int32_t {
  kPropertyStart = 0,
#define DECLARE_PROPERTY_ID(name, c, value) kPropertyID##name,
  FOREACH_ALL_PROPERTY(DECLARE_PROPERTY_ID)
#undef DECLARE_PROPERTY_ID
      kPropertyEnd
};
}  // namespace tasm
}  // namespace lynx
#endif  // CORE_RENDERER_CSS_CSS_PROPERTY_ID_H_
// AUTO INSERT END, DON'T CHANGE IT!
