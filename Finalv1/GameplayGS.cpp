#include "GameplayGS.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "AssetManager.h"
#include "PauseGS.h"
#include "GameOverGS.h"
#include "SettingsGS.h"
#include <iostream>
#include <string.h>

#include "tinyxml2.h"

//setup static const values
const sf::Vector2f GameplayGS::MS_HEARTPOS(760, 20);		// starting position of heart sprites
const sf::Vector2f GameplayGS::MS_SCOREPOS(730, 8);			// position of score label
const float GameplayGS::MS_HEARTSCALE = 0.07f;				// amount to scale heart texture
const float GameplayGS::MS_SPEED = 100.0f;					// standard starting ball x velocity
const float GameplayGS::MS_MAXSPEED = 200.0f;				// max x velocity
const float GameplayGS::MS_ACCELERATION = 600.0f;			// units/s/s
const int	GameplayGS::MS_BONUSINCREASE = 100;
const float GameplayGS::MS_SPAWNRATE = 3.0f;
const float GameplayGS::MS_PUSPAWNRATE = 15.0f;
const float GameplayGS::MS_EASYMODEDURATION = 10.0f;
const float GameplayGS::MS_HYSTERESIS = 0.2f;
const int	GameplayGS::MS_MINHEADHEIGHT = 240;

// ALISSA
const float	GameplayGS::MS_BGMOVESPEED = 30.0f;
const float GameplayGS::MS_BGSPAWNRATE = 33.0f;

//ported setup can go here in the constructor
GameplayGS::GameplayGS()
	: seed(time(NULL))
	, mSpawnTimer(3.0f)
	, mPUSpawnTimer(0.0f)
	, mEasyModeTimer(0.0f)
	, mSpawnInterval(MS_SPAWNRATE)
	, mGameTime(0.0f)
	, mLeftScore(0)
	, mScoreBonus(MS_BONUSINCREASE)
	, mLives(5)
	, mHearts(NULL)
	, mCharSelect(eCharSelect::CHAR_SELECT_ERR)
	, mEasyMode(false)
	, mIsNewHighScore(false)
	, mGameOver(false)
	, mPlayer(true)
	, mGutter(0, 0, GameStateManager::getInstance().WINDOW_WIDTH / 6, GameStateManager::getInstance().WINDOW_HEIGHT)
	, mEntities()
	, mBGSpawnTimer(0.0f)	//ALISSA
{
	srand((unsigned int)seed);

	sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/gameplay_bg.png");
	if (tex == nullptr) {
		//Error loading fonts.
		std::cout << "Error loading background texture" << std::endl;
		return;
	}

	//ALISSA
	mBackgroundSprites.push_back(sf::Sprite(*tex));
	mBackgroundSprites.push_back(sf::Sprite(*tex));
	mBackgroundSprites.back().setPosition(999.0f, 0.0f);

	// sound fx
	sf::SoundBuffer * kissBuffer = SoundManager::getInstance().getAsset("Assets/Sfx/sfx_kiss.wav");
	sf::SoundBuffer * greenPUBuffer = SoundManager::getInstance().getAsset("Assets/Sfx/sfx_healthPU.wav");
	sf::SoundBuffer * bluePUBuffer = SoundManager::getInstance().getAsset("Assets/Sfx/sfx_pointPU.wav");

	if (kissBuffer == nullptr || greenPUBuffer == nullptr || bluePUBuffer == nullptr) {
		//Error loading buffer
		std::cout << "Error loading audio data" << std::endl;
	}

	mKissSound.setBuffer(*kissBuffer);
	mGreenPUSound.setBuffer(*greenPUBuffer);
	mBluePUSound.setBuffer(*bluePUBuffer);

	mKissSound.setVolume(200);
	mGreenPUSound.setVolume(200);
	mBluePUSound.setVolume(200);

	/*mAllTxt.push_back(&mWinTxt);
	mAllTxt.push_back(&mLoseTxt);*/

	sf::Font * font = FontManager::getInstance().getAsset("Assets/Fonts/CurlzMT.ttf");
	if (font == nullptr) {
		//Error loading font.
		std::cout << "Error loading font" << std::endl;
		return;
	}

	int charSize = 40;
	int hOffset = 10;
	int vOffset = 5;
	int rowDiv = GameStateManager::getInstance().WINDOW_HEIGHT / 6;
	int colDiv = GameStateManager::getInstance().WINDOW_WIDTH / 4;

	mScoreTxt.setString(std::to_string(mLeftScore));
	mScoreTxt.setFont(*font);
	mScoreTxt.setCharacterSize(charSize);
	mScoreTxt.setFillColor(sf::Color::White);
	mScoreTxt.setOutlineColor(sf::Color::Black);
	mScoreTxt.setStyle(sf::Text::Regular);
	mScoreTxt.setOrigin(mScoreTxt.getLocalBounds().width, 0);
	mScoreTxt.setPosition(MS_SCOREPOS.x, MS_SCOREPOS.y);

	/*int charSize = 40;
	int hOffset = 10;
	int vOffset = 5;
	int rowDiv = GameStateManager::getInstance().WINDOW_HEIGHT / 6;
	int colDiv = GameStateManager::getInstance().WINDOW_WIDTH / 6;

	mWinTxt.setString("Win");
	mLoseTxt.setString("Lose");

	for (int i = 0; i < mAllTxt.size(); i++) {
		mAllTxt[i]->setFont(*font);
		mAllTxt[i]->setCharacterSize(charSize);
		mAllTxt[i]->setFillColor(sf::Color::White);
		mAllTxt[i]->setOutlineColor(sf::Color::Black);
		mAllTxt[i]->setStyle(sf::Text::Regular);
		mAllTxt[i]->setOrigin(mAllTxt[i]->getLocalBounds().width / 2, mAllTxt[i]->getLocalBounds().height / 2);
		mAllTxt[i]->setPosition(colDiv, (rowDiv * (i + 1)) + vOffset);
	}*/

	//ported setup goes here

	//Create heart sprites
	float heartX = MS_HEARTPOS.x;
	sf::Texture *heartTex = TextureManager::getInstance().getAsset("Assets/Sprites/pastel_heart.png");
	if (heartTex == nullptr) {
		//Error loading sprite.
		std::cout << "Error loading heart sprite" << std::endl;
		return;
	}
	for (int i = 0; i < mLives; ++i) {
		mHearts.push_back(sf::Sprite(*heartTex));
		mHearts[i].setPosition(heartX, MS_HEARTPOS.y);
		mHearts[i].setScale(MS_HEARTSCALE, MS_HEARTSCALE);
		heartX += 45;  // place more hearts to the right of the first
	}

	// initialize the player
	// TODO: use the dinoM (player) sprites if dinoM character selected
	sf::Texture * dinof = TextureManager::getInstance().getAsset("Assets/Sprites/dinof.png");
	sf::Texture * dinofw1 = TextureManager::getInstance().getAsset("Assets/Sprites/dinof_walk1.png");
	sf::Texture * dinofw2 = TextureManager::getInstance().getAsset("Assets/Sprites/dinof_walk2.png");
	if (dinof == nullptr &&
		dinofw1 == nullptr &&
		dinofw2 == nullptr)
	{
		//Error loading sprite.
		std::cout << "Error loading player dino sprites" << std::endl;
		return;
	}
	mPlayer.createDinoFSprites(dinof, dinofw1, dinofw2, dinof->getSize().x);
}


