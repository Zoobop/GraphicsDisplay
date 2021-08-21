#pragma once

#include <iostream>

#define DEBUG 1

#if DEBUG == 1
#define ENGINE_LOG(x) std::cout << x << std::endl;
#else
#define ENGINE_LOG(x)
#endif

namespace DevEngine::Utils {



}