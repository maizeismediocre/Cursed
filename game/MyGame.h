#pragma once

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite player;
	CSpriteList theSpikes;
	CSpriteList platform;
	CSprite background;
	CSpriteList shotList;
	CSpriteList jetpack_enemies; // jet pack enemy
	CSpriteList gun_enemies; // gun boot enemy
	CSpriteList gun_enemy_shots; // gun boot enemy shots
	//sounds

	// ints and bools
	bool is_falling;
	bool game_over;
	bool is_shielded;

	bool hint;
	 int level_segment;
	 int jetpack_fuel;
	 int shield_timer;
	 int shots;
	 int lives;
	 int shot_timer;
	 int level;
	 int attempts;
	 int shield_cooldown;
	// member functions
	void Playercontrol();
	void Enemycontrol();
	
	void shotcontrol();
	void phase_shield();
	void spikes();
public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
