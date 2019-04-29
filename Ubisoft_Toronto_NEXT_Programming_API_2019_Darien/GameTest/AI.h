#pragma once
#include "GameObject.h"
#pragma once
#include "GameObject.h"
#include "GameWorld.h"
#include "App/Vector.h"
#include "App/Transform.h"
#include "Mesh.h"
#include "Collider.h"
#include "PathFinder.h"

class Scene;
class ObjectTransform;
class AI : public GameObject

{


public:

    AI();
    AI(Scene* sceneref, std::string name);
    AI(Scene* sceneref, std::string name, ObjectTransform t);


    virtual ~AI();

    virtual void Init(std::string name);
    virtual void Init(std::string name, ObjectTransform& t);





    // Inherited via IGameElement
    virtual void Update(float deltatime) override;

    virtual void Render() override;

    virtual void OnEvent(Event* event) override;

    void SetSpeedEncumberance(float value) { m_SpeedEncumberance = value; }

    virtual void SetPosition(Vector2 pos);
    bool IsAtDestination();
    void SetNextDestination();



private:

    Vector2Int m_MoveDirection;
    Collider* m_Collider;

    Vector2Int m_CurrentTilePos;

    float m_SpeedEncumberance;

    Pathfinder* m_PathFinder;

    Vector2Int m_FinalTileDestination;
    Vector2Int m_Destination;

    bool m_Searching = false;
protected:

};
