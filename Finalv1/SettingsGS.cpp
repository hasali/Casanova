#include "SettingsGS.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "AssetManager.h"
#include <iostream>

SettingsGS::SettingsGS()
{
	sf::Texture * bgTex = TextureManager::getInstance().getAsset("Assets/Backgrounds/settings_bg.png");
	if (bgTex == nullptr) {
		//Error loading background.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	mOnActiveTex = TextureManager::getInstance().getAsset("Assets/Sprites/on_active.png");
	mOnInactiveTex = TextureManager::getInstance().getAsset("Assets/Sprites/on_inactive.png");
	mOffActiveTex = TextureManager::getInstance().getAsset("Assets/Sprites/off_active.png");
	mOffInactiveTex = TextureManager::getInstance().getAsset("Assets/Sprites/off_inactive.png");

	if (mOnActiveTex == nullptr ||
		mOnInactiveTex == nullptr ||
		mOffActiveTex == nullptr ||
		mOffInactiveTex == nullptr) {
		//Error loading sprites.
		std::cout << "Error loading sprite textures" << std::endl;
		return;
	}

	mBgSprite.setTexture(*bgTex);

	mMusicOptionOn.setTexture(*mOnActiveTex);
	mMusicOptionOff.setTexture(*mOffInactiveTex);

	mSFXOptionOn.setTexture(*mOnActiveTex);
	mSFXOptionOff.setTexture(*mOffInactiveTex);

	// hardcoded
	mMusicOptionOn.setPosition(130, 182);
	mMusicOptionOff.setPosition(190, 182);

	// hardcoded
	mSFXOptionOn.setPosition(130, 258);
	mSFXOptionOff.setPosition(190, 258);

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

	sfxOn = true;
}

SettingsGS::~SettingsGS()
{
}

void SettingsGS::Update(float delta)
{
	float highlightedThickness = 2.0f;

	mBackTxt.setOutlineThickness(0.0f);

	if (mBackTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		mBackTxt.setOutlineThickness(highlightedThickness);
	}

	// set music on to active and music off to inactive
	if (InputManager::getInstance().wasMouseLeftReleased() && mMusicOptionOn.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {

		mMusicOptionOn.setTexture(*mOnActiveTex);
		mMusicOptionOff.setTexture(*mOffInactiveTex);

		// play bg music here?
		GameStateManager::getInstance().playBGMusic();
	}

	// set music off to active and music on to inactive
	if (InputManager::getInstance().wasMouseLeftReleased() && mMusicOptionOff.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		
		mMusicOptionOn.setTexture(*mOnInactiveTex);
		mMusicOptionOff.setTexture(*mOffActiveTex);

		// stop bg music here?
		GameStateManager::getInstance().stopBGMusic();
	}

	// set sfx on to active and sfx off to inactive
	if (InputManager::getInstance().wasMouseLeftReleased() && mSFXOptionOn.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {

		mSFXOptionOn.setTexture(*mOnActiveTex);
		mSFXOptionOff.setTexture(*mOffInactiveTex);

		// turn on sfx here?
		sfxOn = true;
	}

	// set sfx off to active and sfx on to inactive
	if (InputManager::getInstance().wasMouseLeftReleased() && mSFXOptionOff.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {

		mSFXOptionOn.setTexture(*mOnInactiveTex);
		mSFXOptionOff.setTexture(*mOffActiveTex);

		// turn off sfx here?
		sfxOn = false;
	}

	// go back to main menu GS if player clicks Back
	if (InputManager::getInstance().wasMouseLeftReleased() && mBackTxt.getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
		GameStateManager::getInstance().Pop();
	}
}

void SettingsGS::Draw(sf::RenderWindow & window)
{
	window.draw(mBgSprite);
	window.draw(mBackTxt);

	window.draw(mMusicOptionOn);
	window.draw(mMusicOptionOff);

	window.draw(mSFXOptionOn);
	window.draw(mSFXOptionOff);
}

void SettingsGS::Init()
{
}

void SettingsGS::Deinit()
{
}

bool SettingsGS::IsInit()
{
	return false;
}