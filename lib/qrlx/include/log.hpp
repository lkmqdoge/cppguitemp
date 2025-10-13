#ifndef QRLX_LOG
#define QRLX_LOG

#include <iostream>

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl 

#endif