#include "SplashGS.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "AssetManager.h"
#include <iostream>

SplashGS::SplashGS()
{
	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/splash_bg.png");
	if (tex == nullptr) {
		//Error loading fonts.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}
	mSplashSprite.setTexture(*tex);
}

SplashGS::~SplashGS()
{
}

void SplashGS::Update(float delta)
{
	// Get keyboard key release to move to this state -> MainMenu
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ENTER)) {
		GameStateManager::getInstance().Pop();
	}
	// Splash -> Exit
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ESCAPE)) {
		GameStateManager::getInstance().Pop();
		GameStateManager::getInstance().Pop();
	}
}

void SplashGS::Draw(sf::RenderWindow & window)
{
	window.draw(mSplashSprite);
}

void SplashGS::Init()
{
}

void SplashGS::Deinit()
{
}

bool SplashGS::IsInit()
{
	return false;
}
