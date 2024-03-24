#include "stdafx.h"
#include "MyGame.h"



CMyGame::CMyGame(void)
	// to initialise more sprites here use a comma-separated list
{
	
	
}

CMyGame::~CMyGame(void)
{
	
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();
	if (IsMenuMode() || IsGameOver()) return;
	
	spikes();
	Playercontrol();
	player.Update(t);
	shotcontrol();
	phase_shield();
	Enemycontrol();
	if (lives <= 0)
	{
		GameOver();
	}
	for (CSprite* pShot : shotList)
		pShot->Update(t);
	for (CSprite* jetpack_cultist : jetpack_enemies)
		jetpack_cultist->Update(t);
	for (CSprite* gun_cultist : gun_enemies)
		gun_cultist->Update(t);
	for (CSprite * shield_cultist : shield_enemies)
		shield_cultist->Update(t);
	for (CSprite* enemy_shot : gun_enemy_shots)
		enemy_shot->Update(t);

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
	if (IsMenuMode())
	{
		startscreen.Draw(g);
		return;
	}

	background.Draw(g);
	player.Draw(g);
	
	for (CSprite* pSpikes : theSpikes)
		pSpikes->Draw(g);
	for (CSprite* pPlatform : platform)
		pPlatform->Draw(g);
	for (CSprite* pShot : shotList)
		pShot->Draw(g);
	for (CSprite* jetpack_cultist : jetpack_enemies)
		jetpack_cultist->Draw(g);
	for (CSprite* gun_cultist : gun_enemies)
		gun_cultist->Draw(g);
	for (CSprite* shield_cultist : shield_enemies)
		shield_cultist->Draw(g);
	for (CSprite* enemy_shot : gun_enemy_shots)
		enemy_shot->Draw(g);
	if (game_over == false && gamewon != true)
	{

		*g << font(20) << color(CColor::Green()) << xy(10, 1050) << "level: " << level;
		*g << font(20) << color(CColor::Green()) << xy(10, 1000) << "lives: " << lives;
		*g << font(20) << color(CColor::Green()) << xy(10, 950) << "level segment: " << level_segment;
		*g << font(20) << color(CColor::Green()) << xy(10, 900) << "attempts: " << attempts;
		*g << font(15) << color(CColor::Green()) << xy(1500, 850) << "fuel: " << jetpack_fuel;
		*g << font(15) << color(CColor::Green()) << xy(1610, 835) << "shots: " << shots;
		*g << font(15) << color(CColor::Green()) << xy(1730, 840) << "shield timer: " << shield_timer;
		if (shield_cooldown == 0)
		{
			*g << font(15) << color(CColor::Green()) << xy(1730, 820) << "shield ready";
		}
	}
	
	if (gamewon == true)
	{
		
		endscreen.Draw(g);
	}

	if (game_over == true && gamewon == false)
	{
		
		*g << font(50) << color(CColor::Red()) << xy(850, 540) << "GAME OVER";
		
	}
	if (hint == true)
	{
		*g << font(20) << color(CColor::Red()) << xy(400, 1050) << "You need to make it through the segment without losing any lives to progress";
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
		jetpack.Play("jetpack.wav");
		jetpack.Volume(0.8);
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
		gun_enemy_shots.clear();
		Nextlevel.Play("nextlevel.wav");
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
		gun_enemy_shots.clear();
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
		gun_enemy_shots.clear();
		Nextlevel.Play("nextlevel.wav");
		NewLevel();
	}

	
		
	
	
	
	
	




	
	
	
	
}


