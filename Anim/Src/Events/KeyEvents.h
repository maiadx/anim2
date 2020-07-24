#pragma once
#include "Events/Events.h"

namespace Anim
{
    class KeyEvent : public Event
    {
    protected:
        KeyEvent(int keyCode) : keyCode(keyCode){}
        int keyCode;

    public:
        inline int GetKeyCode() const { return keyCode; }
        inline EventCategory GetCategory() const { return EventCategory::CAT_KEYBOARD; }
    };


    class KeyPressEvent : public KeyEvent  
    {
    protected:
        int repeats;    
    public: 
        KeyPressEvent(int keyCode, int repeats) : KeyEvent(keyCode), repeats(repeats){}

        inline EventType GetType() const { return EventType::KEY_PRESS; }
        inline int GetRepeats() const { return repeats; }
    };


    class KeyReleaseEvent : public KeyEvent
    {
    public:
        KeyReleaseEvent(int keyCode) : KeyEvent(keyCode){}
        inline EventType GetType() const { return EventType::KEY_RELEASE; }
    };


    class KeyEventListener : public EventListener
    {
    public:
        ~KeyEventListener(){}
        virtual void OnEvent(const KeyEvent& e) = 0;

    };


    class KeyEventDispatcher : public EventDispatcher
    {
    public:
        KeyEventDispatcher(){}
        ~KeyEventDispatcher(){}
    };
}