#pragma once
#include "GameState.h"

#include <vector>
#include <SFML\Graphics.hpp>

class SettingsGS :
	public AGameState
{
public:
	static SettingsGS &getInstance() {
		static SettingsGS instance;
		return instance;
	}

	bool isSFXOn() {
		return sfxOn;
	}
private:
	SettingsGS();
	SettingsGS(SettingsGS const &);
	SettingsGS &operator=(SettingsGS const &);
public:
	~SettingsGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	sf::Text mBackTxt;

	sf::Sprite	mBgSprite;

	sf::Texture* mOnActiveTex;
	sf::Texture* mOnInactiveTex;
	sf::Texture* mOffActiveTex;
	sf::Texture* mOffInactiveTex;

	sf::Sprite mMusicOptionOn;
	sf::Sprite mMusicOptionOff;
	sf::Sprite mSFXOptionOn;
	sf::Sprite mSFXOptionOff;

	bool sfxOn;
};