//
// Created by 19254 on 24-5-31.
//

#ifndef LVGLEX_LOGS_H
#define LVGLEX_LOGS_H

#include "fmt/format.h"
#include <chrono>
#include <string>
#include <cstring>
#include <iostream>

namespace LVGLEx {

#ifdef _HOST_WINDOWS_
#define LOCALTIME(time_str)                                                          \
  auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
  std::tm tm_info = {0};                                                             \
  localtime_s(&tm_info, &now);                                                       \
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);

#else
#define LOCALTIME(time_str)    \
  auto now = time(nullptr);    \
  struct tm tm_info = {0};     \
  localtime_r(&now, &tm_info); \
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);

#endif

#define PrintInfo(fstr, ...)                                                                                      \
  do {                                                                                                            \
    char time_str[32];                                                                                            \
    LOCALTIME(time_str);                                                                                          \
    std::string_view __TMP__fPath__ = __FILE__;                                                                   \
    auto __TMP__lstr__ = fmt::format("<info> <{}> [{}:{}] ", time_str, __TMP__fPath__, __LINE__);                  \
    auto __TMP__ustr__ = fmt::format(fstr, ##__VA_ARGS__);                                                        \
    std::cout << fmt::format("{}{}", __TMP__lstr__, __TMP__ustr__) << std::endl;                                  \
  } while (0)

#define PrintDebug(fstr, ...)                                                                                     \
  do {                                                                                                            \
    char time_str[32];                                                                                            \
    LOCALTIME(time_str);                                                                                          \
    std::string_view TMP_fPath = __FILE__;                                                                   \
    auto TMP_lstr = fmt::format("<debug> <{}> [{}:{}] ", time_str, TMP_fPath, __LINE__);                  \
    auto TMP_ustr = fmt::format(fstr, ##__VA_ARGS__);                                                        \
    std::cout << fmt::format("{}{}", TMP_lstr, TMP_ustr) << std::endl;                                  \
  } while (0)

#define PrintError(fstr, ...)                                                                                              \
  do {                                                                                                            \
    char time_str[32];                                                                                            \
    LOCALTIME(time_str);                                                                                          \
    std::string_view __TMP__fPath__ = __FILE__;                                                                   \
    auto __TMP__lstr__ = fmt::format("<error> <{}> [{}:{}] ", time_str, __TMP__fPath__, __LINE__);                  \
    auto __TMP__ustr__ = fmt::format(fstr, ##__VA_ARGS__);                                                        \
    std::cerr << fmt::format("{}{}", __TMP__lstr__, __TMP__ustr__) << std::endl;                                  \
  } while (0)

/*
*
    __TMP__fPath__ = __TMP__fPath__.substr(strlen(PRIOJECT_PATH), __TMP__fPath__.size() - strlen(PRIOJECT_PATH)); \
* */

}// namespace LVGLEx
#endif// LVGLEX_LOGS_H