GameplayGS::~GameplayGS()
{
	//clean up here
	//other than the entities, everything should just go out of scope when the game state is cleaned up

	//player
	mPlayer.CleanUp();
	mPlayer = nullptr;
	//gutter
	mGutter.CleanUp();
	mGutter = nullptr;
	//mEntities
	
	for each (Entity ent in mEntities) {
		ent.CleanUp();
	}
}

void GameplayGS::setChar(eCharSelect selection)
{
	mCharSelect = selection;
}

void GameplayGS::Update(float delta)
{
	for (int i = 0; i < mBackgroundSprites.size(); i++) {
		sf::Vector2f prevPos = mBackgroundSprites[i].getPosition();
		mBackgroundSprites[i].setPosition((mBackgroundSprites[i].getPosition().x) + -MS_BGMOVESPEED * delta, mBackgroundSprites[i].getPosition().y);

		// ALISSA
		if (mBackgroundSprites[i].getPosition().x <= 0 && prevPos.x > 0) {
			//ALISSA
			sf::Texture * tex = TextureManager::getInstance().getAsset("Assets/Backgrounds/gameplay_bg.png");
			if (tex == nullptr) {
				//Error loading fonts.
				std::cout << "Error loading background texture" << std::endl;
				return;
			}
			//ALISSA
			mBackgroundSprites.push_back(sf::Sprite(*tex));
			mBackgroundSprites.back().setPosition(999.0f, 0.0f);

			//mBGSpawnTimer += delta;
		}
		if (prevPos.x < -1000) {
			mBackgroundSprites.erase(mBackgroundSprites.begin() + i);
		}
	}
	
	

	

	/*float highlightedThickness = 2.0f;
	for (int i = 0; i < mAllTxt.size(); i++) {
		mAllTxt[i]->setOutlineThickness(0.0f);
	}

	for (int i = 0; i < mAllTxt.size(); i++) {
		if (mAllTxt[i]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
			mAllTxt[i]->setOutlineThickness(highlightedThickness);
		}
	}*/

	// Press 'P' to pause
	if (InputManager::getInstance().wasKeyReleased(InputManager::GK_P)) {
		GameStateManager::getInstance().Push(PauseGS::getInstance());
	}

	//// go to GameOverGS and new high score 'true'
	//if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[0]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
	//	GameOverGS::getInstance().setNewHighScore(true);
	//	GameStateManager::getInstance().Push(GameOverGS::getInstance());
	//}

	//// go to GameOverGS no new high score
	//if (InputManager::getInstance().wasMouseLeftReleased() && mAllTxt[1]->getGlobalBounds().contains(InputManager::getInstance().getMousePos())) {
	//	GameStateManager::getInstance().Push(GameOverGS::getInstance());
	//}

	//ported update goes here
	//out of lives, trigger the GameOverGSf
	if (mLives <= 0) {
		GameOverGS::getInstance().setNewHighScore(mLeftScore > mMinHighScore ? true : false);

		GameStateManager::getInstance().Push(GameOverGS::getInstance());
		
	}

	//stretch or compress player dino's neck
	if (InputManager::getInstance().isKeyDown(InputManager::GK_SPACE)) {
		mPlayer.SetAcceleration(-(MS_ACCELERATION + 400));
	}
	else {
		mPlayer.SetAcceleration(MS_ACCELERATION);
	}

	mPlayer.Update(delta);

	int y;

	//spawn kissing targets
	//for every interval of time spawn exactly one new entity with a constant x velocity
	if (mSpawnTimer > mSpawnInterval) {
		y = rand() % 221 + 10;
		//spawn with constant speed <-- 200px/s leftward
		mEntities.push_back(Entity(GameStateManager::getInstance().WINDOW_WIDTH, y, -200.0f, 0.0f, true));
		
		//TODO: get different seet of sprites depending on the character selected
		sf::Texture * dinom = TextureManager::getInstance().getAsset("Assets/Sprites/dinom.png");
		sf::Texture * dinomw1 = TextureManager::getInstance().getAsset("Assets/Sprites/dinom_walk1.png");
		sf::Texture * dinomw2 = TextureManager::getInstance().getAsset("Assets/Sprites/dinom_walk2.png");
		if (dinom == nullptr &&
			dinomw1 == nullptr &&
			dinomw2 == nullptr)
		{
			//Error loading sprite.
			std::cout << "Error loading player dino sprites" << std::endl;
			return;
		}
		dinom->setSmooth(true);
		dinomw1->setSmooth(true);
		dinomw2->setSmooth(true);
		mEntities.back().createDinoMSprites(dinom, dinomw1, dinomw2, dinom->getSize().x);
		mEntities.back().setIsblue(false);
		if (mCharSelect == eCharSelect::PURPLE_DINO) {
			//setup player to be dinof
			sf::Texture * dinof = TextureManager::getInstance().getAsset("Assets/Sprites/dinof.png");
			sf::Texture * dinofw1 = TextureManager::getInstance().getAsset("Assets/Sprites/dinof_walk1.png");
			sf::Texture * dinofw2 = TextureManager::getInstance().getAsset("Assets/Sprites/dinof_walk2.png");
			if (dinof == nullptr &&
				dinofw1 == nullptr &&
				dinofw2 == nullptr)
			{
				//Error loading sprite.
				std::cout << "Error loading player dino sprites" << std::endl;
				return;
			}
			dinof->setSmooth(true);
			dinofw1->setSmooth(true);
			dinofw2->setSmooth(true);
			mEntities.back().setEnitityTex(dinof, dinofw1, dinofw2, true);
			mEntities.back().setIsblue(true);
		}

		if (mGameTime > 5.0f) {
			mSpawnInterval = MS_SPAWNRATE - 0.7f - ((rand() % 101) / 100.0f);
		}
		mSpawnTimer = 0;
	}
	else { // mSpawnTimer < 0
		mSpawnTimer += delta;
	}

	//spawn power ups
	if (mPUSpawnTimer > MS_PUSPAWNRATE) {
		POWERUP pu;
		y = rand() % 141 + 10;
		pu = (rand() % 2 == 0) ? BONUS_POINTS : EASY_MODE;
		sf::Texture* puTex = pu == BONUS_POINTS ? 
			TextureManager::getInstance().getAsset("Assets/Sprites/powerup_b.png") 
			: TextureManager::getInstance().getAsset("Assets/Sprites/powerup_g.png");
		//spawn with constant speed <-- 200px/s leftward 150px/s up/down
		mEntities.push_back(Entity(GameStateManager::getInstance().WINDOW_WIDTH, y, 15, 15, -200.0f, 100.0f, pu));
		mEntities.back().createPowerUpSprite(puTex);
		mPUSpawnTimer = 0;
	}
	else { // mPUSpawnTimer < 0
		mPUSpawnTimer += delta;
	}

	//easy mode timer
	if (mEasyMode) {
		mEasyModeTimer > MS_EASYMODEDURATION ? mEasyMode = false : mEasyModeTimer += delta;
	}

	//update all non-player entities
	for (std::vector<Entity>::iterator it = mEntities.begin(); it != mEntities.end();) {
		it->Update(delta);
		//move all non power-up entities to be at the same height as the player
		if (mEasyMode && it->GetPowerUp() == NONE) {
			//use hysteresis to making kissing targets follow more smoothly
			//rather than look like they teleport
			y = (int)(MS_HYSTERESIS * (mPlayer.Center().y - it->Center().y));
			it->SetCenter((int)it->Center().x, (int)it->Center().y + y);
		}
		if (it->Overlaps(mPlayer.Box()) && !it->isKissed()) {
			//player collides with something
			//update the kissing targets to make them kissed
			it->SetKissed();
			
			if (it->GetPowerUp() == NONE) {
				mLeftScore += mScoreBonus;
				mScoreBonus += MS_BONUSINCREASE;
				if (SettingsGS::getInstance().isSFXOn()) {
					mKissSound.play();
				}			
			}
			else if (it->GetPowerUp() > NONE) {
				if (it->GetPowerUp() == BONUS_POINTS) {
					//increase score multiplier
					for (int i = 0; i < 7; ++i) {
						mLeftScore += mScoreBonus;
						mScoreBonus += MS_BONUSINCREASE;
						if (SettingsGS::getInstance().isSFXOn()) {
							mBluePUSound.play();
						}
					}
				}
				else if (it->GetPowerUp() == EASY_MODE) {
					mEasyMode = true;
					mEasyModeTimer = 0.0f;
					if (SettingsGS::getInstance().isSFXOn()) {
						mGreenPUSound.play();
					}
				}
			}
		}
		if (it->Right() < -200 || (it->isKissed() && it->GetPowerUp() > NONE)) {
			//entity has gone off the left side of screen
			//remove it from the list
			it = mEntities.erase(it);
		}
		else {
			++it;
		}
	}
	
	//check for collisions
	sf::Vector2i center = mPlayer.Center();
	//reposition the player within the bounds of play area
	if (center.y < mPlayer.Height() / 2 + 15) { //top of screen
		center.y = mPlayer.Height() / 2 + 15;
	}
	else if (center.y > MS_MINHEADHEIGHT) {
		center.y = MS_MINHEADHEIGHT;
	}
	mPlayer.SetCenter((int)center.x, (int)center.y);

	//check if any of the kissing targets hit the gutter
	for (std::vector<Entity>::iterator it = mEntities.begin(); it != mEntities.end(); ++it) {
		if (it->GetPowerUp() == NONE) {
			if (it->Overlaps(mGutter.Box()) && !it->isMissed() && !it->isKissed()) {
				it->SetMissed();
				mScoreBonus = MS_BONUSINCREASE; // reset bonus value
				mLives -= 1;
			}
		}
	}
	//update score label
	mScoreTxt.setString(std::to_string(mLeftScore));
	//reposition to account for changing size of text
	mScoreTxt.setOrigin(mScoreTxt.getLocalBounds().width, 0);
	mScoreTxt.setPosition(MS_SCOREPOS.x, MS_SCOREPOS.y);

	mGameTime += delta;
}

