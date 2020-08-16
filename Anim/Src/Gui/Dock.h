#pragma once
#include "Events/Events.h"
#include "Core/Frame.h"
namespace Anim 
{
class Dock : public EventDispatcher
{
    static Dock& Instance()
    {
        Dock* dock = new Dock;
        return *dock;
    }
    // bool f_showMenubar;
    bool f_ShowSidepanel;

public:
    Dock();	
    ~Dock();

    static void Init();
    static void Update(Frame& Frame, float dt);

    static void ShowSidePanel(Frame& Frame, float dt);
    static void ShowFrameSubPanel(Frame& Frame);
    static void ShowPlotSubPanel();
    static void ShowShaderSubPanel();

    static void DrawUserText(const std::string& msg);
    static void ShowInfoWindow();
};
}