#pragma once
#include "GameObject.h"
#include "GameWorld.h"
#include "App/Vector.h"
#include "App/Transform.h"
#include "Mesh.h"
#include "Collider.h"

class Scene;
class ObjectTransform;
class Player : public GameObject

{


public:

    Player();
    Player(Scene* sceneref, std::string name);
    Player(Scene* sceneref, std::string name, ObjectTransform t);


    virtual ~Player();

    virtual void Init(std::string name);
    virtual void Init(std::string name, ObjectTransform& t);





    // Inherited via IGameElement
    virtual void Update(float deltatime) override;

    virtual void Render() override;

    virtual void OnEvent(Event* event) override;


    void CheckForInput();
    void SetSpeedEncumberance(float value) { m_SpeedEncumberance = value; }


private:

    Vector2Int m_MoveDirection;
    Collider* m_Collider;

    Vector2Int m_CurrentTilePos;

    float m_SpeedEncumberance;
protected:

};

