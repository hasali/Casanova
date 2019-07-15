#pragma once
#include "GameState.h"

#include <vector>
#include <SFML\Graphics.hpp>

// CURRENTLY THE SAME CODE AS HELPGS.H B/C NO XML IMPLEMENTATION YET
class HighScoresGS :
	public AGameState
{
public:
	static HighScoresGS &getInstance() {
		static HighScoresGS instance;
		return instance;
	}
private:
	HighScoresGS();
	HighScoresGS(HighScoresGS const &);
	HighScoresGS &operator=(HighScoresGS const &);
public:
	~HighScoresGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Text mBackTxt;

	//sf::Text tempTxt; //no business being here if its just a temp

	std::vector<sf::Text> mHighScoresTxt;

	sf::Sprite	mBgSprite;
};