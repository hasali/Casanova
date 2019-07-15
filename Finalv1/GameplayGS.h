#pragma once
#include "GameState.h"
#include "Entity.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class GameplayGS :
	public AGameState
{
public:
	
	static GameplayGS &getInstance() {
		static GameplayGS instance;
		return instance;
	}
	enum eCharSelect {
		CHAR_SELECT_ERR = -1,
		BLUE_DINO,
		PURPLE_DINO,
		COUNT
	};

	int getScore() { return mLeftScore; };
	void setChar(eCharSelect selection);

private:
	GameplayGS();
	GameplayGS(GameplayGS const &);
	GameplayGS &operator=(GameplayGS const &);
	~GameplayGS();

	// Inherited via AGameState
	virtual void Update(float delta) override;
	virtual void Draw(sf::RenderWindow & window) override;
	virtual void Init() override;
	virtual void Deinit() override;
	virtual bool IsInit() override;

private:
	//used for testing
	/*sf::Text mWinTxt;
	sf::Text mLoseTxt;
	std::vector<sf::Text*> mAllTxt;*/

	sf::Text mScoreTxt;
	sf::Sprite mGameplaySprite; //BG

	//Ported stuff goes here
	time_t				seed;
	int					mLeftScore;
	int					mScoreBonus;
	int					mLives;
	float				mSpawnTimer;
	float				mPUSpawnTimer;
	float				mEasyModeTimer;
	float				mSpawnInterval;
	float				mGameTime;

	//ALISSA
	float mBGSpawnTimer;
	int mMinHighScore; 
	sf::Sound mKissSound;
	sf::Sound mGreenPUSound;
	sf::Sound mBluePUSound;


	/*SDL_Window*			mWindow;
	const Uint8*		mKeys;
	SDL_Renderer*		mRenderer;
	SDL_Texture*		mBmpFontTex;*/
	//sf::Sprite*		mBackgroundSprite;
	//std::vector<SDL_Texture*>mTextures;
	//std::vector<int>	mTextureWidths;
	std::vector<sf::Sprite>mHearts;

	eCharSelect			mCharSelect;
	bool				mEasyMode;
	bool				mIsNewHighScore;
	bool				mGameOver;
	//bool				mShouldQuit;

	// ALISSA
	std::vector<sf::Sprite> mBackgroundSprites;

	Entity				mPlayer;
	Entity				mGutter;
	std::vector<Entity> mEntities;


	static const sf::Vector2f	MS_HEARTPOS;
	static const sf::Vector2f	MS_SCOREPOS;
	static const float			MS_HEARTSCALE;
	static const float			MS_SPEED;
	static const float			MS_MAXSPEED;
	static const float			MS_ACCELERATION;
	static const float			MS_SPAWNRATE;
	static const float			MS_PUSPAWNRATE;
	static const int			MS_BONUSINCREASE;
	static const float			MS_EASYMODEDURATION;
	static const float			MS_HYSTERESIS;
	static const int			MS_MINHEADHEIGHT;

	// ALISSA
	static const float MS_BGMOVESPEED;
	static const float MS_BGSPAWNRATE;
};

