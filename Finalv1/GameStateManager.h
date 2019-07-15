#pragma once
#include <vector>
#include <SFML\Audio.hpp>

class AGameState;
namespace sf {
	class RenderWindow;
}

class GameStateManager
{
private:
	std::vector<AGameState *> mStates;
	sf::Music *mMusic;
	//static GameStateManager *theInstance;
public:
	static GameStateManager &getInstance() {
	/*
		if (theInstance == nullptr) {
			theInstance = new GameStateManager();
		}
		return *theInstance;
	*/
		static GameStateManager instance;
		return instance;
	}


	// sounds better when the music keeps going than actually stopping the music
	// and startinga ll over
	void playBGMusic() {
		mMusic->setVolume(50);
	}

	void stopBGMusic() {
		mMusic->setVolume(0);
	}

	int const WINDOW_WIDTH = 1000;
	int const WINDOW_HEIGHT = 500;

private:
	GameStateManager();
	GameStateManager(GameStateManager const &);
	GameStateManager &operator=(GameStateManager const &);


public:
	~GameStateManager();
	//Main program loop, run after any setup is done in main.
	int Play(); 
	void Update(float delta);
	void Draw(sf::RenderWindow &window);
	//GameState stack management
	void Pop();
	void Push(AGameState &newState);
	void Change(AGameState &newState);
	void PopAllThenPush(AGameState &newState);
};

