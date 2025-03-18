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
  static PointerPack<T, Deleter> makeQuote(T *ptr) {
    PointerPack<T, Deleter> tmp_pointer;
    tmp_pointer.is_quote = true;
    tmp_pointer.m_quote_ptr = ptr;
    return tmp_pointer;
  }
  static PointerPack<T, Deleter> makePrivatePtr(T *widget) {
    PointerPack<T, Deleter> widget_pointer;
    widget_pointer.is_quote = false;
    widget_pointer.m_auto_ptr = std::unique_ptr<T, Deleter>(widget);
    return widget_pointer;
  }

  PointerPack() = default;
  PointerPack(T *ptr) {
    m_quote_ptr = ptr;
    is_quote = true;
  };
  PointerPack(const PointerPack &ptr) {
    if (ptr.is_quote) {
      m_quote_ptr = ptr.m_quote_ptr;
    } else {
      m_quote_ptr = ptr.get();
    }
    is_quote = true;
  };
  virtual ~PointerPack() = default;

  T *operator->() {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_auto_ptr.get();
    }
  }
  T &operator*() {
    if (is_quote) {
      return *m_quote_ptr;
    } else {
      return *m_auto_ptr;
    }
  }

  T *get() const {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_auto_ptr.get();
    }
  }

  bool operator==(const PointerPack<T, Deleter> &other) {
    if (is_quote && other.is_quote) {
      return m_quote_ptr == other.m_quote_ptr;
    } else if (!is_quote && !other.is_quote) {
      return m_auto_ptr == other.m_auto_ptr;
    } else {
      return false;
    }
  }

  explicit operator bool() const {
    if (is_quote) {
      return m_quote_ptr != nullptr;
    } else {
      return m_auto_ptr != nullptr;
    }
  }

  explicit operator T *() const {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_auto_ptr.get();
    }
  }

  PointerPack &operator=(T *other) = delete;
  PointerPack &operator=(PointerPack &&other) noexcept {
    is_quote = other.is_quote;
    if (is_quote) {
      m_quote_ptr = other.m_quote_ptr;
    } else {
      m_auto_ptr = std::move(other.m_auto_ptr);
      // m_deleter = std::move(other.m_deleter);
    }
    return *this;
  };
  // PointerPack& operator=(T* other) {
  //   if (is_quote) {
  //     m_quote_ptr = other;
  //   } else {
  //     m_shared_ptr = std::shared_ptr<T>(other, other->m_deleter);
  //   }
  //   return *this;
  // }

  void clean() {
    if (is_quote) {
      m_quote_ptr = nullptr;
    } else {
      m_auto_ptr.reset();
    }
  }

  T *release() {
    if (is_quote) {
      return m_quote_ptr;
    } else {
      return m_auto_ptr.release();
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

typedef PointerPack<lv_obj_t, WidgetPointerDeleter> WidgetPointer;
typedef PointerPack<lv_display_t, DisplayPointerDeleter> DisplayPointer;

} // namespace LVGLEx

#endif // LVGLEX_OBJ_POINTER_H
