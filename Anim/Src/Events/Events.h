#pragma once
#include "Utils/Memory.h"
/* Event System uses the Dispatcher and Listener pattern, also known as 'Observers'. 
   The implementation is currently blocking, meaning that all events must be handled
   as they are recieved, however it is planned that not-urgent events be put
   into an Event Queue for later processing. */

namespace Anim {

enum class EventType : short
{
    NONE, 
    WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_NOT_FOCUS, WINDOW_MOVE,
    PROG_UPDATE, PROG_RENDER, FRAME_SWAP,
    KEY_PRESS, KEY_RELEASE, 
    MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE, MOUSE_MOVE, MOUSE_SCROLL
};

enum class EventCategory: short
{
    NONE,
    CAT_PROGRAM,
    CAT_KEYBOARD,
    CAT_MOUSE,
    CAT_MOUSE_BUTTON
};

/* abstract definition for an event */
class Event
{
public:
    virtual ~Event(){}
    virtual EventType GetType() const = 0;
    virtual EventCategory GetCategory() const = 0;

    inline bool InCategory(EventCategory cat)
    {
        return cat == GetCategory();
    }
    
    EventCategory category;
    bool m_Handled = false;
};

/* recieves and processes events through the OnEvent function */
class EventListener 
{
public:
    virtual ~EventListener(){}                           /* Listeners should always be removed               */
    virtual void OnEvent(const Event& e) = 0;           /* from dispatchers upon destruction.               */
    virtual void OnAttach() = 0;                       /*  Called when listener is attached to dispatcher. */

};  

    /* sends events to listener */
    class EventDispatcher
    {
    friend class EventListener;

    protected:    
        uint32_t m_NumListeners = 0;
        std::vector<EventListener*> m_Listeners;

    public:
        virtual ~EventDispatcher(){}
        void AddListener(EventListener* listener)
        {
            m_Listeners.push_back(listener);
            listener->OnAttach();
        }
        void RmListener(EventListener* listener)
        {
            for(unsigned int i = 0; i < m_Listeners.size(); i++)
            {
                if(listener == m_Listeners[i])
                {
                    m_Listeners.erase(m_Listeners.begin() + i, m_Listeners.begin() + (i + 1)); 
                }
            }
        }

        void Notify(const Event& e)
        {
            for(EventListener* listener : m_Listeners)
                listener->OnEvent(e);
        }
    };
}