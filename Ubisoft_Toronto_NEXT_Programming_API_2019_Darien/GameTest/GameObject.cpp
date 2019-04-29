#include "stdafx.h"
#include "GameObject.h"
#include "App/app.h"

// Game object class for all inheriting game objects.

GameObject::GameObject()
{

}

GameObject::GameObject(Scene* sceneref, std::string name)
{
   
    m_SceneIBelongTo = sceneref;
    
    Init(name);

    




 
}

GameObject::GameObject(Scene* sceneref, std::string name, ObjectTransform transform)
{
    Init(name, transform);

    m_SceneIBelongTo = sceneref;



    
}


GameObject::~GameObject()
{

}

void GameObject::Init(std::string name)
{

    m_Name = name;
  
    m_Transform = ObjectTransform();

    
}

void GameObject::Init(std::string name, ObjectTransform& t)
{
    m_Name = name;
    m_Transform = t;
}


void GameObject::Update(float deltatime)
{
    
}

void GameObject::Render()
{
   // Default game object draw call.
    Vector2Int LeftPos = m_Transform.Position - 32;
    Vector2Int RightPos = m_Transform.Position + 32;
    //App::DrawQuad((float)LeftPos.x, (float)LeftPos.y, (float)RightPos.x, (float)RightPos.y, 0.5f, 0.5f, 0.5f);
    App::DrawQuad(LeftPos, RightPos, Vector3(1, 1, 0));
}

void GameObject::OnEvent(Event * event)
{
}
