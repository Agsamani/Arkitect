#include "Arkitect.h"
#include "core/EntryPoint.h"

#include "TestLayer.h"
#include "MandleBulbDemo.h"
#include "ComputeTestLayer.h"
#include "SlimeMouldLayer.h"
#include "MetaBallLayer.h"


class SandBoxApp : public Arkitect::Application {
public:
	SandBoxApp() {
		PushLayer(new SlimeMouldLayer());
	}

	~SandBoxApp() {
	}
};

Arkitect::Application* Arkitect::CreateApplication() {
	return new SandBoxApp();
}