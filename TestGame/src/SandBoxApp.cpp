#include "Arkitect.h"
#include "core/EntryPoint.h"

#include "TestLayer.h"
#include "MandleBulbDemo.h"
#include "ComputeTestLayer.h"
#include "SlimeMouldLayer.h"
#include "MetaBallLayer.h"
#include "Renderer2DTestLayer.h"


class SandBoxApp : public Arkitect::Application {
public:
	SandBoxApp() {
		PushLayer(new Renderer2DTestLayer());
	}

	~SandBoxApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new SandBoxApp();
}