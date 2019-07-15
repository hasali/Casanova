#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <map>

class InputManager
{
public:
	static InputManager &getInstance() {
		static InputManager instance;
		return instance;
	}
	~InputManager();

	//Lazy way to do initial mapping, but note that it
	// does prevent multiple keyboard keys mapping to the
	// same game key.
	enum GameKey {
		GK_ENTER,
		GK_ESCAPE,
		GK_UP,
		GK_UP_ALT,
		GK_LEFT,
		GK_LEFT_ALT,
		GK_RIGHT,
		GK_RIGHT_ALT,
		GK_W,
		GK_SPACE,
		GK_L,
		GK_P,
		GK_COUNT
	};

private:
	InputManager();
	InputManager(InputManager const &); //No def
	InputManager &operator=(InputManager const &); //No def

public:
	bool isKeyDown(GameKey gk);
	bool wasKeyPressed(GameKey gk);
	bool wasKeyReleased(GameKey gk);
	bool wasMouseLeftPressed();
	bool wasMouseLeftReleased();
	sf::Vector2f getMousePos();
	void update(sf::RenderWindow& window);

private:
	std::map<GameKey, sf::Keyboard::Key> mKeyMap;
	std::map<sf::Keyboard::Key, bool> mCurrentKeyState;
	std::map<sf::Keyboard::Key, bool> mPreviousKeyState;
	bool mCurrentMouseLeftState;
	bool mPreviousMouseLeftState;
	sf::Vector2f mMousePos;
};

