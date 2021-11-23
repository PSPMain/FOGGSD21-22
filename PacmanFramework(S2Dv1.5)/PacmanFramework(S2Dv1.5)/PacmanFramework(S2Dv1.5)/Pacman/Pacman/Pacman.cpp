#include "Pacman.h"
#include<time.h>
#include <sstream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cPacmanSpeed(0.1f),_cPacmanFrameTime(250),_cMunchieFrameTime(500),_ccherryFrameTime(500)
{

	_frameCount = 0;

	_pacman = new Player();
	_pacman->dead = false;
	_pacman-> direction = 0;
	_pacman-> currentFrameTime = 0;
	_pacman-> frame = 0;
	_pacman->speedMultiplyer = 1.0f;

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchie[i] = new Enemy();
		_munchie[i]->frameCount = rand() % 1;
		_munchie[i]->currentFrameTime = 0;
		_munchie[i]->frameTime = rand() % 500 + 50;
	}

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i] = new movingEnemy();
		_ghosts[i]->direction = 0;
		_ghosts[i]->speed = 0.2f;
	}

	_cherry = new Enemy();
	_cherry->currentFrameTime = 0;
	_cherry ->rKeyDown = false;

	_menu = new Menu();
	_menu->paused = false;
	_menu->pKeyDown = false;

	Input::MouseState* mouseState = Input::Mouse::GetState();

	//Initialise important Game aspects

	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);

	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop 
	Graphics::StartGameLoop();

}


Pacman::~Pacman()
{
	delete _pacman->texture;
	delete _pacman->sourceRect;
	delete _pacman->position;
	delete _pacman;

	delete _munchie[0]->blueTexture;
	delete _munchie[0]->invertedTexture;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		delete _munchie[i]->rect;
		delete _munchie[i]->position;
		delete _munchie[i];
	}
	delete[] _munchie;

	delete _cherry->blueTexture;
	delete _cherry->invertedTexture;
	delete _cherry->rect;
	delete _cherry;

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		delete _ghosts[i]->position;
		delete _ghosts[i]->sourceRect;
		delete _ghosts[i]->texture;
		delete _ghosts[i];
	}
	delete _ghosts[0]->texture;
	delete[] _ghosts;
}


void Pacman::LoadContent()
{
	// Load Pacman
	_pacman-> texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Vector2(350.0f, 350.0f);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	// Load Ghost
	Texture2D* ghostTex = new Texture2D();
	ghostTex->Load("Textures/GhostBlue1.png", false);
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->texture = ghostTex;
		_ghosts[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		_ghosts[i]->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	} 

	// Load Munchie
	Texture2D* munchieTex = new Texture2D();
	munchieTex->Load("Textures/Munchie.tga", false);
	Texture2D* munchieInvertedTex = new Texture2D();
	munchieInvertedTex->Load("Textures/MunchieInverted.tga", false);
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchie[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		_munchie[i]->blueTexture = munchieTex;
		_munchie[i]->invertedTexture = munchieInvertedTex;
		_munchie[i]->rect = new Rect(100.0f, 450.0f, 12, 12);
	}


	//load cherry
	_cherry->blueTexture = new Texture2D();
	_cherry->blueTexture->Load("Textures/Cherry.PNG", true);
	_cherry->invertedTexture = new Texture2D();
	_cherry->invertedTexture->Load("Textures/CherryInverted.PNG", true);
	_cherry->rect = new Rect(100.0f, 450.0f, 32, 32);
	_cherry->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	// Set Menu Paramters
	background = new Texture2D();
	background->Load("Textures/Transparency.png", false);
	rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);
}


void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	_frameCount++;

	if (!started)
	{
		if (keyboardState->IsKeyDown(Input::Keys::RETURN))
		{
			_menu->started = true;
		}
	}

	CheckPaused(keyboardState, Input::Keys::P);

	if (!paused)
	{
		/*_frameCount++;*/

		Input(elapsedTime, keyboardState, Input::Mouse::GetState());
		
		CheckViewportCollision();

		UpdatePacman(elapsedTime);

		UpdateMunchie(elapsedTime);
		
		UpdateCherry(elapsedTime);

		for (int i = 0; i < GHOSTCOUNT; i++)
		{
			UpdateGhost(_ghosts[i], elapsedTime);
		}
		CheckGhostCollisions();
	}
}


void Pacman::Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState)
{
	float pacmanSpeed = _cPacmanSpeed * elapsedTime * _pacman->speedMultiplyer;

	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	/*Input::MouseState* mouseState = Input::Mouse::GetState();*/

	if (keyboardState->IsKeyDown(Input::Keys::R))
	{
		_cherry->rect = new Rect((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()),32,32);
	}

	if (keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT))
	{
		//apply multiplyer
		_pacman->speedMultiplyer = 2.0f;
	}
	else
	{
		_pacman->speedMultiplyer = 1.0f;
	}

	// Checks if D key is pressed
	if (state->IsKeyDown(Input::Keys::D))
	{
		_pacman->position->X += pacmanSpeed; //Moves Pacman across X axis
		_pacman->direction = 0;
	}
	else if (state->IsKeyDown(Input::Keys::A))
	{
		_pacman->position->X -= pacmanSpeed; //Moves Pacman across X axis
		_pacman->direction = 2;
	}
	else if (state->IsKeyDown(Input::Keys::S))
	{
		_pacman->position->Y += pacmanSpeed; //Moves Pacman across Y axis
		_pacman->direction = 1;
	}
	else if (state->IsKeyDown(Input::Keys::W))
	{
		_pacman->position->Y -= pacmanSpeed; //Moves Pacman across Y axis
		_pacman->direction = 3;
	}
	//handle mouse input-reposition cherry
	if (mouseState->LeftButton == Input::ButtonState::PRESSED)
	{
		_cherry->rect->X = mouseState->X;
		_cherry->rect->Y = mouseState->Y;
	}
}


