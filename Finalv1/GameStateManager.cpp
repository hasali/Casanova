#include "GameStateManager.h"
#include "GameState.h"
#include "InputManager.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
//GameStateManager *GameStateManager::theInstance = nullptr;

GameStateManager::GameStateManager()
{
	static int count = 0;
	++count;
}


GameStateManager::~GameStateManager()
{
	delete mMusic;
	mMusic = nullptr;
}

int GameStateManager::Play()
{
	//Create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Casanova");
	sf::Color clearColor = sf::Color::Black;

	//Run management
	bool running = true;

	//Clock management
	bool drawRequested = false;
	int updatesSinceDraw = 0;
	int const FRAME_SKIP = 5;
	sf::Clock clock;
	float const TGT_FPS = 30.0f;
	float const TGT_DELTA = 1.0f / TGT_FPS;
	sf::Time deltaTime = sf::seconds(TGT_DELTA);
	sf::Time clockTime = clock.getElapsedTime();
	sf::Time gameTime = clockTime;


	// music
	mMusic = new sf::Music;
	mMusic->openFromFile("Assets/Music/bgm.wav");
	mMusic->play();
	mMusic->setVolume(50);
	mMusic->setLoop(true);


	//Main Game Loop
	while (running) {
		//Reset stateful variables
		drawRequested = false;
		updatesSinceDraw = 0;

		//Event handling
		sf::Event ev;
		while (window.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::KeyReleased:
				break;
			}
		} //End event handling loop

		  //Game update (happens every TGT_DELTA seconds of gametime)
		while (updatesSinceDraw++ < FRAME_SKIP && (clockTime = clock.getElapsedTime()) > gameTime) {
			//Update game time and request a draw
			gameTime += deltaTime;
			drawRequested = true;

			//Update Input Manager
			InputManager::getInstance().update(window);
			//Update all entities in the game, remember that they should use TGT_DELTA
			Update(TGT_DELTA);
		} //End game update loop

		  //Draw to screen
		if (drawRequested) {

			Draw(window);

		} //End drawing code

		if (mStates.empty()) {
			//Everything is popped so exit
			running = false;
		}
	}

	return 0;
}

void GameStateManager::Update(float delta)
{
	//Update the top state in the stack
	if (!mStates.empty()) {
		mStates.back()->Update(delta);
	}
}

void GameStateManager::Draw(sf::RenderWindow & window)
{
	//Clear the window
	window.clear(sf::Color::Black);
	//Render drawables
	//TODO: Add opaque handling code.
	// Draw from the first Opaque state found starting from the top of the
	// stack and moving down, then draw that state and all states above it.
	if (!mStates.empty()) {
		for (std::vector<AGameState*>::reverse_iterator i = mStates.rbegin();
			i != mStates.rend(); ++i) {
			// found first opaque
			if ((*i)->isOpaque()) {	
				bool match = false;
				for (std::vector<AGameState*>::iterator j = mStates.begin(); j != mStates.end(); j++) {
					if (*j == *i) {
						match = true;						
					}
					// draw first opaque and everything above it
					if (match) {
						(*j)->Draw(window);
					}
				}
				break;
			}
		}
	}

	//Show the window
	window.display();
}

void GameStateManager::Pop()
{
	if(!mStates.empty()) {
		mStates.back()->Deinit();
		mStates.pop_back();
	}
	if (!mStates.empty()) {
		mStates.back()->Resume();
	}
}

void GameStateManager::Push(AGameState & newState)
{
	if (!mStates.empty()) {
		mStates.back()->Pause();
	}
	newState.Init();
	//Call newState.Resume() iff newState.Init() doesn't
	// explicitly put the state in the non-paused state
	mStates.push_back(&newState);
}

void GameStateManager::Change(AGameState & newState)
{
	Pop();
	Push(newState);
}

void GameStateManager::PopAllThenPush(AGameState & newState)
{
	while (!mStates.empty()) {
		Pop();
	}
	Push(newState);
}
