#include "InputManager.h"

InputManager::InputManager() 
{
	mKeyMap[GK_ENTER] = sf::Keyboard::Key::Return;
	mKeyMap[GK_ESCAPE] = sf::Keyboard::Key::Escape;
	mKeyMap[GK_UP] = sf::Keyboard::Key::Up;
	mKeyMap[GK_UP_ALT] = sf::Keyboard::Key::W;
	mKeyMap[GK_LEFT] = sf::Keyboard::Key::Left;
	mKeyMap[GK_LEFT_ALT] = sf::Keyboard::Key::A;
	mKeyMap[GK_RIGHT] = sf::Keyboard::Key::Right;
	mKeyMap[GK_RIGHT_ALT] = sf::Keyboard::Key::D;
	mKeyMap[GK_W] = sf::Keyboard::Key::W;
	mKeyMap[GK_SPACE] = sf::Keyboard::Key::Space;
	mKeyMap[GK_L] = sf::Keyboard::Key::L;
	mKeyMap[GK_P] = sf::Keyboard::Key::P;

}
InputManager::~InputManager()
{
}

bool InputManager::isKeyDown(GameKey gk)
{
	return mCurrentKeyState[mKeyMap[gk]];
}

bool InputManager::wasKeyPressed(GameKey gk)
{
	return !mPreviousKeyState[mKeyMap[gk]] && mCurrentKeyState[mKeyMap[gk]];
}

bool InputManager::wasKeyReleased(GameKey gk)
{
	return mPreviousKeyState[mKeyMap[gk]] && !mCurrentKeyState[mKeyMap[gk]];
}

bool InputManager::wasMouseLeftPressed()
{
	return !mPreviousMouseLeftState && mCurrentMouseLeftState;
}

bool InputManager::wasMouseLeftReleased()
{
	return mPreviousMouseLeftState && !mCurrentMouseLeftState;
}

sf::Vector2f InputManager::getMousePos()
{
	return mMousePos;
}

void InputManager::update(sf::RenderWindow& window)
{
	mCurrentKeyState.swap(mPreviousKeyState);
	mPreviousMouseLeftState = mCurrentMouseLeftState;

	for (int k = 0; k < GK_COUNT; ++k) {
		sf::Keyboard::Key sfk = mKeyMap[(GameKey)k];
		mCurrentKeyState[sfk] = sf::Keyboard::isKeyPressed(sfk);
	}
	mCurrentMouseLeftState = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	mMousePos = sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
}
