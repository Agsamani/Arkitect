#include <rktpch.h>
#include "Utils.h"

#include "GLFW/glfw3.h"

namespace Arkitect{

	float Time::GetTime()
	{
		return glfwGetTime();
	}

}