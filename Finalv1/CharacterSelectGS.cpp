#include "CharacterSelectGS.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameplayGS.h"
#include <iostream>

CharacterSelectGS::CharacterSelectGS()
{
	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/char_select_bg2.png");
	if (tex == nullptr) {
		//Error loading background.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	sf::Texture * fDinoTex = TextureManager::getInstance().getAsset("Assets/Sprites/fdino_char_select.png");
	sf::Texture * mDinoTex = TextureManager::getInstance().getAsset("Assets/Sprites/mdino_char_select.png");
	if (fDinoTex == nullptr || mDinoTex == nullptr) {
		//Error loading background.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	// hardcoded
	mBackTxt.setPosition(400, 445);

	mBgSprite.setTexture(*tex);
	mFDinoSprite.setTexture(*fDinoTex);
	mMDinoSprite.setTexture(*mDinoTex);

	// hardcoded
	mFDinoSprite.setPosition(602.0f, 208.0f);
	mMDinoSprite.setPosition(790.0f, 185.0f);

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}

	int charDinoNameSize = 23;

	// default is female dino
	mFDinoName = "Cera";
	mMDinoName = "Littlefoot";

	mPlayerDinoNameTxt.setFont(*font);
	mPlayerDinoNameTxt.setCharacterSize(charDinoNameSize);
	mPlayerDinoNameTxt.setFillColor(sf::Color::Black);
	mPlayerDinoNameTxt.setStyle(sf::Text::Regular);

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

CharacterSelectGS::~CharacterSelectGS()
{
}

void CharacterSelectGS::Update(float delta)
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

	if (mFDinoSprite.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		mPlayerDinoNameTxt.setString(mFDinoName);	// mouse hovering over cera

		// hardcoded
		mPlayerDinoNameTxt.setPosition(700, 440);
	}
	else if (mMDinoSprite.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		mPlayerDinoNameTxt.setString(mMDinoName);	// mouse hovering over littlefoot
		
		// hardcoded
		mPlayerDinoNameTxt.setPosition(840, 440);
	}
	else {
		mPlayerDinoNameTxt.setString("");		// mouse not hovering over either dino
	}

	// go to gameplay GS once player chooses a dino

	if (InputManager::getInstance().wasMouseLeftReleased()){

		if (mFDinoSprite.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
			GameplayGS::getInstance().setChar(GameplayGS::eCharSelect::BLUE_DINO);
		}
		else if (mMDinoSprite.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
			GameplayGS::getInstance().setChar(GameplayGS::eCharSelect::PURPLE_DINO);
		}

		GameStateManager::getInstance().Change(GameplayGS::getInstance());
	}
}

void CharacterSelectGS::Draw(sf::RenderWindow & window)
{
	window.draw(mBgSprite);

	window.draw(mBackTxt);
	
	// only draw if mouse is on cera
	if (mFDinoSprite.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		window.draw(mFDinoSprite);
		window.draw(mPlayerDinoNameTxt);
	}
	
	// only draw if mouse is on littlefoot
	if (mMDinoSprite.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		window.draw(mMDinoSprite);
		window.draw(mPlayerDinoNameTxt);
	}
}

void CharacterSelectGS::Init()
{
}

void CharacterSelectGS::Deinit()
{
}

bool CharacterSelectGS::IsInit()
{
	return false;
}
