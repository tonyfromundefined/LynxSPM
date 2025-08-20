// Copyright 2019 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#ifndef CORE_RENDERER_CSS_CSS_VALUE_H_
#define CORE_RENDERER_CSS_CSS_VALUE_H_

#include <memory>
#include <string>
#include <utility>

#include "base/include/base_export.h"
#include "core/renderer/starlight/style/css_type.h"
#include "core/runtime/vm/lepus/array.h"
#include "core/runtime/vm/lepus/lepus_value.h"

namespace lynx {
namespace tasm {
enum class CSSValuePattern : uint8_t {
  EMPTY = 0,
  STRING = 1,
  NUMBER = 2,
  BOOLEAN = 3,
  ENUM = 4,
  PX = 5,
  RPX = 6,
  EM = 7,
  REM = 8,
  VH = 9,
  VW = 10,
  PERCENT = 11,
  CALC = 12,
  ENV = 13,
  ARRAY = 14,
  MAP = 15,
  PPX = 16,
  INTRINSIC = 17,
  SP = 18,
  FR = 19,
  COUNT = 20,
};

enum class CSSValueType : uint8_t {
  DEFAULT = 0,
  VARIABLE = 1,
};

enum class CSSFunctionType : uint8_t {
  DEFAULT = 0,
  REPEAT = 1,
  MINMAX = 2,
};

class BASE_EXPORT_FOR_DEVTOOL CSSValue {
 public:
  explicit CSSValue(CSSValuePattern pattern = CSSValuePattern::STRING)
      : pattern_(pattern), type_(CSSValueType::DEFAULT) {}
  explicit CSSValue(const lepus::Value& value,
                    CSSValuePattern pattern = CSSValuePattern::STRING,
                    CSSValueType type = CSSValueType::DEFAULT)
      : value_(value), pattern_(pattern), type_(type) {}
  CSSValue(const lepus::Value& value, CSSValuePattern pattern,
           CSSValueType type, const base::String& default_val)
      : value_(value),
        default_value_(default_val),
        pattern_(pattern),
        type_(type) {}
  CSSValue(const lepus::Value& value, CSSValuePattern pattern,
           CSSValueType type, const base::String& default_val,
           const lepus::Value& default_value_map_opt)
      : value_(value),
        default_value_(default_val),
        default_value_map_opt_(new lepus::Value(default_value_map_opt)),
        pattern_(pattern),
        type_(type) {}
  explicit CSSValue(fml::RefPtr<lepus::CArray>&& array,
                    CSSValuePattern pattern = CSSValuePattern::ARRAY)
      : value_(std::move(array)),
        pattern_(pattern),
        type_(CSSValueType::DEFAULT) {}

  enum CreateEnumTag { kCreateEnumTag };
  CSSValue(int enum_value, CreateEnumTag)
      : value_(enum_value),
        pattern_(CSSValuePattern::ENUM),
        type_(CSSValueType::DEFAULT) {}

  enum CreateNumberTag { kCreateNumberTag };
  CSSValue(double value, CreateNumberTag)
      : value_(value),
        pattern_(CSSValuePattern::NUMBER),
        type_(CSSValueType::DEFAULT) {}

  CSSValue(const CSSValue& other)
      : value_(other.value_),
        default_value_(other.default_value_),
        pattern_(other.pattern_),
        type_(other.type_) {
    if (other.default_value_map_opt_) {
      default_value_map_opt_ =
          std::make_unique<lepus::Value>(*other.default_value_map_opt_);
    }
  }

  CSSValue& operator=(const CSSValue& other) {
    if (this == &other) {
      return *this;
    }
    this->value_ = other.value_;
    this->default_value_ = other.default_value_;
    if (other.default_value_map_opt_) {
      this->default_value_map_opt_ =
          std::make_unique<lepus::Value>(*other.default_value_map_opt_);
    } else {
      this->default_value_map_opt_ = nullptr;
    }
    this->pattern_ = other.pattern_;
    this->type_ = other.type_;
    return *this;
  }

  CSSValue(CSSValue&& other) = default;
  CSSValue& operator=(CSSValue&& other) = default;

  template <typename T>
  T GetEnum() const {
    return (T)AsNumber();
  }

  static CSSValue Empty() { return CSSValue(CSSValuePattern::EMPTY); }

  static CSSValue MakeEnum(int enumType) {
    return CSSValue(lepus::Value(enumType), CSSValuePattern::ENUM);
  }

