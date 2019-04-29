#include "stdafx.h"
#include "MasterHeader.h"

// Game World class.
// Inherits from a game element interface in order to share behaviour with game related objects but that don't need to be inherited from.

GameWorld::GameWorld() : IGameElement()
{
    
}


GameWorld::~GameWorld()
{
    delete m_GameScene;
    while (m_EventQueue.size() != 0)
    {
        Event* pEvent = m_EventQueue.front();
        m_EventQueue.pop();
        delete pEvent;
    }
  
}

GameWorld::GameWorld(int worldSize) : IGameElement()
{
   
    Init(worldSize);
}



void GameWorld::Init(int worldsize)
{
   // World creates a scene passing in self and worldsize
    m_GameScene = new Scene(this, worldsize);
}

void GameWorld::ProcessEvents()
{
    while (m_EventQueue.size() != 0)
    {
        Event* newEvent = m_EventQueue.front();
        m_EventQueue.pop();

        OnEvent(newEvent);
        delete newEvent;
    }
}

void GameWorld::QueueEvent(Event * event)
{
    m_EventQueue.push(event);
}
// Update the current gameworld that gets called from the applications update.
void GameWorld::Update(float deltatime)
{
    // Check the event queue and send them down the scene graph.
    ProcessEvents();
    // Update the scene graph.
    m_GameScene->Update(deltatime);
}

void GameWorld::Render()
{
    // Render the scene.
    m_GameScene->Render();
}

void GameWorld::OnEvent(Event * event)
{
    // Pass the events down the chain.
    m_GameScene->OnEvent(event);
}