void GameplayGS::Draw(sf::RenderWindow & window)
{
	//draw bg
	//window.draw(mGameplaySprite);
	//ALISSA
	for (int i = 0; i < mBackgroundSprites.size(); i++) {
		window.draw(mBackgroundSprites[i]);
	}

	//draw mEntities
	for (std::vector<Entity>::iterator it = mEntities.begin(); it != mEntities.end(); ++it) {
		it->Draw(window);
	}

	//draw player
	mPlayer.Draw(window);

	/*for (int i = 0; i < mAllTxt.size(); i++) {
		window.draw(*mAllTxt[i]);
	}*/

	//draw hearts
	for (int i = 0; i < mLives; ++i) {
		window.draw(mHearts[i]);
	}

	//draw score
	window.draw(mScoreTxt);
}

void GameplayGS::Init()
{
	std::cout << "Reinit GameplayGS" << std::endl;
	// Reset all the game state values that need to be reinitialized every time a new game is started
	GameOverGS::getInstance().setNewHighScore(false);

	//ported re-initialization goes here
	mLeftScore = 0;
	mLives = 5;
	mGameOver = false;
	mScoreBonus = MS_BONUSINCREASE;
	mSpawnTimer = 3.0f;
	mPUSpawnTimer = 0.0f;
	mEasyModeTimer = 0.0f;
	mGameTime = 0.0f;
	mEasyMode = false;
	mIsNewHighScore = false;

	//initialize the player
	mPlayer.SetCenter(GameStateManager::getInstance().WINDOW_WIDTH / 5 + 10, MS_MINHEADHEIGHT);
	if (mCharSelect != eCharSelect::CHAR_SELECT_ERR) {
		//character was selected properly
		if (mCharSelect == eCharSelect::BLUE_DINO) {
			//setup player to be dinof
			sf::Texture * dinof = TextureManager::getInstance().getAsset("Assets/Sprites/dinof.png");
			sf::Texture * dinofw1 = TextureManager::getInstance().getAsset("Assets/Sprites/dinof_walk1.png");
			sf::Texture * dinofw2 = TextureManager::getInstance().getAsset("Assets/Sprites/dinof_walk2.png");
			if (dinof == nullptr &&
				dinofw1 == nullptr &&
				dinofw2 == nullptr)
			{
				//Error loading sprite.
				std::cout << "Error loading player dino sprites" << std::endl;
				return;
			}
			dinof->setSmooth(true);
			dinofw1->setSmooth(true);
			dinofw2->setSmooth(true);
			mPlayer.setEnitityTex(dinof, dinofw1, dinofw2);
			mPlayer.setIsblue(true);
		}
		if (mCharSelect == eCharSelect::PURPLE_DINO) {
			//setup player to be dinom
			sf::Texture * dinom = TextureManager::getInstance().getAsset("Assets/Sprites/dinom.png");
			sf::Texture * dinomw1 = TextureManager::getInstance().getAsset("Assets/Sprites/dinom_walk1.png");
			sf::Texture * dinomw2 = TextureManager::getInstance().getAsset("Assets/Sprites/dinom_walk2.png");
			if (dinom == nullptr &&
				dinomw1 == nullptr &&
				dinomw2 == nullptr)
			{
				//Error loading sprite.
				std::cout << "Error loading player dino sprites" << std::endl;
				return;
			}
			dinom->setSmooth(true);
			dinomw1->setSmooth(true);
			dinomw2->setSmooth(true);
			mPlayer.setEnitityTex(dinom, dinomw1, dinomw2, true, true);
			mPlayer.setIsblue(false);
		}
	}

	//empty the entities collection
	if (!mEntities.empty()) {
		mEntities.clear();
	}

	// get the lowest high score from xml
	//XML
	//XML tutorial
	using namespace tinyxml2;
	XMLDocument doc;

	if (doc.LoadFile("GameData/casanova_game_data_edited.xml")) {
		//An error occurred
		std::cout << "Error loading XML file" << std::endl;
		//return 1;
	}
	XMLElement * gameDataEl = doc.FirstChildElement("game_data");
	if (gameDataEl == nullptr) {
		//An error occurred
		std::cout << "Error finding game_data element" << std::endl;
		//return 1;
	}
	XMLElement * highScoreEl = gameDataEl->FirstChildElement("high_score");
	while (highScoreEl != nullptr) {

		if (highScoreEl->NextSiblingElement("high_score") == nullptr) {
			// found the min high score
			XMLElement *scoreEl = highScoreEl->FirstChildElement("score");
			if (scoreEl != nullptr) {
				mMinHighScore = atoi(scoreEl->GetText());
			}
		}

		//Get next element if available
		highScoreEl = highScoreEl->NextSiblingElement("high_score");
	}
}

void GameplayGS::Deinit()
{
}

bool GameplayGS::IsInit()
{
	return false;
}
