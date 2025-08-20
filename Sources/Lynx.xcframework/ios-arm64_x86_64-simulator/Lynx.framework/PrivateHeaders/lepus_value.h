// Copyright 2019 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
#ifndef CORE_RUNTIME_VM_LEPUS_LEPUS_VALUE_H_
#define CORE_RUNTIME_VM_LEPUS_LEPUS_VALUE_H_

#include <cstring>
#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "base/include/base_export.h"
#include "base/include/closure.h"
#include "base/include/fml/memory/ref_counted.h"
#include "base/include/log/logging.h"
#include "base/include/value/base_string.h"
#include "base/include/vector.h"
#include "core/runtime/vm/lepus/lynx_value_extended.h"
#include "core/runtime/vm/lepus/marco.h"
#include "core/runtime/vm/lepus/ref_type.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "base/include/value/lynx_value_types.h"
#ifdef __cplusplus
}
#endif

namespace lynx {
namespace lepus {

class Value;

using LepusValueIterator =
    base::MoveOnlyClosure<void, const lepus::Value&, const lepus::Value&>;

using ExtendedValueIteratorCallback =
    base::MoveOnlyClosure<void, lynx_api_env, const lynx_value&,
                          const lynx_value&>;

#define NormalNumberType(V) \
  V(Double, double)         \
  V(Int32, int32_t)         \
  V(UInt32, uint32_t)       \
  V(UInt64, uint64_t)

#define NumberType(V) NormalNumberType(V) V(Int64, int64_t)

/*
LepusNG will add more types:
  1. JSValue
    It include:  type_ > Value_TypeCount || type_ < 0
    It make lepus::Value can hold quickjs JSValue type
*/
enum ValueType {
  Value_Nil,
  Value_Double,
  Value_Bool,
  Value_String,
  Value_Table,
  Value_Array,
  Value_Closure,
  Value_CFunction,
  Value_CPointer,
  Value_Int32,
  Value_Int64,
  Value_UInt32,
  Value_UInt64,
  Value_NaN,
  Value_CDate,
  Value_RegExp,
  Value_JSObject,
  Value_Undefined,
  Value_ByteArray,
  Value_RefCounted,
  // Value_TypeCount is used for encoding jsvalue tag,
  // Adding a new Value_type needs to be inserted before 'Value_TypeCount'
  Value_PrimJsValue,
  Value_FunctionTable,
  Value_TypeCount,
};

class Context;
class CArray;
class CDate;
class Dictionary;
class Closure;
class RegExp;
class ByteArray;
class RefCounted;
class LEPUSObject;
class BuiltinFunctionTable;

typedef Value (*CFunction)(Context*);

class BASE_EXPORT_FOR_DEVTOOL Value {
 private:
  lynx_value value_;
  lynx_api_env env_;
  lynx_value_ref value_ref_;

 public:
  explicit Value() { value_.type = lynx_value_null; };

  enum CreateAsUndefinedTag { kCreateAsUndefinedTag };
  explicit Value(CreateAsUndefinedTag);

  Value(const Value& value);
  Value(Value&& value) noexcept;

  explicit Value(const base::String& data);
  explicit Value(base::String&& data);
  explicit Value(const char* val);
  explicit Value(const std::string& str);
  explicit Value(std::string&& str);

  explicit Value(const fml::RefPtr<Dictionary>& data);
  explicit Value(fml::RefPtr<Dictionary>&& data);
  explicit Value(const fml::WeakRefPtr<Dictionary>& data);
  explicit Value(const fml::RefPtr<CArray>& data);
  explicit Value(fml::RefPtr<CArray>&& data);
  explicit Value(const fml::WeakRefPtr<CArray>& data);
  explicit Value(const fml::RefPtr<lepus::LEPUSObject>& data);
  explicit Value(fml::RefPtr<lepus::LEPUSObject>&& data);
  explicit Value(const fml::RefPtr<lepus::ByteArray>& data);
  explicit Value(fml::RefPtr<lepus::ByteArray>&& data);
  explicit Value(const fml::RefPtr<lepus::RefCounted>& data);
  explicit Value(fml::RefPtr<lepus::RefCounted>&& data);
  explicit Value(const fml::RefPtr<Closure>& data);
  explicit Value(fml::RefPtr<Closure>&& data);
  explicit Value(const fml::RefPtr<CDate>& data);
  explicit Value(fml::RefPtr<CDate>&& data);
  explicit Value(const fml::RefPtr<RegExp>& data);
  explicit Value(fml::RefPtr<RegExp>&& data);

