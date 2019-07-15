#pragma once
#include "GameState.h"

#include <vector>
#include <string.h>
#include <SFML\Graphics.hpp>

class CharacterSelectGS :
	public AGameState
{
public:
	static CharacterSelectGS &getInstance() {
		static CharacterSelectGS instance;
		return instance;
	}
private:
	CharacterSelectGS();
	CharacterSelectGS(CharacterSelectGS const &);
	CharacterSelectGS &operator=(CharacterSelectGS const &);
public:
	~CharacterSelectGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Text mBackTxt;

	sf::Text mPlayerDinoNameTxt;

	std::string mFDinoName;
	std::string mMDinoName;

	sf::Sprite	mBgSprite;

	sf::Sprite	mFDinoSprite;

	sf::Sprite	mMDinoSprite;
};

