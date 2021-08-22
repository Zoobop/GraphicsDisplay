#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace DevEngine::Math {

#define	RAD2DEG(degrees) (degrees * (M_PI / 180.0f))
#define DEG2RED(radians) (radians * (180.0f / M_PI))

}