void CMyGame::Enemycontrol()
{ 
	//jetpack cultist movement
	for (CSprite* jetpack_cultist : jetpack_enemies)
	{
		// if the jetpack cultist goes past x 435 it will turn around
		if (jetpack_cultist->GetX() <= 435)
		{
			jetpack_cultist->SetMotion(100, 0);
		}
		// if the jetpack cultist goes past x 1430 it will turn around
		if (jetpack_cultist->GetX() >= 1430)
		{
			jetpack_cultist->SetMotion(-100, 0);
		}
		if (player.HitTest(jetpack_cultist) && is_shielded == false)
		{
			hit.Play("playerhit.wav");
			player.SetPos(960, 1000);
			player.SetMotion(0, 0);
			--lives;
			jetpack_fuel = 100;
			shots = 5;



		}


	}

	

	// gun cultist behaviour

	for (CSprite* gun_cultist : gun_enemies)
	{
		CVector direction = player.GetPosition() - gun_cultist->GetPosition();
		gun_cultist->SetDirection(direction);
		gun_cultist->SetRotation(gun_cultist->GetDirection());
		if (rand() % 150 == 0 && is_falling == true)
		{
			CSprite* enemy_shot = new CSprite(gun_cultist->GetX(), gun_cultist->GetY(), 0, 0, GetTime());
			enemy_shot->AddImage("enemy_shot.png", "enemyshot", 10, 1, 0, 0, 9, 0);
			enemy_shot->SetAnimation("enemyshot",12);
			enemy_shot->SetDirection(player.GetPosition() - gun_cultist->GetPosition());
			enemy_shot->SetSpeed(300);
			shotSound.Play("shot.wav");
			gun_enemy_shots.push_back(enemy_shot);
			
		}
	}
	// if the player hit the gun cultist and is not shielded they lose a life
	for (CSprite* gun_cultist : gun_enemies)
	{
		if (player.HitTest(gun_cultist) && is_shielded == false)
		{
			hit.Play("playerhit.wav");
			player.SetPos(960, 1000);
			player.SetMotion(0, 0);
			--lives;
			jetpack_fuel = 100;
			shots = 5;
		}
	}
	//shield cultist behaviour
	// same behaviour as jetpack cultist but with a when the player is shielding whilst it hits them it kills the
	for (CSprite* shield_cultist : shield_enemies)
	{
		if (shield_cultist->GetX() <= 435)
		{
			shield_cultist->SetMotion(100, 0);
		}
		if (shield_cultist->GetX() >= 1430)
		{
			shield_cultist->SetMotion(-100, 0);
		}
		if (player.HitTest(shield_cultist) && is_shielded == false)
		{
			hit.Play("playerhit.wav");
			player.SetPos(960, 1000);
			player.SetMotion(0, 0);
			--lives;
			jetpack_fuel = 100;
			shots = 5;
		}
		if (player.HitTest(shield_cultist) && is_shielded == true)
		{
			shield_cultist->Delete();
		}
	}
}
	



void CMyGame::shotcontrol()
{
	// if the enemy shots go off the screen they are deleted
	for (CSprite* enemy_shot : gun_enemy_shots)
	{
		if (enemy_shot->GetY() < 0) enemy_shot->Delete();
	}

	// if the player gets hit by the enemy shot and is not shielded they lose a life
	for (CSprite* enemy_shot : gun_enemy_shots)
	{
		if (player.HitTest(enemy_shot) && is_shielded == false)
		{
			hit.Play("playerhit.wav");
			player.SetPos(960, 1000);
			player.SetMotion(0, 0);
			--lives;
			--lives;
			jetpack_fuel = 100;
			shots = 5;
			enemy_shot->Delete();
		}
	}
	// if the player gets hit by the enemy shot and is shielded the is absorbed and the player gains a shot
	for (CSprite* enemy_shot : gun_enemy_shots)
	{
		if (player.HitTest(enemy_shot) && is_shielded == true)
		{
			enemy_shot->Delete();
			shots++;
		}
	}


	
	if (IsKeyDown(SDLK_x) && shots != 0 && shot_timer == 0 && is_falling == true)
	{
		CSprite* pShot = new CSprite(player.GetX(), player.GetBottom(), 0, 0, GetTime());
		// set the motion of the new shot sprite
		pShot->AddImage("shot2.png", "shot2", 10, 1, 0, 0, 9, 0);
		pShot->SetAnimation("shot2", 12);
		pShot->SetMotion(0, player.GetYVelocity() - 400);
		// add the shot sprite to the list
		shotList.push_back(pShot);
		shotSound.Play("shot.wav");
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
		for (CSprite* jetpack_cultist : jetpack_enemies)
		{
			if (pShot->HitTest(jetpack_cultist))
			{
				jetpack_cultist->Delete();
				pShot->Delete();
			}
		}
	}
	for (CSprite* pShot : shotList)
	{
		for (CSprite* gun_cultist : gun_enemies)
		{
			if (pShot->HitTest(gun_cultist))
			{
				gun_cultist->Delete();
				pShot->Delete();
			}
		}
	}
	// if the shot hits the shield enemy it is deleted the shield enemy is not and the bullet is reflected back at the player
	for (CSprite* pShot : shotList)
	{
		for (CSprite* shield_cultist : shield_enemies)
		{
			if (pShot->HitTest(shield_cultist))
			{
				CSprite* enemy_shot = new CSprite(shield_cultist->GetX(), shield_cultist->GetY(), 0, 0, GetTime());
				enemy_shot->AddImage("enemy_shot.png", "enemyshot", 10, 1, 0, 0, 9, 0);
				enemy_shot->SetAnimation("enemyshot", 12);
				enemy_shot->SetDirection(player.GetPosition() - shield_cultist->GetPosition());
				enemy_shot->SetSpeed(300);
				gun_enemy_shots.push_back(enemy_shot);
				pShot->Delete();
			}
		}
	}
	

	for (CSprite* pShot : shotList)
	{

		if (pShot->GetY() < 0) pShot->Delete();
	}
	shotList.delete_if(deleted);
	jetpack_enemies.delete_if(deleted);
	gun_enemies.delete_if(deleted);
	gun_enemy_shots.delete_if(deleted);
}

