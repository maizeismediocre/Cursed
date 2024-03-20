#include "stdafx.h"
#include "MyGame.h"



CMyGame::CMyGame(void)
	// to initialise more sprites here use a comma-separated list
{
	
	
	
	
	theSpikes.push_back(new CSprite(CRectangle(400, 0, 30, 1080), "spike_v.bmp", CColor::Black(), GetTime()));
	theSpikes.back()->Rotate(180);
	theSpikes.push_back(new CSprite(CRectangle(1430, 0, 30, 1080), "spike_v.bmp", CColor::Black(), GetTime()));
	platform.push_back(new CSprite(CRectangle(780, 950, 300, 30), "platform.bmp", CColor::Black(), GetTime()));
	
}

CMyGame::~CMyGame(void)
{
	
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	
	
	Playercontrol();
	player.Update(t);
	shotcontrol();
	if (lives == 0)
	{
		GameOver();
	}
	for (CSprite* pShot : shotList)
		pShot->Update(t);
	if (shot_timer > 0)
	{
		--shot_timer;
	}
	
}

void CMyGame::OnDraw(CGraphics* g)
{
	
	background.Draw(g);
	player.Draw(g);
	for (CSprite* pSpikes : theSpikes)
		pSpikes->Draw(g);
	for (CSprite* pPlatform : platform)
		pPlatform->Draw(g);
	for (CSprite* pShot : shotList)
		pShot->Draw(g);

	*g << font(28) << color(CColor::Green()) << xy(10, 1050) << "lives: " << lives;
	*g << font(28) << color(CColor::Green()) << xy(10, 1000) << "level segment: " << level_segment;
	*g << font(28) << color(CColor::Green()) << xy(10, 950) << "jetpack fuel: " << jetpack_fuel;
	*g << font(28) << color(CColor::Green()) << xy(10, 900) << "shots: " << shots;
	if (game_over == true)
	{
		*g << font(50) << color(CColor::Red()) << xy(850, 540) << "GAME OVER";
	}
	if (hint == true)
	{
		*g << font(20) << color(CColor::Red()) << xy(730, 1050) << "You need to make it through the segment without losing any lives to progress";
	}
}
void CMyGame::Playercontrol()
{
	CVector gravity(0, -5);



	if (player.HitTest(platform.front()))
	{
		if (player.GetRight() > platform.front()->GetLeft() && player.GetLeft() < platform.front()->GetLeft())
		{
			player.SetPos(platform.front()->GetLeft() - player.GetWidth() / 2, player.GetY());
		}
		if (player.GetLeft() < platform.front()->GetRight() && player.GetRight() > platform.front()->GetRight())
		{
			player.SetPos(platform.front()->GetRight() + player.GetWidth() / 2, player.GetY());
		}
	}
	if (player.HitTest(platform.front()))
	{
		is_falling = false;
		player.SetMotion(player.GetXVelocity(), 0);
	}
	else
	{
		is_falling = true;
	}
	if (is_falling == true)
	{
		player.Accelerate(gravity);
	}
	if (IsKeyDown(SDLK_LEFT)) player.SetMotion(-400, player.GetYVelocity());
	else if (IsKeyDown(SDLK_RIGHT)) player.SetMotion(400, player.GetYVelocity());
	else player.SetMotion(0, player.GetYVelocity());
	if (IsKeyDown(SDLK_z) && jetpack_fuel != 0 && is_falling == true)
	{

		jetpack_fuel--;
		player.Accelerate(CVector(0, 10));

	}

	if (player.GetBottom() < 0 && lives == 3)
	{
		player.SetPos(960, 1000);
		player.SetMotion(0, 0);
		level_segment++;
		hint = false;
		jetpack_fuel = 100;
		shots = 5;

	}
	if (player.GetBottom() < 0 && lives != 3)
	{
		player.SetPos(960, 1000);
		player.SetMotion(0, 0);
		lives = 3;
		hint = true;
		jetpack_fuel = 100;
		shots = 5;
	}

	for (CSprite* pSpikes : theSpikes)
	{
		if (player.HitTest(pSpikes))
		{
			player.SetPos(960, 1000);
			player.SetMotion(0, 0);
			jetpack_fuel = 100;
			lives--;
			shots = 5;
		}
	}

	
	
	
	




	
	
	
	
}


void CMyGame::Enemycontrol()
{
	// TO DO add horizontal control jetpack cultist
	// TO DO add the gun cultist that shoots at the player

}

void CMyGame::levelsegments()
{
	// TO DO set up the level segments with different enemies and obstacles
}

void CMyGame::shotcontrol()
{
	for (CSprite* pShot : shotList)
	{
		for (CSprite* pSpikes : theSpikes)
		{
			if (pShot->HitTest(pSpikes))
			{
				pShot->Delete();
			}
		}
	}
	shotList.delete_if(deleted);

	if (IsKeyDown(SDLK_x) && shots != 0 && shot_timer == 0 && is_falling == true)
	{
		CSprite* newShot = new CSprite(player.GetX(), player.GetBottom(), 0, 0, GetTime());
		// set the motion of the new shot sprite
		newShot->AddImage("shot2.png", "shot2", 10, 1, 0, 0, 9, 0);
		newShot->SetAnimation("shot2", 12);
		newShot->SetMotion(0, player.GetYVelocity() - 400);
		// add the shot sprite to the list
		shotList.push_back(newShot);
		shot_timer = 15;
		--shots;
	}
	CSprite* newShot = new CSprite(player.GetX(), player.GetBottom(), 0, 0, GetTime());
	// set the motion of the new shot sprite

	// add the shot sprite to the list
	shotList.push_back(newShot);

	for (CSprite* shot : shotList)
	{

		if (shot->GetY() < 0) shot->Delete();
	}
	shotList.delete_if(deleted);
}

void CMyGame::phase_shield()
{
	//  TO DO add phase shield which changes the sprite appearance and gives the player invicibility for a set time
	// TO DO change sprite according to the phase shield
	// TO DO use a timer to set the time of the phase shield
}


/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	background.LoadImage("temp_background.bmp");
	background.SetImage("temp_background.bmp");
	player.LoadImage("player_temp.bmp", CColor::Red());
	player.SetImage("player_temp.bmp");

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
	background.SetPosition(950, 540);
	player.SetPosition(960, 1000);
	
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
	game_over = false;
	lives = 3;
	
	jetpack_fuel = 100;
	shots = 5;
	level_segment = 1;
}

// called when the game is over
void CMyGame::OnGameOver()
{
	game_over = true;
	
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
