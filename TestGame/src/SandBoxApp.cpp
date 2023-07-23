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
	SandBoxApp(const Arkitect::ApplicationSpecification& spec) 
		:Arkitect::Application(spec) 
	{
		PushLayer(new Renderer2DTestLayer());
	}

	~SandBoxApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	Arkitect::ApplicationSpecification spec;
	return new SandBoxApp(spec);
}