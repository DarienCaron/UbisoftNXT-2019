#pragma once
#include "App/IGameElement.h"
#include "GameWorld.h"
#include "App/Vector.h"
#include "App/Transform.h"
#include "Mesh.h"

class Scene;
class ObjectTransform;
class GameObject : public IGameElement
   
{


public:

    GameObject();
    GameObject(Scene* sceneref, std::string name);
    GameObject(Scene* sceneref, std::string name, ObjectTransform t);
    

    virtual ~GameObject();

    virtual void Init(std::string name);
    virtual void Init(std::string name, ObjectTransform& t);

    



    // Inherited via IGameElement
    virtual void Update(float deltatime) override;

    virtual void Render() override;

    virtual void OnEvent(Event* event) override;

    void SetPosition(Vector2Int pos) 
    {
        m_Transform.Position.x = pos.x; 
        m_Transform.Position.y = pos.y;
    }

    Vector2Int GetPosition() const { return m_Transform.Position; }

    void SetRotation(Vector2 rot)
    {
        m_Transform.Rotation.x = rot.x;
        m_Transform.Rotation.y = rot.y;
    }
    
    Vector2 GetRotation() const { return m_Transform.Rotation; }

    void SetScale(Vector2 scale)
    {
        m_Transform.Scale.x = scale.x;
        m_Transform.Scale.y = scale.y;
    }

    Vector2 GetScale() const { return m_Transform.Scale; }

    void SetAttachedScene(Scene* scene)
    {
        m_SceneIBelongTo = scene;
    }

    Scene* GetAttachedScene() { return m_SceneIBelongTo; }

private:




protected:
    Scene* m_SceneIBelongTo;
    std::string m_Name;
    Mesh* m_Mesh;
    ObjectTransform m_Transform;
};


