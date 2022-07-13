#include "rktpch.h"
#include "Application.h"

#include "Base.h"

namespace Arkitect {

	void Arkitect::Application::run()
	{
		RKT_CORE_TRACE("Application running...");
		Test();
	}

	Application::~Application()
	{

	}

}