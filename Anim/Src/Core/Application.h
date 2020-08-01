#pragma once
#include "Events/Events.h"
#include "Renderer/Renderer.h"
#include "Core/Frame.h"
#include "Gui/Dock.h"

namespace Anim 
{
class Application 
{
	Frame m_Frame;
	Dock m_Gui;
	bool m_ShouldClose;

	/* frame rate stuff: */
	float m_FrameTime;
	float m_LastTime;     
	float m_DeltaTime;

public:
	Application();
	~Application() {}

	void Init();
	void Run();
	void Exit();

	void ScanInput();
	void RunCommand(std::vector<std::string>& inputCmd);
	void RunComputeShaderProgram(const std::string& filepath);
};
}