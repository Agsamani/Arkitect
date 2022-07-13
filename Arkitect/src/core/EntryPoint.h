#pragma once

#include "Base.h"
#include "Application.h"

extern Arkitect::Application* Arkitect::CreateApplication();

int main(int argc, char** argv) {

	Arkitect::Log::Init();

	auto app = Arkitect::CreateApplication();
	app->run();
	delete app;
}
