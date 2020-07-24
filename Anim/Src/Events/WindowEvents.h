#pragma once
#include "Events/Events.h"


namespace Anim 
{
    class WindowEvent : public Event 
    {
    public:
        inline EventCategory GetCategory() const { return EventCategory::CAT_PROGRAM; }
    };


    class WindowResizeEvent : public WindowEvent
    {
        float width, height;    

    public:
        WindowResizeEvent(int sWidth, int sHeight) : width(sWidth), height(sHeight) {}

        inline EventType GetType() const { return EventType::WINDOW_RESIZE; }

        inline float GetScreenWidth() const { return width; }
        inline float GetScreenHeight() const { return height; }
    };


    class WindowCloseEvent : public WindowEvent
    {
    public:
        inline EventType GetType() const { return EventType::WINDOW_CLOSE; }
    };

    class WindowEventDispatcher : public EventDispatcher
    {
    public:
        WindowEventDispatcher(){}
        ~WindowEventDispatcher(){}
    };
}

