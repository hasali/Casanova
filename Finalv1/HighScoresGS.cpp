#include "HighScoresGS.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include <iostream>

#include "tinyxml2.h"


// CURRENTLY THE SAME CODE AS HELPGS.CPP B/C NO XML IMPLEMENTATION YET
HighScoresGS::HighScoresGS()
{
	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/high_scores_bg.png");
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



	//XML tutorial
	//using namespace tinyxml2;
	//XMLDocument doc;
	//if (doc.LoadFile("SaveGames.xml")) {
	//	//An error occurred
	//	std::cout << "Error loading XML file" << std::endl;
	//	return 1;
	//}
	//XMLElement * savesEl = doc.FirstChildElement("Saves");
	//if (savesEl == nullptr) {
	//	//An error occurred
	//	std::cout << "Error finding Saves element" << std::endl;
	//	return 1;
	//}
	//XMLElement * saveEl = savesEl->FirstChildElement("Save");
	//while (saveEl != nullptr) {
	//	//Process the current saveEl
	//	//Process level attribute
	//	int level;
	//	//This way is okay when you want to just carry on with a default
	//	level = saveEl->IntAttribute("level", -1);
	//	//This way is better for when you need to decide what to do when no value or error
	//	if (saveEl->QueryIntAttribute("level", &level)) {
	//		//An error occurred, handle it here
	//	}
	//	//Process inner AMMO element
	//	XMLElement *ammoEl = saveEl->FirstChildElement("Ammo");
	//	if (ammoEl != nullptr) {
	//		//Ammo element exists
	//		std::cout << "Ammo: " << ammoEl->GetText() << std::endl;
	//	}
	//	//Get next element if available
	//	saveEl = saveEl->NextSiblingElement("Save");
	//}
	//return 0;
}

HighScoresGS::~HighScoresGS()
{
}

void HighScoresGS::Update(float delta)
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

void HighScoresGS::Draw(sf::RenderWindow & window)
{
	window.draw(mBgSprite);
	window.draw(mBackTxt);
	int place = 1;
	for (int i = 0; i < mHighScoresTxt.size(); i++) {
		window.draw(mHighScoresTxt[i]);
	}

}

void HighScoresGS::Init()
{
	//clear high score list to write updated
	mHighScoresTxt.clear();

	//create the temp here
	sf::Text tempTxt;

	//XML
	//XML tutorial
	using namespace tinyxml2;
	XMLDocument doc;
	int highScorePlace = 1;
	if (doc.LoadFile("GameData/casanova_game_data_edited.xml") != XML_SUCCESS) {
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

		//Process inner name element
		XMLElement *nameEl = highScoreEl->FirstChildElement("name");
		if (nameEl != nullptr) {
			//name element exists
			std::cout << "Name: " << nameEl->GetText() << std::endl;
		}
		XMLElement *scoreEl = highScoreEl->FirstChildElement("score");
		if (scoreEl != nullptr) {
			//score element exists
			std::cout << "Score: " << scoreEl->GetText() << std::endl;
		}
		tempTxt.setString(std::to_string(highScorePlace) + ". " + nameEl->GetText() + " - " + scoreEl->GetText());
		mHighScoresTxt.push_back(tempTxt);
		highScorePlace++;
		//Get next element if available
		highScoreEl = highScoreEl->NextSiblingElement("high_score");
	}

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}

	int scoreCharSize = 30;
	int hOffset = 13;
	int vOffset = 80;
	int rowDiv = GameStateManager::getInstance().WINDOW_HEIGHT / 9;
	int margin = GameStateManager::getInstance().WINDOW_WIDTH / 6 + hOffset;


	for (int i = 0; i < mHighScoresTxt.size(); i++) {
		mHighScoresTxt[i].setFont(*font);
		mHighScoresTxt[i].setCharacterSize(scoreCharSize);
		mHighScoresTxt[i].setFillColor(sf::Color::White);

		mHighScoresTxt[i].setStyle(sf::Text::Regular);
		mHighScoresTxt[i].setOrigin( mHighScoresTxt[i].getLocalBounds().width / 2, mHighScoresTxt[i].getLocalBounds().height);
		mHighScoresTxt[i].setPosition((float)margin, (float)(rowDiv * (i + 1)) + vOffset);
	}
}

void HighScoresGS::Deinit()
{
}

bool HighScoresGS::IsInit()
{
	return false;
}