  explicit Value(bool val);
  explicit Value(void* data);
  explicit Value(CFunction val);
  explicit Value(BuiltinFunctionTable* data);
  explicit Value(bool for_nan, bool val);
  explicit Value(lynx_value&& value);
  Value(lynx_api_env env, int64_t val, int32_t tag);
  Value(lynx_api_env env, const lynx_value& value);
  Value(lynx_api_env env, lynx_value&& value);

  inline bool IsCDate() const {
    return value_.type == lynx_value_object &&
           value_.tag == static_cast<int32_t>(CustomRefCountedType::kCDate);
  }
  inline bool IsRegExp() const {
    return value_.type == lynx_value_object &&
           value_.tag == static_cast<int32_t>(CustomRefCountedType::kRegExp);
  }

  void SetClosure(const fml::RefPtr<lepus::Closure>&);
  void SetClosure(fml::RefPtr<lepus::Closure>&&);
  void SetRegExp(const fml::RefPtr<lepus::RegExp>&);
  void SetRegExp(fml::RefPtr<lepus::RegExp>&&);
  void SetDate(const fml::RefPtr<lepus::CDate>&);
  void SetDate(fml::RefPtr<lepus::CDate>&&);

  inline void DupValue() const;
  void FreeValue();

  inline bool IsClosure() const {
    return value_.type == lynx_value_object &&
           value_.tag == static_cast<int32_t>(CustomRefCountedType::kClosure);
  }
  inline bool IsCallable() const { return IsClosure() || IsJSFunction(); }

// add for compile
#define NumberConstructor(name, type) explicit Value(type data);

  NumberType(NumberConstructor)

      explicit Value(uint8_t data);
#undef NumberConstructor

  void SetNumber(double val) {
    FreeValue();
    value_ = {.val_double = val, .type = lynx_value_double};
  }

  void SetNumber(int32_t val) {
    FreeValue();
    value_ = {.val_int32 = val, .type = lynx_value_int32};
  }

  void SetNumber(uint32_t val) {
    FreeValue();
    value_ = {.val_uint32 = val, .type = lynx_value_uint32};
  }

  void SetNumber(int64_t val) {
    FreeValue();
    value_ = {.val_int64 = val, .type = lynx_value_int64};
  }

  void SetNumber(uint64_t val) {
    FreeValue();
    value_ = {.val_uint64 = val, .type = lynx_value_uint64};
  }

  inline ValueType Type() const { return LegacyTypeFromLynxValue(value_); }

  static Value Clone(const Value& src, bool clone_as_jsvalue = false);

  static Value ShallowCopy(const Value& src, bool clone_as_jsvalue = false);

  inline bool IsReference() const {
    return (value_.type >= lynx_value_string &&
            value_.type <= lynx_value_object);
  }
  inline void* Ptr() const { return value_.val_ptr; }

  inline bool IsBool() const {
    return value_.type == lynx_value_bool || IsJSBool();
  }

  inline bool IsString() const {
    return value_.type == lynx_value_string || IsJSString();
  }

  inline bool IsInt64() const {
    return value_.type == lynx_value_int64 || IsJSInteger();
  }

  inline bool IsNumber() const {
    return (value_.type >= lynx_value_double &&
            value_.type <= lynx_value_uint64) ||
           IsJSNumber();
  }

  inline bool IsDouble() const { return value_.type == lynx_value_double; }

  inline bool IsArray() const { return value_.type == lynx_value_array; }

  inline bool IsTable() const { return value_.type == lynx_value_map; }

  inline bool IsObject() const {
    if (IsTable()) return true;
    if (IsJSValue()) return IsJSTable();
    return false;
  }

  inline bool IsArrayOrJSArray() const {
    if (IsArray()) return true;
    if (IsJSValue()) return IsJSArray();
    return false;
  }

  inline bool IsCPointer() const {
    return value_.type == lynx_value_external || IsJSCPointer();
  }

