#include "stdafx.h"
#include "Scene.h"
#include "Player.h"
#include "AI.h"
#include "App/app.h"
#include "App/Event.h"
#include "App/PauseEvent.h"
#include "App/Vector.h"
#include "App/Transform.h"

//Scene class
// Second element of the scene graph, this class is meant to hold all the game objects into a map and update them in sequence. 
//Makes for easy instantiation.
Scene::Scene() : IGameElement()
{

}
Scene::Scene(GameWorld* gworld, int worldsize) : IGameElement()
{
    m_GameInstance = gworld;
    m_worldSize = worldsize;
    Init();
}

Scene::~Scene()
{

    for (auto object : m_GameObjects)
    {
        delete object.second;
    }

    delete m_TileMap;
  
}

void Scene::Init()
{
    m_TileMap = new CSimpleTileMap(m_worldSize);
    int bp = 0;
    m_TileMap->RandomMap(80, 12);


    m_GameObjects["Test"] = new Player(this, "Test");
    m_GameObjects["Test"]->SetPosition(Vector2Int(1024 / 2, 768 / 2));

    
    ObjectTransform t = ObjectTransform();
    t.Position = Vector2Int(300, 300);
    m_GameObjects["AI"] = new AI(this, "AI", t);
    

}


void Scene::Update(float deltatime)
{
   


    if (m_GamePaused == true)
    {
        return;
    }
    else
    {

        UpdateObjects(deltatime);
    }

}

void Scene::Render()
{
    m_TileMap->Render();
    // Wrapper function
    RenderObjects();
}


// Second level of the scene graph chain.
// Listens for events but also sends the events to the children objects under it.
void Scene::OnEvent(Event * event)
{
    if (event->m_EventType == Event::EventTypes::PauseEvent)
    {
        m_GamePaused = !m_GamePaused; // Don't update if we are paused.
    }
    for (auto object : m_GameObjects)
    {
        object.second->OnEvent(event);
    }
}

void Scene::UpdateObjects(float deltatime)
{

    for (auto object : m_GameObjects)
    {
        object.second->Update(deltatime);
    }
}

void Scene::RenderObjects()
{
    // Loop through our game objects and render them.
    for (auto object : m_GameObjects)
    {
        object.second->Render();
    }
}
