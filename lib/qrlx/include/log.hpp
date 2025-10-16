#ifndef QRLX_LOG
#define QRLX_LOG


#include <iostream>
#include "SDL3/SDL.h"

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl 

#define CLOG(msg) \
     SDL_Log(msg)

#endif