#pragma once
#include "GameState.h"

#include <vector>
#include <SFML\Graphics.hpp>

class MainMenuGS :
	public AGameState
{
public:
	static MainMenuGS &getInstance() {
		static MainMenuGS instance;
		return instance;
	}
private:
	MainMenuGS();
	MainMenuGS(MainMenuGS const &);
	MainMenuGS &operator=(MainMenuGS const &);
public:
	~MainMenuGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Text mStartTxt;
	sf::Text mSettingsTxt;
	sf::Text mHelpTxt;
	sf::Text mHighScoresTxt;
	sf::Text mQuitTxt;
	std::vector<sf::Text*> mAllTxt;

	sf::Sprite	mBgSprite;
};

