#pragma once


class Event
{
public: 
    Event() { m_EventType = EventTypes::NotSet; }
     ~Event() {}




     enum EventTypes
     {
         InputEvent,
         GameEvent,
         PauseEvent,
         NotSet
     };
  
     EventTypes m_EventType;
  

 
};