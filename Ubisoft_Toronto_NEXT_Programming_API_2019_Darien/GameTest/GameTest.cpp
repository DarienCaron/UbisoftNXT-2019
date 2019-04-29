//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "SimpleTileMap.h"
#include "GameWorld.h"

static const int MAP_SIZE = 16;
static const int TUNNEL_LEN = 12;
static const float TUNNEL_FILL_PERCENT = 80;

GameWorld* MyWorld;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
    MyWorld = new GameWorld(MAP_SIZE);

   
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
    static const float MIN_FRAMERATE = (1000 / 20);
    if (deltaTime > MIN_FRAMERATE)
        deltaTime = MIN_FRAMERATE;
	    
    MyWorld->Update(deltaTime);
    if (App::GetController().CheckButton(VK_PAD_A, true))
    {
        MyWorld->GetActiveScene().GetTileMap().RandomMap(TUNNEL_FILL_PERCENT, TUNNEL_LEN);
    }
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	 
    MyWorld->Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
    delete MyWorld;
}