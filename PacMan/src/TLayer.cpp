#include "TLayer.h"


TLayer::TLayer()
	:Layer("TLayer")
{
}

void TLayer::OnImGuiUpdate()
{

}

void TLayer::OnAttach()
{

}

void TLayer::OnDetach()
{

}

void TLayer::OnUpdate(float dt)
{

}

void TLayer::OnEvent(Arkitect::Event& e)
{
	RKT_INFO(e.ToString());
}
