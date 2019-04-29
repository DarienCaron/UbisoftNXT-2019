#pragma once
#include "App/IGameElement.h"
#include "Scene.h"
#include "App/Event.h"
#include <queue>


class Scene; 
class GameWorld : public IGameElement
{

public:
    GameWorld();
    ~GameWorld();



    GameWorld(const int worldSize);


    void Init(int worldsize);


    void ProcessEvents();
    void QueueEvent(Event* event);


    virtual void Update(float deltatime);
    virtual void Render();
    virtual void OnEvent(Event* event);

    Scene& GetActiveScene() { return *m_GameScene; }

    int GetWorldSize() { return m_WorldSize; }
  

private:
    Scene* m_GameScene;
    int m_WorldSize;
    std::queue<Event*> m_EventQueue;
    
   
};

