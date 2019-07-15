#include "MainMenuGS.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "AssetManager.h"
#include "GameOverGS.h"
#include "HighScoresGS.h"
#include "EnterNameGS.h"
#include <iostream>

GameOverGS::GameOverGS()
{
	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/game_over_bg.png");
	if (tex == nullptr) {
		//Error loading fonts.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}
	mGameOverSprite.setTexture(*tex);

	/*mAllTxt.push_back(&mGameOverTxt);
	mAllTxt.push_back(&mContinueTxt);*/

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}

	int charSize = 25;
	int hOffset = 10;
	int vOffset = 5;
	int rowDiv = GameStateManager::getInstance().WINDOW_HEIGHT / 6;
	int colDiv = GameStateManager::getInstance().WINDOW_WIDTH / 6;

	mContinueTxt.setString("Continue");

	mContinueTxt.setFont(*font);
	mContinueTxt.setCharacterSize(charSize);
	mContinueTxt.setFillColor(sf::Color::Black);
	mContinueTxt.setOutlineColor(sf::Color::White);
	mContinueTxt.setStyle(sf::Text::Regular);

	// hardcoded
	mContinueTxt.setPosition(450, 445);
}


GameOverGS::~GameOverGS()
{
}

void GameOverGS::Update(float delta)
{
	float highlightedThickness = 2.0f;
	mContinueTxt.setOutlineThickness(0.0f);

	if (mContinueTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		mContinueTxt.setOutlineThickness(highlightedThickness);
	}

	if (InputManager::getInstance().wasMouseLeftReleased() && mContinueTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Pop();		// pop game over GS
		GameStateManager::getInstance().Pop();		// pop gameplay GS; main menu GS is left
		if (mNewHighScore) {
			// commented out bc scores have to be saved into xml first
			// high scores cant be reading before saving
			// pushing in EnterNameGS instead
			//GameStateManager::getInstance().Push(HighScoresGS::getInstance());
			GameStateManager::getInstance().Push(EnterNameGS::getInstance());
		}
	}

	// Press 'P' to unpause
	//if (InputManager::getInstance().wasKeyReleased(InputManager::GK_P)) {
	//	GameStateManager::getInstance().Pop();
	//}
}

void GameOverGS::Draw(sf::RenderWindow & window)
{
	window.draw(mGameOverSprite);
	window.draw(mContinueTxt);
}

void GameOverGS::Init()
{
}

void GameOverGS::Deinit()
{
}

bool GameOverGS::IsInit()
{
	return false;
}
