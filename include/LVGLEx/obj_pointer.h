//
// Created by 19254 on 25-2-23.
//

#ifndef LVGLEX_OBJ_POINTER_H
#define LVGLEX_OBJ_POINTER_H

#include <core/lv_obj_private.h>
#include <functional>
#include <memory>
#include <misc/lv_types.h>
struct _lv_display_t;

namespace LVGLEx {

template <typename T, typename Deleter> class PointerPack {
  bool is_quote = false;
  std::unique_ptr<T, Deleter> m_auto_ptr;
  T *m_quote_ptr = nullptr;

public:
  // 工厂方法
  static PointerPack<T, Deleter> makeQuote(T *ptr) {
    PointerPack<T, Deleter> tmp_pointer;
    tmp_pointer.is_quote = true;
    tmp_pointer.m_quote_ptr = ptr;
    return tmp_pointer;
  }
  static PointerPack<T, Deleter> makeQuote(const T *ptr) {
    PointerPack<T, Deleter> tmp_pointer;
    tmp_pointer.is_quote = true;
    tmp_pointer.m_quote_ptr = (T *)ptr;
    return tmp_pointer;
  }
  static PointerPack<T, Deleter> makePrivatePtr(T *ptr) {
    PointerPack<T, Deleter> tmp_pointer;
    tmp_pointer.is_quote = false;
    tmp_pointer.m_auto_ptr = std::unique_ptr<T, Deleter>(ptr);
    return tmp_pointer;
  }

  // 构造/析构
  PointerPack() = default;
  explicit PointerPack(T *ptr) : is_quote(true), m_quote_ptr(ptr) {}
  ~PointerPack() = default;

  // 禁用拷贝
  PointerPack(const PointerPack &) = delete;
  PointerPack &operator=(const PointerPack &) = delete;

  // 移动语义
  PointerPack(PointerPack &&other) noexcept { *this = std::move(other); }

  PointerPack &operator=(PointerPack &&other) noexcept {
    if (this != &other) {
      // 清理当前资源
      if (!is_quote)
        m_auto_ptr.reset();
      else
        m_quote_ptr = nullptr;

      // 转移资源
      is_quote = other.is_quote;
      if (is_quote) {
        m_quote_ptr = other.m_quote_ptr;
        other.m_quote_ptr = nullptr;
      } else {
        m_auto_ptr = std::move(other.m_auto_ptr);
        other.is_quote = true; // 原对象转为空引用
        other.m_quote_ptr = nullptr;
      }
    }
    return *this;
  }

  // 指针操作
  explicit operator bool() const noexcept { return get() != nullptr; }
  explicit operator T *() const noexcept { return get(); }
  T *get() const noexcept { return is_quote ? m_quote_ptr : m_auto_ptr.get(); }
  T *operator->() const noexcept { return get(); }
  T &operator*() const { return *get(); }

  bool operator==(const PointerPack<T, Deleter> &other) {
    if (is_quote && other.is_quote) {
      return m_quote_ptr == other.m_quote_ptr;
    } else if (!is_quote && !other.is_quote) {
      return m_auto_ptr == other.m_auto_ptr;
    } else {
      return false;
    }
  }

  // 所有权管理
  bool isOwning() const noexcept { return !is_quote; }

  T *release() noexcept {
    if (is_quote) {
      T *p = m_quote_ptr;
      m_quote_ptr = nullptr;
      return p;
    }
    return m_auto_ptr.release();
  }

  void reset(T *ptr = nullptr) {
    if (is_quote) {
      m_quote_ptr = ptr;
    } else {
      m_auto_ptr.reset(ptr);
    }
  }

  void swap(PointerPack &other) noexcept {
    std::swap(is_quote, other.is_quote);
    std::swap(m_auto_ptr, other.m_auto_ptr);
    std::swap(m_quote_ptr, other.m_quote_ptr);
  }

  // 比较操作
  bool operator==(const PointerPack &other) const noexcept {
    return get() == other.get();
  }

  bool operator!=(const PointerPack &other) const noexcept {
    return !(*this == other);
  }

  bool operator==(std::nullptr_t) const noexcept { return get() == nullptr; }
  bool operator!=(std::nullptr_t) const noexcept { return get() != nullptr; }

  void clean() {
    if (is_quote) {
      m_quote_ptr = nullptr;
    } else {
      m_auto_ptr.reset();
    }
  }
};

struct WidgetPointerDeleter {
  void operator()(lv_obj_t *ptr) const {
    if (ptr && lv_obj_is_valid(ptr)) {
      lv_obj_delete(ptr);
    }
  }
};

struct DisplayPointerDeleter {
  void operator()(lv_display_t *ptr) const {
    if (ptr) {
      lv_display_delete(ptr);
    }
  }
};

struct LayerPointerDeleter {
  void operator()(lv_layer_t *ptr) const {
    if (ptr) {
      delete ptr;
    }
  }
};

typedef PointerPack<lv_obj_t, WidgetPointerDeleter> WidgetPointer;
typedef PointerPack<lv_display_t, DisplayPointerDeleter> DisplayPointer;
typedef PointerPack<lv_layer_t, LayerPointerDeleter> LayerPointer;

} // namespace LVGLEx

#endif // LVGLEX_OBJ_POINTER_H
