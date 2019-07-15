#include "EnterNameGS.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "HighScoresGS.h"
#include <iostream>
#include <algorithm>
#include "string.h"
#include "GameplayGS.h"

#include "tinyxml2.h"

EnterNameGS::EnterNameGS()
{
	// change the background to something else
	sf::Texture * bgTex = TextureManager::getInstance().getAsset("Assets/Backgrounds/enter_name_bg2.png");
	if (bgTex == nullptr) {
		//Error loading background.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	mBgSprite.setTexture(*bgTex);

	mInitialsTxt.push_back(&mFirstLetter);
	mInitialsTxt.push_back(&mSecondLetter);
	mInitialsTxt.push_back(&mThirdLetter);

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}
	int charSize = 35;
	int charSizeCont = 25;

	mContinueTxt.setString("Continue");

	mContinueTxt.setFont(*font);
	mContinueTxt.setCharacterSize(charSizeCont);
	mContinueTxt.setFillColor(sf::Color::Black);
	mContinueTxt.setOutlineColor(sf::Color::White);
	mContinueTxt.setStyle(sf::Text::Regular);

	// hardcoded
	mContinueTxt.setPosition(450, 445);

	mCurrLetterVal = 65; // A
	offset = 0;
	mLetterTxt.setString(std::string() + char(mCurrLetterVal));
	mLetterTxt.setFont(*font);
	mLetterTxt.setCharacterSize(charSize);
	mLetterTxt.setFillColor(sf::Color::White);
	//mContinueTxt.setOutlineColor(sf::Color::White);
	mLetterTxt.setStyle(sf::Text::Bold);

	mLetterTxt.setPosition(162,275);

	for (int i = 0; i < mInitialsTxt.size(); i++) {
		mInitialsTxt[i]->setFont(*font);
		mInitialsTxt[i]->setCharacterSize(charSize);
		mInitialsTxt[i]->setFillColor(sf::Color::White);
		mInitialsTxt[i]->setOutlineColor(sf::Color::Black);
		mInitialsTxt[i]->setStyle(sf::Text::Bold);
	}

	mFirstLetter.setPosition(110,325);
	mSecondLetter.setPosition(162, 325);
	mThirdLetter.setPosition(215, 325);

	mFirstLetter.setOutlineThickness(2.0f);
	mSecondLetter.setOutlineThickness(2.0f);
	mThirdLetter.setOutlineThickness(2.0f);
}

EnterNameGS::~EnterNameGS()
{
}

