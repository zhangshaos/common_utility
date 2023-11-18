#ifndef EXPLORER_PRINTF_H
#define EXPLORER_PRINTF_H

#include <cstdio>
#include <string>

std::string
str_printf(size_t buf_size, const char *const fmt, ...){
  //Copied from https://blog.csdn.net/xcoderone/article/details/48735425
  char *buf = (char*) alloca(buf_size);
  std::fill(buf, buf+buf_size, '\0');
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, buf_size, fmt, args);
  va_end(args);
  std::string s = buf;
  return s;
}

#endif //EXPLORER_PRINTF_H