  inline bool IsRefCounted() const {
    return value_.type == lynx_value_object &&
           value_.tag ==
               static_cast<int32_t>(CustomRefCountedType::kRefCounted);
  }

  inline bool IsInt32() const { return value_.type == lynx_value_int32; }
  inline bool IsUInt32() const { return value_.type == lynx_value_uint32; }
  inline bool IsUInt64() const { return value_.type == lynx_value_uint64; }
  inline bool IsNil() const {
    return (value_.type == lynx_value_null) || IsJsNull();
  }
  inline bool IsUndefined() const {
    return value_.type == lynx_value_undefined || IsJSUndefined();
  }
  inline bool IsCFunction() const { return value_.type == lynx_value_function; }
  inline bool IsBuiltinFunctionTable() const {
    return value_.type == lynx_value_function_table;
  }
  inline bool IsJSObject() const {
    return value_.type == lynx_value_object &&
           value_.tag == static_cast<int32_t>(CustomRefCountedType::kJSObject);
  }
  inline bool IsByteArray() const {
    return value_.type == lynx_value_arraybuffer;
  }
  inline bool IsNaN() const { return value_.type == lynx_value_nan; }

  inline bool Bool() const {
    if (value_.type != lynx_value_bool) return !IsFalse();
    return value_.val_bool;
  }
  inline bool NaN() const {
    return value_.type == lynx_value_nan && value_.val_bool;
  }

  double Number() const;

  Value& operator=(const Value& value) {
    Copy(value);
    return *this;
  }
  Value& operator=(Value&& value) noexcept;

#define NumberValue(name, type) type name() const;
  NumberType(NumberValue)
#undef NumberValue

      /// @brief Returns a string view of the internal lepus string
      /// storage. The result is guaranteed to be null terminated.
      std::string_view StringView() const {
    return StdString();
  }

  /// @brief Equivalent to `String().c_str()` but with better performance and
  /// binary size because there is no temporary base::String object generated
  /// although it does not retain the underlying string impl. Use only when C
  /// string is required.
  const char* CString() const { return StdString().c_str(); }

  /// @brief Equivalent to `String().str()` but with better performance and
  /// binary size because there is no temporary base::String object generated
  /// although it does not retain the underlying string impl. Use this function
  /// for most scenarios.
  BASE_EXPORT const std::string& StdString() const;

  /// @Note
  /// If possible, use StringView(), StdString() or CString() instead of this
  /// because this function produce a temporary base::String instance although
  /// it does not retain the underlying ref-counted impl.
  ///
  /// @brief For values representing string, js string, boolean and js boolean
  /// this function returns a base::String instance which does not strong
  /// retains the underlying impl object. You can use the result instance for
  /// its string content safely in synchronous codes and when result is used for
  /// copy or move construction of other base::String instances, the underlying
  /// impl is retained normally by new instances.
  ///
  /// There is only one unsafe case which is assigning result of String()
  /// directly to a variable in asynchronous lambda's capture list.
  /// {
  ///   lepus::Value value;
  ///   do_async([s = value.String()] {
  ///     // s is not retaining the underlying string and is not safe to be used
  ///     // in asynchronous codes.
  ///   });
  /// }
  ///
  /// Instead you should write code like this so that the variable seen by
  /// lambda body retains the string when capture list is formed.
  /// {
  ///   lepus::Value value;
  ///   auto value_str = value.String();  // Not retaining the string
  ///   do_async([value_str] {            // Capture by copy.
  ///     // This value_str is copy constructed from outer value_str.
  ///   });
  /// }
  base::String String() const&;

  /// For rvalue this object, returns base::String which retains the underlying
  /// string impl to avoid dangling pointer. Consider a function which returns
  /// a Value. Without this overload, `s` would be using a dangling string impl.
  ///   static lepus::Value funcA(const char* s) {
  ///      return lepus::Value(s);
  ///   }
  ///   auto s = funcA("asdf").String();
  ///
  /// There is one case which matches this overload but not desired.
  ///   auto s = table_value.GetProperty("a").String();
  /// s would retain the string impl because String() is called for a rvalue
  /// returned by GetProperty(). In this case the base::String returned is not
  /// optimal but acceptable for safety reason.
  base::String String() &&;

