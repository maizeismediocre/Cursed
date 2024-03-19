#include "stdafx.h"
#include "MyGame.h"



CMyGame::CMyGame(void)
	// to initialise more sprites here use a comma-separated list
{
	is_falling = false;
	// TODO: add initialisation here
	theWalls.push_back(new CSprite(CRectangle(400, 0, 30, 1080), "wallvert.bmp", CColor::Blue(), GetTime()));
	theWalls.push_back(new CSprite(CRectangle(1500, 0, 30, 1080), "wallvert.bmp", CColor::Blue(), GetTime()));
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	// TODO: add the game update code here
	Playercontrol();
	player.Update(t);

	
}

void CMyGame::OnDraw(CGraphics* g)
{
	// TODO: add drawing code here
	player.Draw(g);
	for (CSprite* pWall : theWalls)
		pWall->Draw(g);
	
	
}
void CMyGame::Playercontrol()
{
	CVector gravity(0, -5);
	
	if (IsKeyDown(SDLK_DOWN))
	{
		is_falling = true;
	}
	if (is_falling == true)
	{
		player.Accelerate(gravity);
	}
		if (IsKeyDown(SDLK_LEFT)) player.SetMotion(-400,player.GetYVelocity());
		else if (IsKeyDown(SDLK_RIGHT)) player.SetMotion(400, player.GetYVelocity());
		else player.SetMotion(0, player.GetYVelocity());
		if (IsKeyDown(SDLK_z))
		{
			player.SetMotion(player.GetXVelocity(),0);
	}
	
	if (player.GetBottom() < 0)
	{
		player.SetPos(960, 1000);
		player.SetMotion(0,0);
		
		is_falling = false;
	}
	for (CSprite* pWall : theWalls)
	{
		if (player.HitTest(pWall))
		{
			if (player.GetLeft() < 451)
			{
				player.SetX(451);
			}
			if (player.GetRight() > 1480)
			{
				player.SetX(1480);

			}
		}
	
	}
	// add gun boots 
	// add cool down for jetpack
	// add platform for the player to stand on, pressing down arrow will make the player fall through it 
	// add phase shield which changes the sprite appearance and gives the player invicibility for a set time
}

void CMyGame::Enemycontrol()
{
	//add horizontal control jetpack cultist
	//add the gun cultist that shoots at the player

}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	player.LoadImage("rocket.bmp", CColor::Blue());
	player.SetImage("rocket.bmp");

}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	StartGame();	// exits the menu mode and starts the game mode
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{

	player.SetPosition(960, 1000);

}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
