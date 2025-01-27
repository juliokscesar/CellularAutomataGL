#pragma once

#include <griffinLog/griffinLog.hpp>

#define logi grflog::info
#define logw grflog::warn
#define logc grflog::critical
#define logf grflog::fatal

#ifndef _NDEBUG
    #define logd grflog::debug
#else
    #define logd
#endif // _NDEBUG
