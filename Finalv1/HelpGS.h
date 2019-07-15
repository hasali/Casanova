#pragma once
#include "GameState.h"

#include <vector>
#include <SFML\Graphics.hpp>

class HelpGS :
	public AGameState
{
public:
	static HelpGS &getInstance() {
		static HelpGS instance;
		return instance;
	}
private:
	HelpGS();
	HelpGS(HelpGS const &);
	HelpGS &operator=(HelpGS const &);
public:
	~HelpGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Text mBackTxt;

	sf::Sprite	mBgSprite;
};