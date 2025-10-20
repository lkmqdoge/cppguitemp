#ifndef QRLX_LOG_HPP_
#define QRLX_LOG_HPP_

#include <iostream>
#include "SDL3/SDL.h"

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl

#define ELOG(msg, ...) \
     SDL_Log(msg)

#endif