void EnterNameGS::Update(float delta)
{
	float highlightedThickness = 2.0f;

	mContinueTxt.setOutlineThickness(0.0f);

	if (mContinueTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		mContinueTxt.setOutlineThickness(highlightedThickness);
	}

	// only allow player to scroll through letters
	// while there are initials to enter
	if (mThirdLetter.getOutlineThickness() > 0.0f) {
		if (InputManager::getInstance().wasKeyReleased(InputManager::GK_RIGHT)) {
			offset++;
		}

		if (InputManager::getInstance().wasKeyReleased(InputManager::GK_LEFT)) {
			offset = (offset == 0) ? 25 : --offset;
		}
		offset %= 26;
		mCurrLetterVal = 65 + offset;
		mLetterTxt.setString(std::string() + char(mCurrLetterVal));
	}
	

	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_ENTER)) {
		mLetterTxt.setString("A");
		offset = 0;

		if (mFirstLetter.getOutlineThickness() > 0.0f) {
			mFirstLetter.setOutlineThickness(0.0f);
			mSecondLetter.setOutlineThickness(2.0f);
		}
		else if (mSecondLetter.getOutlineThickness() > 0.0f) {
			mSecondLetter.setOutlineThickness(0.0f);
			mThirdLetter.setOutlineThickness(2.0f);
		}
		else if (mThirdLetter.getOutlineThickness() > 0.0f) {
			mThirdLetter.setOutlineThickness(0.0f);
		}
	}

	if (mFirstLetter.getOutlineThickness() > 0.0f) {
		mFirstLetter.setString(mLetterTxt.getString());
	}
	else if (mSecondLetter.getOutlineThickness() > 0.0f) {
		mSecondLetter.setString(mLetterTxt.getString());
	}
	else if (mThirdLetter.getOutlineThickness() > 0.0f) {
		mThirdLetter.setString(mLetterTxt.getString());
	}

	// go back to high scores GS if player clicks Continue
	if (InputManager::getInstance().wasMouseLeftReleased() && mContinueTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos()) &&
		mThirdLetter.getOutlineThickness() == 0.0f){


		// ALISSA - high score, set it in appropriate place in XML
		//XML
		//XML tutorial
		using namespace tinyxml2;
		XMLDocument doc;
		bool newHighScoreSet = false;

		//int newHighScore = -1;
		int oldHighScore = -1;
		int tempOldHighScore = -1;

		std::string newName = "";
		std::string oldName = "";
		std::string tempOldName = "";

		if (doc.LoadFile("GameData/casanova_game_data_edited.xml")) {
			//An error occurred
			std::cout << "Error loading XML file" << std::endl;
			//return 1;
		}
		XMLElement * gameDataEl = doc.FirstChildElement("game_data");
		if (gameDataEl == nullptr) {
			//An error occurred
			std::cout << "Error finding game_data element" << std::endl;
			//return 1;
		}
		XMLElement * highScoreEl = gameDataEl->FirstChildElement("high_score");
		while (highScoreEl != nullptr) {

			XMLElement *scoreEl = highScoreEl->FirstChildElement("score");
			//char buffer[100];
			if (scoreEl != nullptr) {
				//score element exists

				if (GameplayGS::getInstance().getScore() > atoi(scoreEl->GetText()) && !newHighScoreSet) {
					
					// keep track of the old high score to compare it with the other high scores
					oldHighScore = atoi(scoreEl->GetText());

					// new high score; assign it to the appropriate score node
					scoreEl->SetText(std::to_string(GameplayGS::getInstance().getScore()).c_str());

					XMLElement *nameEl = highScoreEl->FirstChildElement("name");

					// keep track of the old name to associate it with the old score
					oldName = nameEl->GetText();
					
					// assign name to the appropriate name node
					newName = mFirstLetter.getString() + mSecondLetter.getString() + mThirdLetter.getString();
					nameEl->SetText(newName.c_str());

					newHighScoreSet = true;
				}
				else {
					// compare the old score with the other high scores
					if (oldHighScore >= atoi(scoreEl->GetText())) {

						tempOldHighScore = atoi(scoreEl->GetText());
						scoreEl->SetText(std::to_string(oldHighScore).c_str());
						oldHighScore = tempOldHighScore;

						XMLElement *nameEl = highScoreEl->FirstChildElement("name");

						tempOldName = nameEl->GetText();

						nameEl->SetText(oldName.c_str());

						oldName = tempOldName;
					}
				}
			}

			//Get next element if available
			highScoreEl = highScoreEl->NextSiblingElement("high_score");
		}
		doc.SaveFile("GameData/casanova_game_data_edited.xml");

		// reset values for initials
		for (int i = 0; i < mInitialsTxt.size(); i++) {
			mInitialsTxt[i]->setString(i == 0 ? "A" : "");
			mInitialsTxt[i]->setOutlineThickness(2.0f);
		}

		//GameStateManager::getInstance().Pop();
		//Change = Pop then push
		// pushing here instead
		GameStateManager::getInstance().Change(HighScoresGS::getInstance());
	}
}

void EnterNameGS::Draw(sf::RenderWindow & window)
{
	window.draw(mBgSprite);
	
	window.draw(mLetterTxt);

	if (mThirdLetter.getOutlineThickness() == 0.0f) {
		// player is done entering initials
		// show continue text
		window.draw(mContinueTxt);
	}
	
	for (int i = 0; i < mInitialsTxt.size(); i++) {
		window.draw(*mInitialsTxt[i]);
	}
}

void EnterNameGS::Init()
{
}

void EnterNameGS::Deinit()
{
}

bool EnterNameGS::IsInit()
{
	return false;
}