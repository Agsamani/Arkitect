#pragma once

#include "Log.h"
#include "Deltatime.h"

#define RKT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
