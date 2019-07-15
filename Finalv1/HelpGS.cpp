#include "HelpGS.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include <iostream>

HelpGS::HelpGS()
{
	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/help_bg.png");
	if (tex == nullptr) {
		//Error loading background.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	mBgSprite.setTexture(*tex);

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}
	int charSize = 25;

	mBackTxt.setString("Back to Main Menu");

	mBackTxt.setFont(*font);
	mBackTxt.setCharacterSize(charSize);
	mBackTxt.setFillColor(sf::Color::Black);
	mBackTxt.setOutlineColor(sf::Color::White);
	mBackTxt.setStyle(sf::Text::Regular);

	// hardcoded
	mBackTxt.setPosition(400, 445);
}

HelpGS::~HelpGS()
{
}

void HelpGS::Update(float delta)
{
	float highlightedThickness = 2.0f;
	
	mBackTxt.setOutlineThickness(0.0f);
	
	if (mBackTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		mBackTxt.setOutlineThickness(highlightedThickness);
	}

	// go back to main menu GS if player clicks Back
	if (InputManager::getInstance().wasMouseLeftReleased() && mBackTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Pop();
	}
}

void HelpGS::Draw(sf::RenderWindow & window)
{
	window.draw(mBgSprite);
	window.draw(mBackTxt);
}

void HelpGS::Init()
{
}

void HelpGS::Deinit()
{
}

bool HelpGS::IsInit()
{
	return false;
}
