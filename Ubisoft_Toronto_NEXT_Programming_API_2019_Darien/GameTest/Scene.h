#pragma once
#include "App/IGameElement.h"
#include "GameObject.h"
#include <map>
#include "SimpleTileMap.h"
class GameWorld;
class GameObject;

class Scene : public IGameElement
{

public:
    Scene();
    virtual~Scene();
    Scene(GameWorld* gworld, int worldsize);


    void Init();

    virtual void Update(float deltatime);
    virtual void Render();
    virtual void OnEvent(Event* event);

    GameWorld* GetWorld() { return m_GameInstance; }

    CSimpleTileMap& GetTileMap(){ return *m_TileMap; }

private:
    int m_worldSize;

    void UpdateObjects(float deltatime);
    void RenderObjects();



protected:
    bool m_GamePaused;
    GameWorld* m_GameInstance;

    std::map<std::string, GameObject*> m_GameObjects;
    CSimpleTileMap* m_TileMap;
    

};

