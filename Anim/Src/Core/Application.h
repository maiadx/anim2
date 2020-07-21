#pragma once
#include "Events/Events.h"
#include "Renderer/Renderer.h"
#include "Core/Frame.h"
#include "Gui/Dock.h"

namespace Anim 
{
class Application 
{
	Frame frame;
	Dock gui;

	/* frame rate stuff: */
	float frameTime;
	float lastTime;     
	float deltaTime;

public:
	Application();
	~Application() {}

	void Init();
	void Run();
	void Exit();

	void ScanInput();
	void RunCommand(std::vector<std::string>& inputCmd);
};
}