  fml::WeakRefPtr<Closure> GetClosure() const&;
  fml::WeakRefPtr<CDate> Date() const&;
  fml::WeakRefPtr<lepus::RegExp> RegExp() const&;
  fml::WeakRefPtr<Dictionary> Table() const&;
  fml::WeakRefPtr<CArray> Array() const&;
  fml::WeakRefPtr<lepus::LEPUSObject> LEPUSObject() const&;
  fml::WeakRefPtr<lepus::ByteArray> ByteArray() const&;
  fml::WeakRefPtr<lepus::RefCounted> RefCounted() const&;

  fml::RefPtr<Closure> GetClosure() &&;
  fml::RefPtr<CDate> Date() &&;
  fml::RefPtr<lepus::RegExp> RegExp() &&;
  fml::RefPtr<Dictionary> Table() &&;
  fml::RefPtr<CArray> Array() &&;
  fml::RefPtr<lepus::LEPUSObject> LEPUSObject() &&;
  fml::RefPtr<lepus::ByteArray> ByteArray() &&;
  fml::RefPtr<lepus::RefCounted> RefCounted() &&;

  CFunction Function() const;
  BuiltinFunctionTable* FunctionTable() const;
  void* CPoint() const;

  void SetBool(bool);

  void SetString(const base::String&);
  void SetString(base::String&&);

  void SetTable(const fml::RefPtr<lepus::Dictionary>&);
  void SetTable(fml::RefPtr<lepus::Dictionary>&&);
  void SetArray(const fml::RefPtr<lepus::CArray>&);
  void SetArray(fml::RefPtr<lepus::CArray>&&);

  void SetJSObject(const fml::RefPtr<lepus::LEPUSObject>&);
  void SetJSObject(fml::RefPtr<lepus::LEPUSObject>&&);
  void SetByteArray(const fml::RefPtr<lepus::ByteArray>&);
  void SetByteArray(fml::RefPtr<lepus::ByteArray>&&);

  void SetRefCounted(const fml::RefPtr<lepus::RefCounted>&);
  void SetRefCounted(fml::RefPtr<lepus::RefCounted>&&);

  bool SetProperty(uint32_t idx, const Value& val);
  bool SetProperty(uint32_t idx, Value&& val);
  bool SetProperty(const base::String& key, const Value& val);
  bool SetProperty(base::String&& key, const Value& val);
  bool SetProperty(base::String&& key, Value&& val);

  Value GetProperty(uint32_t idx) const;
  Value GetProperty(const base::String& key) const;

  int GetLength() const;
  bool Contains(const base::String& key) const;
  static void MergeValue(lepus::Value& target, const lepus::Value& update);
  static bool UpdateValueByPath(lepus::Value& target,
                                const lepus::Value& update,
                                const base::Vector<std::string>& path);

  bool MarkConst() const;

  BASE_EXPORT bool IsJSValue() const;

  lynx_api_env env() const { return env_; }

  /*
   deep convert jsvalue to lepus::Value when deep_convert == true;
   */
  Value ToLepusValue(bool deep_convert = false) const;

  inline bool IsJSCPointer() const {
    return IsJSValue() && (value_.tag >> 16) == lynx_value_external;
  }

  inline void* LEPUSCPointer() const {
    DCHECK(IsJSCPointer());
    void* ret;
    lynx_value_get_external(env_, value_, &ret);
    return ret;
  }

  bool IsJSArray() const;
  bool IsJSTable() const;

  inline bool IsJSBool() const {
    return IsJSValue() && (value_.tag >> 16) == lynx_value_bool;
  }
  inline bool LEPUSBool() const {
    if (!IsJSBool()) return false;
    bool ret;
    lynx_value_get_bool(env_, value_, &ret);
    return ret;
  }
  inline bool IsJSString() const {
    return IsJSValue() && (value_.tag >> 16) == lynx_value_string;
  }

  inline bool IsJSUndefined() const {
    return IsJSValue() && (value_.tag >> 16) == lynx_value_undefined;
  }

  inline bool IsJSNumber() const {
    int32_t type = value_.tag >> 16;
    return IsJSValue() &&
           (type == lynx_value_int32 || type == lynx_value_int64 ||
            type == lynx_value_double);
  }

