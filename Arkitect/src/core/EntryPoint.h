#pragma once

#include "Base.h"
#include "Application.h"

#include "events/KeyEvent.h"

extern Arkitect::Application* Arkitect::CreateApplication();

int main(int argc, char** argv) {

	Arkitect::KeyPressedEvent k(Arkitect::Key::K);
	std::cout << k.ToString();

	Arkitect::Log::Init();

	auto app = Arkitect::CreateApplication();
	app->run();
	delete app;
}
