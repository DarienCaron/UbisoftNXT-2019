#include "stdafx.h"
#include "GameObject.h"
#include "App/app.h"
#include "Player.h"
#include "App/InputEvent.h"
#include "App/PauseEvent.h"


Player::Player()
{

}
// Initialize the player here
Player::Player(Scene* sceneref, std::string name) : GameObject(sceneref, name)
{

    m_SceneIBelongTo = sceneref;

    Init(name);







}

Player::Player(Scene* sceneref, std::string name, ObjectTransform transform) : GameObject(sceneref, name, transform)
{
    Init(name, transform);

    m_SceneIBelongTo = sceneref;




}


Player::~Player()
{
    delete m_Collider;
}

void Player::Init(std::string name)
{

    m_Name = name;

    m_Transform = ObjectTransform();

    m_Collider = new Collider(); // Set up the collider
    m_Collider->SetHalfDimensions(Vector2(24, 24)); // Set its dimensions
}

void Player::Init(std::string name, ObjectTransform& t)
{
    m_Name = name;
    m_Transform = t;

    m_Collider = new Collider();
    m_Collider->SetHalfDimensions(Vector2(24, 24));
}


void Player::Update(float deltatime)
{
    CheckForInput(); // Function within player that listens for input.
    m_Collider->CalculateCollider(m_Transform.Position, m_MoveDirection); // Calculates the collider displacement.
    if (m_Collider->CheckCollisions(m_SceneIBelongTo->GetTileMap())) // Checks if any of the collision points have collided.
    {

        m_Collider->ResolveCollision(m_MoveDirection); // If true, resolve it.

    }




    m_Transform.Position += m_MoveDirection * deltatime / 5; // Move the player.



}

void Player::Render()
{

    Vector2Int LeftPos = m_Transform.Position - 24;
    Vector2Int RightPos = m_Transform.Position + 24;


    m_Collider->DebugDrawCollider();

    App::DrawCircle(m_Transform.Position, 12, 0.04f, Vector3(1, 1, 0));
}

void Player::OnEvent(Event * sEvent)
{
    Vector2Int Direction = Vector2Int().Zero(); // Event system that is passed down through the scene graph.
    if (sEvent->m_EventType == Event::EventTypes::InputEvent) // Check the event type.
    {
        InputEvent* Input = (InputEvent*)sEvent; // Cast the event as an input event to pull the data from it.
        Direction = Input->InputDirection;
        m_MoveDirection = Direction;
    }
  

    
    
    
}

void Player::CheckForInput()
{
    if (App::IsKeyPressed('W')) // Uses the application to listen for input and fires off an event with direction data.
    {
        InputEvent* NewEvent = new InputEvent(Vector2Int().Up());
        m_SceneIBelongTo->GetWorld()->QueueEvent(NewEvent);
        
    }
    if (App::IsKeyPressed('A'))
    {
        InputEvent* NewEvent = new InputEvent(Vector2Int().Left());
        m_SceneIBelongTo->GetWorld()->QueueEvent(NewEvent);
       
    }
    if (App::IsKeyPressed('S'))
    {
        InputEvent* NewEvent = new InputEvent(Vector2Int().Down());
        m_SceneIBelongTo->GetWorld()->QueueEvent(NewEvent);
       
    }
    if (App::IsKeyPressed('D'))
    {
        InputEvent* NewEvent = new InputEvent(Vector2Int().Right());
        m_SceneIBelongTo->GetWorld()->QueueEvent(NewEvent);
       
    }


}