  inline bool IsJsNull() const {
    return IsJSValue() && (value_.tag >> 16) == lynx_value_null;
  }

  double LEPUSNumber() const;
  bool IsJSInteger() const;
  bool IsJSFunction() const;
  int GetJSLength() const;
  bool IsJSFalse() const;
  int64_t JSInteger() const;
  std::string ToString() const;

  void SetCPoint(void*);
  void SetCFunction(CFunction);
  void SetNan(bool);
  ~Value();

  bool IsTrue() const { return !IsFalse(); }

  bool IsFalse() const {
    return value_.type == lynx_value_null || value_.type == lynx_value_nan ||
           value_.type == lynx_value_undefined ||
           (value_.type == lynx_value_bool && !Bool()) ||
           (IsNumber() && Number() == 0) ||
           (value_.type == lynx_value_string && StringView().empty()) ||
           IsJSFalse();
  }
  inline bool IsEmpty() const {
    return (value_.type == lynx_value_null) ||
           (value_.type == lynx_value_undefined) || IsJSUndefined() ||
           IsJsNull();
  }

  inline void SetNil() {
    FreeValue();
    value_.type = lynx_value_null;
    value_.val_ptr = nullptr;
  }

  inline void SetUndefined() {
    FreeValue();
    value_.type = lynx_value_undefined;
    value_.val_ptr = nullptr;
  }

  bool IsEqual(const Value& value) const;
  BASE_EXPORT_FOR_DEVTOOL friend bool operator==(const Value& left,
                                                 const Value& right);

  BASE_EXPORT_FOR_DEVTOOL friend bool operator!=(const Value& left,
                                                 const Value& right) {
    return !(left == right);
  }

  friend Value operator+(const Value& left, const Value& right) {
    Value value;
    if (left.IsNumber() && right.IsNumber()) {
      if (left.IsInt64() && right.IsInt64()) {
        value.SetNumber(left.Int64() + right.Int64());
      } else {
        value.SetNumber(left.Number() + right.Number());
      }
    }
    return value;
  }

  friend Value operator-(const Value& left, const Value& right) {
    Value value;
    if (left.IsNumber() && right.IsNumber()) {
      if (left.IsInt64() && right.IsInt64()) {
        value.SetNumber(left.Int64() - right.Int64());
      } else {
        value.SetNumber(left.Number() - right.Number());
      }
    }
    return value;
  }

  friend Value operator*(const Value& left, const Value& right) {
    Value value;
    if (left.IsNumber() && right.IsNumber()) {
      if (left.IsInt64() && right.IsInt64()) {
        value.SetNumber(left.Int64() * right.Int64());
      } else {
        value.SetNumber(left.Number() * right.Number());
      }
    }
    return value;
  }

  friend Value operator/(const Value& left, const Value& right) {
    Value value;
    if (left.IsNumber() && right.IsNumber()) {
      if (left.IsInt64() && right.IsInt64()) {
        value.SetNumber(left.Int64() / right.Int64());
      } else {
        value.SetNumber(left.Number() / right.Number());
      }
    }
    return value;
  }

  friend Value operator%(const Value& left, const Value& right) {
    Value value;
    if (left.IsNumber() && right.IsNumber()) {
      value.SetNumber((int64_t)(left.Number()) % ((int64_t)right.Number()));
    }
    return value;
  }

  Value& operator+=(const Value& value) {
    if (IsNumber() && value.IsNumber()) {
      if (IsInt64() && value.IsInt64()) {
        SetNumber(Int64() + value.Int64());
      } else {
        SetNumber(Number() + value.Number());
      }
    }
    return *this;
  }

  Value& operator-=(const Value& value) {
    if (IsNumber() && value.IsNumber()) {
      if (IsInt64() && value.IsInt64()) {
        SetNumber(Int64() - value.Int64());
      } else {
        SetNumber(Number() - value.Number());
      }
    }
    return *this;
  }

  Value& operator*=(const Value& value) {
    if (IsNumber() && value.IsNumber()) {
      if (IsInt64() && value.IsInt64()) {
        SetNumber(Int64() * value.Int64());
      } else {
        SetNumber(Number() * value.Number());
      }
    }
    return *this;
  }

