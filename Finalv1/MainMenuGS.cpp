#include "MainMenuGS.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "SplashGS.h"
#include "CharacterSelectGS.h"
#include "SettingsGS.h"
#include "HelpGS.h"
#include "HighScoresGS.h"
#include "AssetManager.h"
#include <iostream>

MainMenuGS::MainMenuGS()
{
	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/menu_bg.png");
	if (tex == nullptr) {
		//Error loading background.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	mBgSprite.setTexture(*tex);

	mAllTxt.push_back(&mStartTxt);
	mAllTxt.push_back(&mSettingsTxt);
	mAllTxt.push_back(&mHelpTxt);
	mAllTxt.push_back(&mHighScoresTxt);
	mAllTxt.push_back(&mQuitTxt);

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}

	int charSize = 40;
	int hOffset = 10;
	int vOffset = 5;
	int rowDiv = GameStateManager::getInstance().WINDOW_HEIGHT / 7;
	int margin = GameStateManager::getInstance().WINDOW_WIDTH / 6 + hOffset;

	mStartTxt.setString("Start");
	mSettingsTxt.setString("Settings");
	mHelpTxt.setString("Help");
	mHighScoresTxt.setString("High Scores");
	mQuitTxt.setString("Quit");

	for (int i = 0; i < mAllTxt.size(); i++) {
		mAllTxt[i]->setFont(*font);
		mAllTxt[i]->setCharacterSize(charSize);
		mAllTxt[i]->setFillColor(sf::Color::White);
		mAllTxt[i]->setOutlineColor(sf::Color::Black);
		mAllTxt[i]->setStyle(sf::Text::Regular);
		mAllTxt[i]->setOrigin(mAllTxt[i]->getLocalBounds().width / 2, mAllTxt[i]->getLocalBounds().height);
		mAllTxt[i]->setPosition((float)margin, (float)(rowDiv * (i + 1)) + vOffset);
	}
}


MainMenuGS::~MainMenuGS()
{
}

void MainMenuGS::Update(float delta)
{
	float highlightedThickness = 2.0f;
	for (int i = 0; i < mAllTxt.size(); i++) {
		mAllTxt[i]->setOutlineThickness(0.0f);
	}

	for (int i = 0; i < mAllTxt.size(); i++) {
		if (mAllTxt[i]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
			mAllTxt[i]->setOutlineThickness(highlightedThickness);
		}
	}

	// do we need this? should we keep it?
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ESCAPE)) {
		GameStateManager::getInstance().Push(SplashGS::getInstance());
	}

	// go to character select GS if player clicks Start
	if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[0]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Push(CharacterSelectGS::getInstance());
	}

	// go to settings GS if player clicks Settings
	if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[1]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Push(SettingsGS::getInstance());
	}

	// go to help GS if player clicks Help
	if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[2]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Push(HelpGS::getInstance());
	}

	// go to high scores GS if player clicks High Scores
	if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[3]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Push(HighScoresGS::getInstance());
	}

	// exit the game if player clicks Quit
	// need to clean up resources first?
	if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[4]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Pop();
	}
}

void MainMenuGS::Draw(sf::RenderWindow & window)
{
	window.draw(mBgSprite);
	for (int i = 0; i < mAllTxt.size(); i++) {
		window.draw(*mAllTxt[i]);
	}
}

void MainMenuGS::Init()
{
}

void MainMenuGS::Deinit()
{
	
}

bool MainMenuGS::IsInit()
{
	return false;
}
