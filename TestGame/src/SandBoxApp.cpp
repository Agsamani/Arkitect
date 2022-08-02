#include "Arkitect.h"
#include "core/EntryPoint.h"

#include "TestLayer.h"


class SandBoxApp : public Arkitect::Application {
public:
	SandBoxApp() {
		PushLayer(new TestLayer());
	}

	~SandBoxApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new SandBoxApp();
}