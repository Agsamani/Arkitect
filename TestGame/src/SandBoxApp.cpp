#include "Arkitect.h"
#include "core/EntryPoint.h"

class SandBoxApp : public Arkitect::Application {
public:
	SandBoxApp() {
	}

	~SandBoxApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new SandBoxApp();
}