void CMyGame::phase_shield()
{
	
	if (IsKeyDown(SDLK_c) && shield_cooldown == 0)
	{
		shield_timer = 30;
		shieldsound.Play("explosion.wav");
		
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
			hit.Play("playerhit.wav");
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
	player.LoadImage("player_temp.bmp", CColor::Blue());
	player.SetImage("player_temp.bmp");
	
	startscreen.LoadImage("Startscreen.bmp");
	startscreen.SetImage("Startscreen.bmp");
	player.LoadImage("player_shield_temp.bmp", CColor::Red());
	
	endscreen.LoadImage("endscreen.bmp");
	endscreen.SetImage("endscreen.bmp");
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	startscreen.SetPosition(960, 540);	// exits the menu mode and starts the game mode
	music.Play("Music.wav", -1);
	music.Volume(0.3);
	underscore.Stop();
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	background.SetPosition(960, 540);
	gamewon = false;
	level_segment = 1;
	music.Stop();
	
	underscore.Play("underscore.wav", -1);
	underscore.Volume(0.8);
	
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
	for each (CSprite * pSpikes in theSpikes)
	{
		delete pSpikes;
	}
	player.SetPosition(960, 1000);
	theSpikes.clear();
	jetpack_enemies.clear();
	shield_enemies.clear();
	gun_enemies.clear();
	gun_enemy_shots.clear();
	shotList.clear();
	theSpikes.push_back(new CSprite(CRectangle(400, 0, 30, 1080), "spike_v.bmp", CColor::Black(), GetTime()));
	theSpikes.back()->Rotate(180);
	theSpikes.push_back(new CSprite(CRectangle(1430, 0, 30, 1080), "spike_v.bmp", CColor::Black(), GetTime()));
	platform.push_back(new CSprite(CRectangle(780, 950, 300, 30), "platform.bmp", CColor::Black(), GetTime()));
	

	hint = false;
	
	game_over = false;
	lives = 3;
	level = 5;
	jetpack_fuel = 100;
	shots = 5;
	
	attempts = 0;
	switch (nLevel)
	{
		case 0:
			// menu mode
			break;
		case 1: // level 1 add vertical spikes 
			// first layer of obstacles
			
			theSpikes.push_back(new CSprite(CRectangle(450, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(1200, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(730, 700, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			// second layer of obstacles
			jetpack_enemies.push_back(new CSprite(650, 550, "jetpack_cultist.bmp", CColor::Blue(), GetTime()));
			jetpack_enemies.back()->SetMotion(100, 0);
			jetpack_enemies.push_back(new CSprite(1200, 550, "jetpack_cultist.bmp", CColor::Blue(), GetTime()));
			jetpack_enemies.back()->SetMotion(-100, 0);
			


			// third layer of obstacles
			theSpikes.push_back(new CSprite(CRectangle(730, 350, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(450, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(1200, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			// fourth layer of obstacles
			gun_enemies.push_back(new CSprite(650, 200, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
			gun_enemies.push_back(new CSprite(1200, 200, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
			// fifth layer of obstacles
			theSpikes.push_back(new CSprite(CRectangle(730, 50, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
		

		break;
		case 2: // level 2
			// first layer of obstacles
			theSpikes.push_back(new CSprite(CRectangle(450, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(1200, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(730, 700, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			// second layer of obstacles
			shield_enemies.push_back(new CSprite(650, 550, "shield_cultist.bmp", CColor::Red(), GetTime()));
			shield_enemies.back()->SetMotion(100, 0);
			shield_enemies.push_back(new CSprite(1200, 550, "shield_cultist.bmp", CColor::Red(), GetTime()));
			shield_enemies.back()->SetMotion(-100, 0);


			// third layer of obstacles
			gun_enemies.push_back(new CSprite(750, 430, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
			gun_enemies.push_back(new CSprite(1100, 430, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(450, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(1200, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			theSpikes.push_back(new CSprite(CRectangle(730, 350, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			// fourth layer of obstacles
			gun_enemies.push_back(new CSprite(650, 200, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
			gun_enemies.push_back(new CSprite(1200, 200, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
			shield_enemies.push_back(new CSprite(650, 300, "shield_cultist.bmp", CColor::Red(), GetTime()));
			shield_enemies.back()->SetMotion(100, 0);
			shield_enemies.push_back(new CSprite(1200, 300, "shield_cultist.bmp", CColor::Red(), GetTime()));
			shield_enemies.back()->SetMotion(-100, 0);
			// fifth layer of obstacles
			theSpikes.push_back(new CSprite(CRectangle(730, 50, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
			break; 
			case 3: // level 3
				// first layer of obstacles
				theSpikes.push_back(new CSprite(CRectangle(450, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				theSpikes.push_back(new CSprite(CRectangle(1200, 700, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				theSpikes.push_back(new CSprite(CRectangle(730, 700, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				gun_enemies.push_back(new CSprite(750, 750, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
				gun_enemies.push_back(new CSprite(1100, 750, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
				// second layer of obstacles
				jetpack_enemies.push_back(new CSprite(650, 550, "jetpack_cultist.bmp", CColor::Blue(), GetTime()));
				jetpack_enemies.back()->SetMotion(100, 0);
				jetpack_enemies.push_back(new CSprite(1200, 550, "jetpack_cultist.bmp", CColor::Blue(), GetTime()));
				jetpack_enemies.back()->SetMotion(-100, 0);



				// third layer of obstacles
				gun_enemies.push_back(new CSprite(750, 400, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
				gun_enemies.push_back(new CSprite(1100, 400, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
				theSpikes.push_back(new CSprite(CRectangle(450, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				theSpikes.push_back(new CSprite(CRectangle(1200, 350, 200, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				theSpikes.push_back(new CSprite(CRectangle(730, 350, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				// fourth layer of obstacles
				gun_enemies.push_back(new CSprite(650, 200, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
				gun_enemies.push_back(new CSprite(1200, 200, "Gunboot_cultist.bmp", CColor::Blue(), GetTime()));
				shield_enemies.push_back(new CSprite(650, 300, "shield_cultist.bmp", CColor::Red(), GetTime()));
				shield_enemies.back()->SetMotion(100, 0);
				shield_enemies.push_back(new CSprite(1200, 300, "shield_cultist.bmp", CColor::Red(), GetTime()));
				shield_enemies.back()->SetMotion(-100, 0);
				//fifth layer of obstacles
				theSpikes.push_back(new CSprite(CRectangle(730, 150, 400, 30), "spike_h.bmp", CColor::Black(), GetTime()));
				// sixth layer of obstacles
				jetpack_enemies.push_back(new CSprite(650, 50, "jetpack_cultist.bmp", CColor::Blue(), GetTime()));
				jetpack_enemies.back()->SetMotion(100, 0);
				jetpack_enemies.push_back(new CSprite(1200, 50, "jetpack_cultist.bmp", CColor::Blue(), GetTime()));
				jetpack_enemies.back()->SetMotion(-100, 0);
				break;
			case 4: // end screen
				over.Play("wincon.wav");
				gamewon = true;
				endscreen.SetPosition(960, 540);
				underscore.Stop();
				music.Play("Music.wav", -1);
				music.Volume(0.3);
				GameOver();
				break;
				
	}
}

// called when the game is over
void CMyGame::OnGameOver()
{
	game_over = true;
	if (gamewon == false)
	{
		over.Play("gameover.wav");
	}
	
	
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

	if (IsMenuMode())
	{
		StartGame();
	}
	if (gamewon == true)
	{
		StopGame();
	}
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
