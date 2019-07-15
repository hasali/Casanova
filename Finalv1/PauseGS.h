#pragma once
#include "GameState.h"

#include <SFML\Graphics.hpp>

class PauseGS :
	public AGameState
{
public:
	static PauseGS &getInstance() {
		static PauseGS instance;
		return instance;
	}
private:
	PauseGS();
	PauseGS(PauseGS const &);
	PauseGS &operator=(PauseGS const &);
	~PauseGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Sprite	mPauseSprite;
};

