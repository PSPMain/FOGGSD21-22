#define MUNCHIECOUNT 50
#define GHOSTCOUNT 1
#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;


struct Player
{
	bool dead;
	float speedMultiplyer;
	int currentFrameTime;
	int direction;
	int frame;
	Rect* sourceRect;
	Texture2D* texture;
	Vector2* position;
	
};

struct Enemy
{
	Rect* rect;
	Texture2D* blueTexture;
	Texture2D* invertedTexture;
	int frame;
	int frameCount;
	int frameTime;
	int currentFrameTime;
	Vector2* position;
	bool rKeyDown;

};

struct movingEnemy
{
	Vector2* position;
	Texture2D* texture;
	Rect* sourceRect;
	int direction;
	float speed;
};

struct Menu
{
	/*Texture2D* background;
	Rect* rectangle;*/
	//Vector2* stringPosition;
	bool started;
	bool paused;
	bool pKeyDown;
};


// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	// Data to represent Pacman
	Player* _pacman;
	Player* position;
	Player* sourceRect;
	Player* texture;
	Player* direction;
	Player* frame;
	Player* currentFrameTime;
	Player* speedMultiplyer;
	const int _cPacmanFrameTime;

	int _frameCount;

	// Data to represent Munchie 
	Enemy* _munchie[MUNCHIECOUNT];
	//Enemy* rect;
	//Enemy* blueTexture;
	//Enemy* invertedTexture;
	//Enemy* frame;
	//Enemy* currentFrameTime;
	const int _cMunchieFrameTime;

	movingEnemy* _ghosts[GHOSTCOUNT];

	Enemy* _cherry;
	const int _ccherryFrameTime;

	// Position for String
	Vector2* _stringPosition;

	//constant data for game variables
	const float _cPacmanSpeed;

	//data for menu
	Menu* _menu;
	Texture2D* background;
	Rect* rectangle;
	/*Menu* background;
	Menu* rectangle;*/

	/*Menu* stringPosition;*/
	Vector2* stringPosition;
	Menu* started;
	Menu* paused;
	Menu* pKeyDown;

	void CheckGhostCollisions();
	void UpdateGhost(movingEnemy* ghost, int elapsedTime);

	void Input(int elapsedTime, Input::KeyboardState* State, Input::MouseState* mouseState);

	void CheckPaused(Input::KeyboardState* state, Input::Keys pausedKey);
	void CheckViewportCollision();

	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);
	void UpdateCherry(int elapsedTime);

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};