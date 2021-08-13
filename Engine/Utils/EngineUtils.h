#pragma once

#define ENGINE_INIT_FAIL	-1
#define ENGINE_INIT_SUCC	 0

#define ENGINE_GRAPHICS_INITIALIZED				glfwInit()
#define ENGINE_GRAPHICS_TERMINATE(screen)		glfwDestroyWindow(screen->GetWindow())


namespace ZM { namespace Utils {



}}