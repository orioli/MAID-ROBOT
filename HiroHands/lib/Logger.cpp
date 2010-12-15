// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// Loger.cpp
//

#ifdef _WIN32
#define SNPRINTF  sprintf_s
#define VSNPRINTF vsprintf_s
#else
//#define SNPRINTF  std::snprintf
//#define VSNPRINTF std::vsnprintf
#define SNPRINTF  snprintf
#define VSNPRINTF vsnprintf
#endif

#include "Logger.hpp"

Logger::Logger()  { }
Logger::~Logger() { }

void Logger::addMessage(const char *hdr, const char *format, 
                            VA_LIST ap)
{
  char mesg[256];
  VSNPRINTF(mesg, 128, format, ap);
  this->addMessage(hdr, mesg);
}


void Logger::addMessage(const char *hdr, const char *prefix, 
                           const char *format, VA_LIST ap)
{
  int len = std::strlen(format) + std::strlen(prefix) + 1;
#ifdef _MSC_VER
  char *form = (char *)malloc(len);
#else
  char form[len];
#endif
  SNPRINTF(form, len, "%s%s", prefix, format);

  char mesg[256];
  VSNPRINTF(mesg, 256, form, ap);
  this->addMessage(hdr, mesg);

#ifdef _MSC_VER
  free(form);
#endif
}


LoggerStderr::LoggerStderr() { }
LoggerStderr::~LoggerStderr() { }

void LoggerStderr::addMessage(const char *hdr, const char *mesg)
{
  std::cerr << hdr << " " << mesg << std::endl;
}