void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pausedKey)
{
	//checks is the p key is pressed
	if (state->IsKeyDown(Input::Keys::P) && !pKeyDown)
	{
		_menu->pKeyDown = true;
		_menu->paused = !paused;
	}
	if (state->IsKeyUp(Input::Keys::P))
	{
		_menu->pKeyDown = false;
	}
}


void Pacman::CheckViewportCollision()
{
	//Checks if pacman is trying to disapear
	if (_pacman->position->X + _pacman->sourceRect->Width > Graphics::GetViewportWidth())
	{
		//pacman hits the right wall-resets his position
		_pacman->position->X = (Graphics::GetViewportWidth() - Graphics::GetViewportWidth()) - _pacman->sourceRect->Width;
	}
	else if (_pacman->position->X + _pacman->sourceRect->Width < (Graphics::GetViewportWidth() - Graphics::GetViewportWidth()))
	{
		_pacman->position->X = Graphics::GetViewportWidth() - _pacman->sourceRect->Width;
	}
	else if (_pacman->position->Y + _pacman->sourceRect->Height > Graphics::GetViewportHeight())
	{
		_pacman->position->Y = (Graphics::GetViewportHeight() - Graphics::GetViewportHeight()) - _pacman->sourceRect->Height;
	}
	else if (_pacman->position->Y + _pacman->sourceRect->Height < (Graphics::GetViewportHeight() - Graphics::GetViewportHeight()))
	{
		_pacman->position->Y = Graphics::GetViewportHeight() - _pacman->sourceRect->Height;
	}
}


void Pacman::UpdatePacman(int elapsedTime)
{
	_pacman->currentFrameTime += elapsedTime;

	if (_pacman->currentFrameTime > _cPacmanFrameTime)
	{
		_pacman->frame++;
		if (_pacman->frame >= 2)
		{
			_pacman->frame = 0;
		}
		_pacman->currentFrameTime = 0;

		_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
		_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;

	}
}


void Pacman::CheckGhostCollisions()
{
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;

	for (i = 0; i < GHOSTCOUNT; i++)
	{
		//populate variables with Ghost data
		bottom2 = _ghosts[i]->position->Y + _ghosts[i]->sourceRect->Height;
		left2 = _ghosts[i] -> position->X;
		right2 = _ghosts[i]->position->X + _ghosts[i]->sourceRect->Width;
		top2 = _ghosts[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			_pacman->dead = true;
			i = GHOSTCOUNT;
		}
	}
}


void Pacman::UpdateGhost(movingEnemy* ghost, int elapsedTime)
{
	if (ghost->direction == 0)
	{
		ghost->position->X += ghost->speed * elapsedTime;
	}
	else if (ghost->direction == 1)
	{
		ghost->position->X -= ghost->speed * elapsedTime;
	}
	if (ghost->position->X + ghost->sourceRect->Width >= Graphics::GetViewportWidth())
	{
		ghost->direction = 1;
	}
	else if (ghost->position->X <= 0)
	{
		ghost->direction = 0;
	}
	ghost->sourceRect->X = ghost->sourceRect->Width * ghost->direction;
	
}


void Pacman::UpdateMunchie(int elapsedTime)
{
	//_munchie->currentFrameTime += elapsedTime;

	//if (_munchie->currentFrameTime > _cMunchieFrameTime)
	//{
	//	_frameCount++;
	//	if (_frameCount >= 1)
	//	{
	//		_frameCount = 0;
	//	}
	//	_munchie->currentFrameTime = 0;
	//}
}


void Pacman::UpdateCherry(int elapsedTime)
{
	_cherry->currentFrameTime += elapsedTime;
	if (_cherry->currentFrameTime > _ccherryFrameTime)
	{
		_frameCount++;
		if (_frameCount >= 1)
		{
			_frameCount = 0;
		}
		_cherry->currentFrameTime = 0;
	}
}


void Pacman::Draw(int elapsedTime)
{
	
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacman->position->X << " Y: " << _pacman->position->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	if (!_pacman->dead)
	{
		SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman
	}

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		SpriteBatch::Draw(_ghosts[i]->texture, _ghosts[i]->position, _ghosts[i]->sourceRect);
	}

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		if (_frameCount == 0)
		{
			// Draws Red Munchie
			SpriteBatch::Draw(_munchie[i]->invertedTexture, _munchie[i]->rect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
			SpriteBatch::Draw(_cherry->invertedTexture, _cherry->rect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
		}
		else
		{
			// Draw Blue Munchie
			SpriteBatch::Draw(_munchie[i]->blueTexture, _munchie[i]->rect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
			SpriteBatch::Draw(_cherry->blueTexture, _cherry->rect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
		}
	}

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	if (paused)
	{
		std::stringstream menuStream; menuStream << "PAUSED!";
		SpriteBatch::Draw(background, rectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), stringPosition, Color::Red);
	}


	SpriteBatch::EndDraw(); // Ends Drawing

}