  Value& operator/=(const Value& value) {
    if (IsNumber() && value.IsNumber()) {
      if (IsInt64() && value.IsInt64()) {
        SetNumber(Int64() / value.Int64());
      } else {
        SetNumber(Number() / value.Number());
      }
    }
    return *this;
  }

  Value& operator%=(const Value& value) {
    if (IsNumber() && value.IsNumber()) {
      SetNumber((int64_t)Number() % (int64_t)value.Number());
    }
    return *this;
  }

  void Print() const;
  void PrintValue(std::ostream& output, bool ignore_other = false,
                  bool pretty = false) const;
  friend std::ostream& operator<<(std::ostream& output, const lepus::Value& v) {
    v.PrintValue(output);
    return output;
  }

  // override operator<< for class LogStream
  friend base::logging::LogStream& operator<<(base::logging::LogStream& output,
                                              const lepus::Value& v) {
    std::ostringstream output_lepus_value;
    v.PrintValue(output_lepus_value);
    output << output_lepus_value;
    return output;
  }

  void IteratorJSValue(const LepusValueIterator& callback) const;
  const lynx_value& value() const { return value_; }
  static ValueType LegacyTypeFromLynxValue(const lynx_value& value);
  static lynx_value_type ToLynxValueType(ValueType type);

  static inline void IterateExtendedValue(
      lynx_api_env env, const lynx_value& val,
      ExtendedValueIteratorCallback* pfunc) {
    if (!env || !val.val_ptr) {
      LOGE("IterateExtendedValue but env or value is nil");
      return;
    }
    lynx_value_iterate_value(env, val, LynxValueIteratorCallback,
                             reinterpret_cast<void*>(pfunc), nullptr);
  }

  /* The function is used for :
    1. convert lynx_value to lepus::Value when flag == 0;
    2. deep clone lynx_value to lepus::Value when flag == 1;
    3. shallow copy lynx_value to lepus::Value when flag == 2;
  flag default's value is 0
  */
  static Value ToLepusValue(lynx_api_env env, const lynx_value& val,
                            int32_t flag = 0);
  static bool IsLepusValueEqualToExtendedValue(lynx_api_env env,
                                               const lepus::Value& src,
                                               const lynx_value& dst);
  static CArray* DummyArray();
  static Dictionary* DummyTable();
  static class RegExp* DummyRegExp();
  static CDate* DummyDate();
  static Closure* DummyClosure();
  static class LEPUSObject* DummyLEPUSObject();
  static class ByteArray* DummyByteArray();

  static void ForEachLepusValue(const Value& value, LepusValueIterator func);

 private:
  void Copy(const Value& value);

  Value GetPropertyFromTableOrArray(const std::string& key) const;
  bool SetPropertyToTableOrArray(const std::string& key, const Value& update);
  inline lynx_value DeepCopyExtendedValue() const {
    lynx_value ret;
    lynx_value_deep_copy_value(env_, value_, &ret);
    return ret;
  }
  bool IsJSUninitialized() const {
    bool ret;
    lynx_value_is_uninitialized(env_, value_, &ret);
    return ret;
  }

  static void ToLepusValueRecursively(Value& value, bool deep_convert);
  static Value CloneRecursively(const Value& src, bool clone_as_jsvalue);

  static inline void LynxValueIteratorCallback(lynx_api_env env, lynx_value key,
                                               lynx_value value, void* pfunc,
                                               void* raw_data) {
    reinterpret_cast<ExtendedValueIteratorCallback*>(pfunc)->operator()(
        env, key, value);
  }

  static Value ToLepusArray(lynx_api_env env, const lynx_value& val,
                            int32_t flag = 0);
  static Value ToLepusMap(lynx_api_env env, const lynx_value& val,
                          int32_t flag = 0);
  static bool IsLepusArrayEqualToExtendedArray(lynx_api_env env,
                                               lepus::CArray* src,
                                               const lynx_value& dst);
  static bool IsLepusDictEqualToExtendedDict(lynx_api_env env,
                                             lepus::Dictionary* src,
                                             const lynx_value& dst);
};
}  // namespace lepus
}  // namespace lynx
typedef lynx::lepus::Value lepus_value;
#endif  // CORE_RUNTIME_VM_LEPUS_LEPUS_VALUE_H_
