//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_SPINLOCK_H
#define LVGLEX_SPINLOCK_H

#include <mutex>

namespace LVGLEx {

class Spinlock {
private:
  std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
  void lock() {
    while (flag.test_and_set(std::memory_order_acquire)) {
      // 自旋等待
      // 线程优先级
      std::this_thread::yield();
    }
  }

  void unlock() {
    flag.clear(std::memory_order_release);
  }
};

}

#endif //LVGLEX_SPINLOCK_H
