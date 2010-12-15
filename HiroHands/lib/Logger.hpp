// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// Logger.hpp
//

#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#ifdef __QNX__
#include <stdio.h>
#include <string.h>
#else
#include <cstring>
#endif

#include <cstdarg>
#include <iostream>

#ifdef __QNX__
#define VA_LIST va_list
#else
#define VA_LIST std::va_list
#endif

#ifdef HIROHANDSDLL_EXPORTS
#define DLE __declspec(dllexport)
#else
#define DLE
#endif

//
// Logger Interface
//

class DLE Logger {
public:
  Logger();
  virtual ~Logger();
  virtual void addMessage(const char *hdr, const char *mesg)=0;
  void addMessage(const char *hdr, const char *format, VA_LIST ap);
  void addMessage(const char *hdr, const char *prefix, 
                  const char *format, VA_LIST ap);
};


class DLE LoggerStderr : public Logger
{
public:
  LoggerStderr();
  virtual ~LoggerStderr();
  void addMessage(const char *hdr, const char *mesg);
};


#endif //_LOGGER_HPP_
