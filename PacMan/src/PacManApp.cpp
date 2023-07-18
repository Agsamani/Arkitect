#include "Arkitect.h"
#include "core/EntryPoint.h"

#include "TLayer.h"

class PacManApp : public Arkitect::Application {
public:
	PacManApp() {
		PushLayer(new TLayer());
	}

	~PacManApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new PacManApp();
}