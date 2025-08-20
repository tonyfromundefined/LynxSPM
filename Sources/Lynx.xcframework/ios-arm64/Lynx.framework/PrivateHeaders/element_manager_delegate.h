// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_DOM_ELEMENT_MANAGER_DELEGATE_H_
#define CORE_RENDERER_DOM_ELEMENT_MANAGER_DELEGATE_H_

#include <string>

#include "core/template_bundle/lynx_template_bundle.h"

namespace lynx {
namespace tasm {

class FrameElement;

/**
 * ElementManagerDelegate provides APIs which ElementManager needs to call but
 * not implemented in ElementManager.
 */
class ElementManagerDelegate {
 public:
  ElementManagerDelegate() = default;
  virtual ~ElementManagerDelegate() = default;

  /**
   * APIs to load bundle for frame and manage frame element.
   */
  // load bundle for frame element
  virtual void LoadFrameBundle(const std::string &src,
                               FrameElement *element) = 0;
  // callback for frame bundle loaded
  virtual void DidFrameBundleLoaded(const std::string &src,
                                    LynxTemplateBundle bundle) = 0;
  // Call for frame removed.
  virtual void OnFrameRemoved(FrameElement *element) = 0;
};

}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_DOM_ELEMENT_MANAGER_DELEGATE_H_
