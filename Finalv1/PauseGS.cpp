#include "GameplayGS.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "AssetManager.h"
#include "PauseGS.h"
#include <iostream>

PauseGS::PauseGS() : AGameState(false)
{
	sf::Texture * pauseTex = TextureManager::getInstance().getAsset("Assets/Backgrounds/pause_bg.png");
	if (pauseTex == nullptr) {
		//Error loading fonts.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}
	mPauseSprite.setTexture(*pauseTex);
}

PauseGS::~PauseGS()
{
}

void PauseGS::Update(float delta)
{
	// Press 'P' to unpause
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_P)) {
		GameStateManager::getInstance().Pop();
	}
}

void PauseGS::Draw(sf::RenderWindow & window)
{
	window.draw(mPauseSprite);
}

void PauseGS::Init()
{
}

void PauseGS::Deinit()
{
}

bool PauseGS::IsInit()
{
	return false;
}
