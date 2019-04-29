//---------------------------------------------------------------------------------
// App.cpp
// Implementation of the calls that are exposed via the App namespace.
//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include <string>
#include "main.h"
#include "app.h"
#include "SimpleSound.h"
#include "SimpleController.h"

//---------------------------------------------------------------------------------
// Utils and externals for system info.
#define APP_VIRTUAL_TO_NATIVE_COORDS(_x_,_y_)			_x_ = ((_x_ / APP_VIRTUAL_WIDTH )*2.0f) - 1.0f; _y_ = ((_y_ / APP_VIRTUAL_HEIGHT)*2.0f) - 1.0f;
#define APP_NATIVE_TO_VIRTUAL_COORDS(_x_,_y_)			_x_ = ((_x_ + 1.0f) * APP_VIRTUAL_WIDTH) / 2.0f; _y_ = ((_y_ + 1.0f) * APP_VIRTUAL_HEIGHT) / 2.0f;

namespace App
{	
	void DrawLine(float sx, float sy, float ex, float ey, float r, float g, float b)
	{
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(sx, sy);
		APP_VIRTUAL_TO_NATIVE_COORDS(ex, ey);
#endif
		glBegin(GL_LINES);
		glColor3f(r, g, b); // Yellow
		glVertex2f(sx, sy);
		glVertex2f(ex, ey);
		glEnd();
	}
    void DrawQuad(float sx, float sy, float ex, float ey, float r, float g, float b)
    {
#if APP_USE_VIRTUAL_RES		
        APP_VIRTUAL_TO_NATIVE_COORDS(sx, sy);
        APP_VIRTUAL_TO_NATIVE_COORDS(ex, ey);
#endif
        glBegin(GL_TRIANGLES);
        glColor3f(r, g, b); // Yellow
        glVertex2f(sx, sy);
        glVertex2f(ex, sy);
        glVertex2f(ex, ey);
        
        glVertex2f(ex, ey);
        glVertex2f(sx, ey);
        glVertex2f(sx, sy);        
        glEnd();
    }

    void DrawLine(Vector2Int sx, Vector2Int ex, Vector3 color)
    {
#if APP_USE_VIRTUAL_RES		
        APP_VIRTUAL_TO_NATIVE_COORDS(sx.x, sx.y);
        APP_VIRTUAL_TO_NATIVE_COORDS(ex.x, ex.y);
#endif
        glBegin(GL_LINES);
        glColor3f(color.x, color.y, color.z); // Yellow
        glVertex2f(sx.x, sx.y);
        glVertex2f(ex.x, ex.y);
        glEnd();
    }

    void DrawLine(Vector2 s, Vector2 e, Vector3 color)
    {
#if APP_USE_VIRTUAL_RES		
        APP_VIRTUAL_TO_NATIVE_COORDS(s.x, s.y);
        APP_VIRTUAL_TO_NATIVE_COORDS(e.x, e.y);
#endif
        glBegin(GL_LINES);
        glColor3f(color.x, color.y, color.z); // Yellow
        glVertex2f(s.x, s.y);
        glVertex2f(e.x, e.y);
        glEnd();
    }

    void DrawQuad(Vector2Int s, Vector2Int e, Vector3 color)
    {

        float sx = (float)s.x;
        float sy = (float)s.y;
        float ex = (float)e.x;
        float ey = (float)e.y;
#if APP_USE_VIRTUAL_RES		
        APP_VIRTUAL_TO_NATIVE_COORDS(sx, sy);
        APP_VIRTUAL_TO_NATIVE_COORDS(ex, ey);
#endif
        glBegin(GL_TRIANGLES);
        glColor3f(color.x, color.y, color.z); // Yellow
        glVertex2f(sx, sy);
        glVertex2f(ex, sy);
        glVertex2f(ex, ey);

        glVertex2f(ex, ey);
        glVertex2f(sx, ey);
        glVertex2f(sx, sy);
        glEnd();
    }

    void DrawQuad(Vector2 s, Vector2 e, Vector3 color)
    {


#if APP_USE_VIRTUAL_RES		
        APP_VIRTUAL_TO_NATIVE_COORDS(s.x, s.y);
        APP_VIRTUAL_TO_NATIVE_COORDS(e.x, e.y);
#endif
        glBegin(GL_TRIANGLES);
        glColor3f(color.x, color.y, color.z); // Yellow
        glVertex2f(s.x, s.y);
        glVertex2f(e.x, s.y);
        glVertex2f(e.x, e.y);

        glVertex2f(e.x, e.y);
        glVertex2f(s.x, e.y);
        glVertex2f(s.x, s.y);
        glEnd();
    }

    void DrawCircle(Vector2Int Origin, float numofVerts, float radius, Vector3 color)
    {

        float originx = (float)Origin.x;
        float originy = (float)Origin.y;
 
#if APP_USE_VIRTUAL_RES		
        APP_VIRTUAL_TO_NATIVE_COORDS(originx, originy);
 
#endif
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(color.x, color.y, color.z);
        glVertex2f(originx, originy);
        for (int i = 1; i < numofVerts; i++)
        {
            float x = originx + (radius * cos(i * (PI * 2) / numofVerts));
            float y = originy + (radius * sin(i * (PI * 2) / numofVerts));

            glVertex2f(x, y);
        }

        glEnd();

    }
	bool IsKeyPressed(int key)
	{
		return ((GetAsyncKeyState(key) & 0x8000) != 0);
	}

	void GetMousePos(float &x, float &y)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position			
		ScreenToClient(MAIN_WINDOW_HANDLE, &mousePos);
		x = (float)mousePos.x;
		y = (float)mousePos.y;
		x = (x * (2.0f / WINDOW_WIDTH) - 1.0f);
		y = -(y * (2.0f / WINDOW_HEIGHT) - 1.0f);

#if APP_USE_VIRTUAL_RES		
		APP_NATIVE_TO_VIRTUAL_COORDS(x, y);
#endif
	}
	void PlaySound(const char *fileName, bool looping)
	{
		DWORD flags = (looping) ? DSBPLAY_LOOPING : 0;
		CSimpleSound::GetInstance().PlaySound(fileName, flags);
	}
	void StopSound(const char *fileName)
	{
		CSimpleSound::GetInstance().StopSound(fileName);
	}
	bool IsSoundPlaying(const char *fileName)
	{
		return CSimpleSound::GetInstance().IsPlaying(fileName);
	}
	// This prints a string to the screen
	void Print(float x, float y, const char *st, float r, float g, float b, void *font)
	{
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif		
		// Set location to start printing text
		glColor3f(r, g, b); // Yellow
		glRasterPos2f(x, y);
		int l = (int)strlen(st);
		for (int i = 0; i < l; i++)
		{
			glutBitmapCharacter(font, st[i]); // Print a character on the screen
		}
	}
	const CController &GetController( int pad )
	{
		return CSimpleControllers::GetInstance().GetController(pad);
	}
// End namespace App
}