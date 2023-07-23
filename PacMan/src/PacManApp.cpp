#include "Arkitect.h"
#include "core/EntryPoint.h"

#include "GameLayer.h"

class PacManApp : public Arkitect::Application {
public:
	PacManApp(const Arkitect::ApplicationSpecification& spec)
		:Arkitect::Application(spec) 
	{
		PushLayer(new GameLayer());
	}

	~PacManApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	Arkitect::ApplicationSpecification spec;
	spec.Name = "PACMAN!";
	spec.Width = 1280;
	spec.Height = 1280;
	return new PacManApp(spec);
}