#include "stdafx.h"
#include "MyGame.h"



CMyGame::CMyGame(void)
	// to initialise more sprites here use a comma-separated list
{
	
	
	
	
	
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

	
	spikes();
	Playercontrol();
	player.Update(t);
	shotcontrol();
	phase_shield();
	
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
	if (shield_timer > 0)
	{
		--shield_timer;
	}
	if (shield_cooldown > 0)
	{
		--shield_cooldown;
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

	*g << font(28) << color(CColor::Green()) << xy(10, 1050) << "level: " << level;
	*g << font(28) << color(CColor::Green()) << xy(10, 1000) << "lives: " << lives;
	*g << font(28) << color(CColor::Green()) << xy(10, 950) << "level segment: " << level_segment;
	*g << font(28) << color(CColor::Green()) << xy(10, 900) << "attempts: " << attempts;
	*g << font(20) << color(CColor::Green()) << xy(1500, 850) << "fuel: " << jetpack_fuel;
	*g << font(20) << color(CColor::Green()) << xy(1610, 835) << "shots: " << shots;
	*g << font(20) << color(CColor::Green()) << xy(1730, 840) << "shield timer: " << shield_timer;

	


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
	
	if (player.GetX() <= 435)
	{
		player.SetPos(435, player.GetY());
	}
	if (player.GetX() >= 1430)
	{
		player.SetPos(1430, player.GetY());
	}

	
	if (player.GetY() >= 1080)
	{
		player.SetPos(player.GetX(), 1080);
		
	}
	
	
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
		attempts = 0;
		NewLevel();
	}

	if (player.GetBottom() < 0 && lives != 3 && attempts < 10)
	{
		player.SetPos(960, 1000);
		player.SetMotion(0, 0);
		lives = 3;
		hint = true;
		jetpack_fuel = 100;
		shots = 5;
		attempts++;
	}

	if (player.GetBottom() < 0 && lives != 3 && attempts >= 10)
	{
		player.SetPos(960, 1000);
		player.SetMotion(0, 0);
		lives = 3;
		hint = true;
		jetpack_fuel = 100;
		shots = 5;
		attempts = 0;
		NewLevel();
	}

	
		
	
	
	
	
	




	
	
	
	
}


void CMyGame::Enemycontrol()
{
	// TO DO add horizontal control jetpack cultist
	// TO DO add the gun cultist that shoots at the player

}



void CMyGame::shotcontrol()
{
	
	

	
	if (IsKeyDown(SDLK_x) && shots != 0 && shot_timer == 0 && is_falling == true)
	{
		CSprite* pShot = new CSprite(player.GetX(), player.GetBottom(), 0, 0, GetTime());
		// set the motion of the new shot sprite
		pShot->AddImage("shot2.png", "shot2", 10, 1, 0, 0, 9, 0);
		pShot->SetAnimation("shot2", 12);
		pShot->SetMotion(0, player.GetYVelocity() - 400);
		// add the shot sprite to the list
		shotList.push_back(pShot);
		shot_timer = 15;
		--shots;
	}
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
	for (CSprite* pShot : shotList)
	{

		if (pShot->GetY() < 0) pShot->Delete();
	}
	shotList.delete_if(deleted);
}

void CMyGame::phase_shield()
{
	
	if (IsKeyDown(SDLK_c) && shield_cooldown == 0)
	{
		shield_timer = 30;

		
	}
	
if (shield_timer > 0)
	{
		is_shielded = true;
		shield_cooldown = 30;
	}
	else
	{
		is_shielded = false;
		
	}


	
	
if (is_shielded == true)
{
	
		player.SetImage("player_shield_temp.bmp");
	}
else
{
		player.SetImage("player_temp.bmp");
	}
	
}

void CMyGame::spikes()
{
	for (CSprite* pSpikes : theSpikes)
	{
		if (player.HitTest(pSpikes) && is_shielded == false)
		{
			player.SetPos(960, 1000);
			player.SetMotion(0, 0);
			--lives;
			jetpack_fuel = 100;
			shots = 5;
		}
	}
	
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
	player.LoadImage("player_shield_temp.bmp", CColor::Red());

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
	for each (CSprite * pSpikes in theSpikes)
	{
		delete pSpikes;
	}
	theSpikes.clear();
	theSpikes.push_back(new CSprite(CRectangle(400, 0, 30, 1080), "spike_v.bmp", CColor::Black(), GetTime()));
	theSpikes.back()->Rotate(180);
	theSpikes.push_back(new CSprite(CRectangle(1430, 0, 30, 1080), "spike_v.bmp", CColor::Black(), GetTime()));

	game_over = false;
	lives = 3;
	level = 5;
	jetpack_fuel = 100;
	shots = 5;
	level_segment = 1;
	attempts = 0;
	switch (nLevel)
	{
		case 0:
			// menu mode
		break;
		case 1: // level 1 add vertical spikes 
		// first layer of spikes
		theSpikes.push_back(new CSprite(CRectangle(450, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		theSpikes.push_back(new CSprite(CRectangle(1200, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		theSpikes.push_back(new CSprite(CRectangle(730, 700, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		// second layer of spikes
		theSpikes.push_back(new CSprite(CRectangle(650, 550, 100, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		theSpikes.push_back(new CSprite(CRectangle(1100, 550, 100, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		// third layer of spikes
		theSpikes.push_back(new CSprite(CRectangle(730, 350, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		theSpikes.push_back(new CSprite(CRectangle(450, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		theSpikes.push_back(new CSprite(CRectangle(1200, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		// fourth layer of spikes
		theSpikes.push_back(new CSprite(CRectangle(650, 200, 100, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		theSpikes.push_back(new CSprite(CRectangle(1100, 200, 100, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		// fifth layer of spikes
		theSpikes.push_back(new CSprite(CRectangle(730, 50, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		

		break;
	}
}

// called when the game is over
void CMyGame::OnGameOver()
{
	game_over = true;
	
}

// one time termination code
void CMyGame::OnTerminate()
{
	theSpikes.delete_all();
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
