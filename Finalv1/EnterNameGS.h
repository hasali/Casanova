#pragma once
#include "GameState.h"

#include <vector>
#include <SFML\Graphics.hpp>

class EnterNameGS :
	public AGameState
{
public:
	static EnterNameGS &getInstance() {
		static EnterNameGS instance;
		return instance;
	}
private:
	EnterNameGS();
	EnterNameGS(EnterNameGS const &);
	EnterNameGS &operator=(EnterNameGS const &);
public:
	~EnterNameGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	int mCurrLetterVal;
	int offset;
	sf::Text mLetterTxt;

	sf::Text mFirstLetter;
	sf::Text mSecondLetter;
	sf::Text mThirdLetter;

	std::vector<sf::Text*> mInitialsTxt;

	sf::Text mContinueTxt;

	sf::Sprite	mBgSprite;
};