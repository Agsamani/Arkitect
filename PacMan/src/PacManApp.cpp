#include "Arkitect.h"
#include "core/EntryPoint.h"

#include "GameLayer.h"

class PacManApp : public Arkitect::Application {
public:
	PacManApp() {
		PushLayer(new GameLayer());
	}

	~PacManApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new PacManApp();
}