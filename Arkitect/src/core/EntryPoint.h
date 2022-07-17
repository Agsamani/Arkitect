#pragma once

#include "Base.h"
#include "Application.h"

#include "events/KeyEvent.h"
#include "Window/Window.h"

extern Arkitect::Application* Arkitect::CreateApplication();

int main(int argc, char** argv) {

	Arkitect::Log::Init();

	auto app = Arkitect::CreateApplication();
	app->run();
	delete app;
}
