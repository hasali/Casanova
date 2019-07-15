#pragma once
#include "GameState.h"

#include <SFML\Graphics.hpp>

class GameOverGS :
	public AGameState
{
public:
	static GameOverGS &getInstance() {
		static GameOverGS instance;
		return instance;
	}
	void setNewHighScore(bool isHighScore) { mNewHighScore = isHighScore; };

private:
	GameOverGS();
	GameOverGS(GameOverGS const &);
	GameOverGS &operator=(GameOverGS const &);
	~GameOverGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	bool mNewHighScore;
	sf::Text mContinueTxt;

	sf::Sprite	mGameOverSprite;
};