  lepus::Value& GetValue() const { return value_; }
  CSSValuePattern GetPattern() const { return pattern_; }
  CSSValueType GetValueType() const { return type_; }
  base::String& GetDefaultValue() const { return default_value_; }
  std::unique_ptr<lepus::Value>& GetDefaultValueMapOpt() const {
    return default_value_map_opt_;
  }

  void SetValue(const lepus::Value& value) { value_ = value; }
  void SetValue(lepus::Value&& value) { value_ = std::move(value); }
  void SetPattern(CSSValuePattern pattern) { pattern_ = pattern; }
  void SetValueAndPattern(const lepus::Value& value, CSSValuePattern pattern) {
    value_ = value;
    pattern_ = pattern;
    type_ = CSSValueType::DEFAULT;
  }

  void SetType(CSSValueType type) { type_ = type; }
  void SetDefaultValue(base::String default_val) {
    default_value_ = std::move(default_val);
  }
  void SetDefaultValueMap(lepus::Value default_value_map) {
    default_value_map_opt_ = nullptr;
    if (default_value_map != lepus::Value()) {
      default_value_map_opt_ =
          std::make_unique<lepus::Value>(std::move(default_value_map));
    }
  }

  void SetArray(fml::RefPtr<lepus::CArray>&& array) {
    value_.SetArray(std::move(array));
    pattern_ = CSSValuePattern::ARRAY;
    type_ = CSSValueType::DEFAULT;
  }

  void SetBoolean(bool value) {
    value_.SetBool(value);
    pattern_ = CSSValuePattern::BOOLEAN;
    type_ = CSSValueType::DEFAULT;
  }

  void SetNumber(double num) {
    value_.SetNumber(num);
    pattern_ = CSSValuePattern::NUMBER;
    type_ = CSSValueType::DEFAULT;
  }

  void SetNumber(int num, CSSValuePattern pattern) {
    value_.SetNumber(num);
    pattern_ = pattern;
    type_ = CSSValueType::DEFAULT;
  }

  void SetEnum(int value) {
    value_.SetNumber(value);
    pattern_ = CSSValuePattern::ENUM;
    type_ = CSSValueType::DEFAULT;
  }

  bool IsVariable() const { return type_ == CSSValueType::VARIABLE; }
  bool IsString() const { return pattern_ == CSSValuePattern::STRING; }
  bool IsNumber() const { return pattern_ == CSSValuePattern::NUMBER; }
  bool IsBoolean() const { return pattern_ == CSSValuePattern::BOOLEAN; }
  bool IsEnum() const { return pattern_ == CSSValuePattern::ENUM; }
  bool IsPx() const { return pattern_ == CSSValuePattern::PX; }
  bool IsPPx() const { return pattern_ == CSSValuePattern::PPX; }
  bool IsRpx() const { return pattern_ == CSSValuePattern::RPX; }
  bool IsEm() const { return pattern_ == CSSValuePattern::EM; }
  bool IsRem() const { return pattern_ == CSSValuePattern::REM; }
  bool IsVh() const { return pattern_ == CSSValuePattern::VH; }
  bool IsVw() const { return pattern_ == CSSValuePattern::VW; }
  bool IsPercent() const { return pattern_ == CSSValuePattern::PERCENT; }
  bool IsCalc() const { return pattern_ == CSSValuePattern::CALC; }
  bool IsArray() const { return pattern_ == CSSValuePattern::ARRAY; }
  bool IsMap() const { return pattern_ == CSSValuePattern::MAP; }
  bool IsEmpty() const { return pattern_ == CSSValuePattern::EMPTY; }
  bool IsEnv() const { return pattern_ == CSSValuePattern::ENV; }
  bool IsIntrinsic() const { return pattern_ == CSSValuePattern::INTRINSIC; }
  bool IsSp() const { return pattern_ == CSSValuePattern::SP; }

  double AsNumber() const { return value_.Number(); }

  const std::string& AsString() const { return value_.StdString(); }

  bool AsBool() const;

  std::string AsJsonString() const;

  friend bool operator==(const CSSValue& left, const CSSValue& right) {
    return left.pattern_ == right.pattern_ && left.value_ == right.value_;
  }

  friend bool operator!=(const CSSValue& left, const CSSValue& right) {
    return !(left == right);
  }

 private:
  mutable lepus::Value value_;
  mutable base::String default_value_;
  mutable std::unique_ptr<lepus::Value> default_value_map_opt_;
  mutable CSSValuePattern pattern_;
  mutable CSSValueType type_;
};
}  // namespace tasm
}  // namespace lynx

#endif  // CORE_RENDERER_CSS_CSS_VALUE_H_
