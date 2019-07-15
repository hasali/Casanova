#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML\Graphics.hpp>

enum POWERUP
{
	NONE = -1,
	BONUS_POINTS,
	EASY_MODE,
	COUNT
};

class Entity
{
	sf::IntRect				mRect;
	sf::Color				mColor;
	sf::Sprite*				mHead;
	sf::Sprite*				mNeck;
	sf::Sprite*				mBody;
	sf::Sprite*				mWalk1;
	sf::Sprite*				mWalk2;
	sf::Sprite*				mOrb;
	float					mVelocityX;
	float					mVelocityY;
	float					mAcceleration;
	float					mPowerUpMoveDistance;
	float					mWalkDuration;
	bool					mKissed;
	bool					mMissed;
	bool					mIsPlayer;
	bool					mIsBlueDino;
	bool					mIsOther;
	POWERUP					mType;

public:
							Entity();
							Entity(bool isPlayer);
							Entity(int x, int y);
							Entity(int x, int y, int w, int h);
							Entity(int x, int y, float vx, float vy, bool isOther);
							Entity(int x, int y, int w, int h, sf::Color color);
							Entity(int x, int y, int w, int h, float vx, float vy, POWERUP type);
							Entity(int x, int y, int w, int h, float vx, float vy, bool isPlayer);
							Entity(int x, int y, int w, int h, sf::Color color, float vx, float vy, POWERUP type, bool isPlayer, bool isOther);

	int						Width() const		{ return mRect.width; }
	int						Height() const		{ return mRect.height; }

	int						Left() const		{ return mRect.left; }
	int						Top() const			{ return mRect.top; }
	int						Right() const		{ return mRect.left + mRect.width; }
	int						Bottom() const		{ return mRect.top + mRect.height; }

	sf::IntRect				Box() const			{ return mRect; }
	sf::Vector2i			Center() const;

	void					SetLeft(int x)		{ mRect.left = x; }
	void					SetRight(int x)		{ mRect.left = x - mRect.width; }
	void					SetTop(int y)		{ mRect.top = y; }
	void					SetBottom(int y)	{ mRect.top = y - mRect.top; }

	void					SetWidth(int w)		{ mRect.width = w; }
	void					SetHeight(int h)	{ mRect.height = h; }

	void					SetCenter(int x, int y);

	bool					Contains(int x, int y) const;
	bool					Overlaps(sf::IntRect obstacle) const;
	bool					isKissed() const	{ return mKissed; }
	bool					isMissed() const	{ return mMissed; }
	POWERUP					GetPowerUp() const	{ return mType; }

	void					Move(int dx, int dy);
	float					GetVelocityX() const				{ return mVelocityX; }
	float					GetVelocityY() const				{ return mVelocityY; }
	float					GetAcceleration() const				{ return mAcceleration; }
	void					SetVelocity(float vx, float vy);
	void					createDinoFSprites(sf::Texture* head, sf::Texture* walk1, sf::Texture* walk2, int w);
	void					createDinoMSprites(sf::Texture* head, sf::Texture* walk1, sf::Texture* walk2, int w);
	void					createPowerUpSprite(sf::Texture* orb);
	sf::Sprite *			createSprite(sf::Texture * tex, int x, int y, int w, int h);
	void					setEnitityTex(sf::Texture* head, sf::Texture* walk1, sf::Texture* walk2, bool flip = false, bool dinom = false);
	void					setIsblue(bool isBlue)				{ mIsBlueDino = isBlue; }
	void					SetAcceleration(float accel)		{ mAcceleration = accel; }
	void					SetKissed()							{ mKissed = true; }
	void					SetMissed()							{ mMissed = true; }

	void					SetColor(sf::Color color)						{ mColor = color; }
	void					SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)	{ mColor.r = r; mColor.g = g; mColor.b = b; mColor.a = a; }

	void					Update(float delta);
	void					Draw(sf::RenderWindow & window) const;
	void					CleanUp();

private:
	static const int			msDefaultWidth;
	static const int			msDefaultHeight;
	static const float			msDefaultVelocityX;
	static const float			msDefaultVelocityY;
	static const float			msDefaultAcceleration;
	static const float			msPowerUpMoveRange;

	static const int			msFHeadHeight;
	static const int			msFNeckHeight;
	static const int			msFBodyHeight;
	static const sf::Vector2f	msFDinoPos;

	static const int			msMHeadHeight;
	static const int			msMNeckHeight;
	static const int			msMBodyHeight;
	static const sf::Vector2f	msMDinoPos;

	static const int			msPowerUpSpriteW;
	static const int			msPowerUpSpriteH;
	static const float			msPowerUpSpriteScale;

	static const float			msDinoSpriteScale;
	static const float			msStrideLength;

	static const sf::Color		msDefaultColor;
};

#endif
