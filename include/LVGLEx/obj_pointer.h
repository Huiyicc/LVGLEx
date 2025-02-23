//
// Created by 19254 on 25-2-23.
//

#ifndef LVGLEX_OBJ_POINTER_H
#define LVGLEX_OBJ_POINTER_H

#include <memory>
#include <misc/lv_types.h>

namespace LVGLEx {

void WidgetPointerDeleter(lv_obj_t *ptr);

template <typename T> class WidgetPointer {
  bool is_quote = false;
  std::shared_ptr<T> m_shared_ptr;
  T *m_quote_ptr = nullptr;

public:
  static WidgetPointer<T> MakeQuote(T *widget) {
    WidgetPointer<T> widget_pointer;
    widget_pointer.is_quote = true;
    widget_pointer.m_quote_ptr = widget;
    return widget_pointer;
  }
  static WidgetPointer<T> MakePrivatePtr(T *widget) {
    WidgetPointer<T> widget_pointer;
    widget_pointer.is_quote = false;
    widget_pointer.m_shared_ptr =
        std::shared_ptr<T>(widget, WidgetPointerDeleter);
    return widget_pointer;
  }
  static WidgetPointer<T> MakeShared(std::shared_ptr<T> widget) {
    WidgetPointer<T> widget_pointer;
    widget_pointer.is_quote = false;
    widget_pointer.m_shared_ptr =
        std::shared_ptr<T>(widget, WidgetPointerDeleter);
    return widget_pointer;
  }

  WidgetPointer() = default;
  ~WidgetPointer() = default;

  T *operator->() {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_shared_ptr.get();
    }
  }
  T &operator*() {
    if (is_quote) {
      return *m_quote_ptr;
    } else {
      return *m_shared_ptr;
    }
  }

  T *get() const {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_shared_ptr.get();
    }
  }

  bool operator==(const WidgetPointer<T> &other) {
    if (is_quote && other.is_quote) {
      return m_quote_ptr == other.m_quote_ptr;
    } else if (!is_quote && !other.is_quote) {
      return m_shared_ptr == other.m_shared_ptr;
    } else {
      return false;
    }
  }

  explicit operator bool() const {
    if (is_quote) {
      return m_quote_ptr != nullptr;
    } else {
      return m_shared_ptr != nullptr;
    }
  }

  explicit operator T *() const {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_shared_ptr.get();
    }
  }
  WidgetPointer& operator=(T* other) {
    if (is_quote) {
      m_quote_ptr = other;
    } else {
      m_shared_ptr = std::shared_ptr<T>(other, WidgetPointerDeleter);
    }
    return *this;
  }

  void clean() {
    if (is_quote) {
      m_quote_ptr = nullptr;
    } else {
      m_shared_ptr.reset();
    }
  }

};

} // namespace LVGLEx

#endif // LVGLEX_OBJ_POINTER_H
