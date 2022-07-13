#include "Arkitect.h"
#include "core/EntryPoint.h"

class SandBoxApp : public Arkitect::Application {
public:
	SandBoxApp() {
	}

	~SandBoxApp() {
	}

	void Test() {
		RKT_TRACE("SandBox is running...");
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new SandBoxApp();
}