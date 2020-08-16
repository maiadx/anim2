#pragma once
#include "Events/Events.h"

namespace Anim
{
    class KeyEvent : public Event
    {
    protected:
        KeyEvent(int keyCode) : m_KeyCode(keyCode){}
        int m_KeyCode;

    public:
        inline int GetKeyCode() const { return m_KeyCode; }
        inline EventCategory GetCategory() const { return EventCategory::CAT_KEYBOARD; }
    };


    class KeyPressEvent : public KeyEvent  
    {
    protected:
        int repeats;    
    public: 
        KeyPressEvent(int m_KeyCode, int repeats) : KeyEvent(m_KeyCode), repeats(repeats){}

        inline EventType GetType() const { return EventType::KEY_PRESS; }
        inline int GetRepeats() const { return repeats; }
    };


    class KeyReleaseEvent : public KeyEvent
    {
    public:
        KeyReleaseEvent(int m_KeyCode) : KeyEvent(m_KeyCode){}
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