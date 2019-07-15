#pragma once
#include "GameState.h"

#include <SFML\Graphics.hpp>

class SplashGS :
	public AGameState
{
public:
	static SplashGS &getInstance() {
		static SplashGS instance;
		return instance;
	}
private:
	SplashGS();
	SplashGS(SplashGS const &);
	SplashGS &operator=(SplashGS const &);
	~SplashGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Sprite	mSplashSprite;
};

