#include "Entity.h"

//default sizes for easy construction of player and kissing targets
const int Entity::msDefaultWidth = 10;
const int Entity::msDefaultHeight = 20;

//sprite placement values for female dino
const int Entity::msFHeadHeight = 120;
const int Entity::msFNeckHeight = 450 - msFHeadHeight;
const int Entity::msFBodyHeight = 963 - msFHeadHeight - msFNeckHeight;
const sf::Vector2f Entity::msFDinoPos( 20, 240 );

//sprite placement values for male dino
const int Entity::msMHeadHeight = 172;
const int Entity::msMNeckHeight = 501 - msMHeadHeight;
const int Entity::msMBodyHeight = 1012 - msMHeadHeight - msMNeckHeight;
const sf::Vector2f Entity::msMDinoPos( 700, 228 );

//power up sprite constants
const int Entity::msPowerUpSpriteW = 312;
const int Entity::msPowerUpSpriteH = 307;
const float Entity::msPowerUpSpriteScale = 0.06f;

//ensures a velocity must always be set to enable movement
const float Entity::msDefaultVelocityX = 0;
const float Entity::msDefaultVelocityY = 0;

//Acceleration
const float Entity::msDefaultAcceleration = 0.0f; 
//power up movement range
const float Entity::msPowerUpMoveRange = 100.0f;
//scale amount for the dino sprites
const float Entity::msDinoSpriteScale = 0.25f;
//length of time between walking sprite changes
const float Entity::msStrideLength = 0.5f;

const sf::Color	Entity::msDefaultColor = sf::Color(255, 255, 255, 255);		// white

Entity::Entity()
	: Entity(0, 0, msDefaultWidth, msDefaultHeight, msDefaultColor, msDefaultVelocityX, msDefaultVelocityY, POWERUP::NONE, false, false)
{
}

Entity::Entity(bool isPlayer)
	: Entity(0, 0, msDefaultWidth, msDefaultHeight, msDefaultColor, msDefaultVelocityX, msDefaultVelocityY, POWERUP::NONE, isPlayer, false)
{
}

Entity::Entity(int x, int y)
	: Entity(x, y, msDefaultWidth, msDefaultHeight, msDefaultColor, msDefaultVelocityX, msDefaultVelocityY, POWERUP::NONE, false, false)
{
}

Entity::Entity(int x, int y, int w, int h)
	: Entity(x, y, w, h, msDefaultColor, msDefaultVelocityX, msDefaultVelocityY, POWERUP::NONE, false, false)
{
}

Entity::Entity(int x, int y, float vx, float vy, bool isOther)
	: Entity(x, y, msDefaultWidth, msDefaultHeight, msDefaultColor, vx, vy, POWERUP::NONE, false, isOther)
{
}

Entity::Entity(int x, int y, int w, int h, sf::Color color)
	: Entity(x, y, w, h, color, msDefaultVelocityX, msDefaultVelocityY, POWERUP::NONE, false, false)
{
}

Entity::Entity(int x, int y, int w, int h, float vx, float vy, POWERUP type)
	: Entity(x, y, w, h, msDefaultColor, vx, vy, type, false, false)
{
}

Entity::Entity(int x, int y, int w, int h, float vx, float vy, bool isPlayer)
	: Entity(x, y, w, h, msDefaultColor, vx, vy, POWERUP::NONE, isPlayer, false)
{
}

Entity::Entity(int x, int y, int w, int h, sf::Color color, float vx, float vy, POWERUP type, bool isPlayer, bool isOther)
	: mRect()
	, mColor()
{
	mHead = nullptr;
	mNeck = nullptr;
	mWalk1 = nullptr;
	mWalk2 = nullptr;
	mBody = nullptr;
	mOrb = nullptr;
	mRect.left = x;
	mRect.top = y;
	mRect.width = w;
	mRect.height = h;
	mColor = color;
	mVelocityX = vx;
	mVelocityY = vy;
	mAcceleration = msDefaultAcceleration;
	mKissed = false;
	mMissed = false;
	mIsPlayer = isPlayer;
	mIsBlueDino = true;
	mIsOther = isOther;
	mType = type;
	mPowerUpMoveDistance = 0.0f;
	mWalkDuration = 0.0f;
}

sf::Vector2i Entity::Center() const
{
	//returns a point representing the center of the entity
	sf::Vector2i p;
	p.x = Left() + Width() / 2;
	p.y = Top() + Height() / 2;
	return p;
}

void Entity::SetCenter(int x, int y)
{
	SetLeft(x - Width() / 2);
	SetTop(y - Height() / 2);
}

bool Entity::Contains(int x, int y) const
{
	//return true if the point consisting of x and y coordinates
	//are inside the rect of this entity
	return mRect.contains(x, y);
}

bool Entity::Overlaps(sf::IntRect obstacle) const
{
	//returns true if this entity overlaps with another
	return mRect.intersects(obstacle);
}

void Entity::SetVelocity(float vx, float vy) {
	mVelocityX = vx;
	mVelocityY = vy;
}

void Entity::createDinoFSprites(sf::Texture* head, sf::Texture* walk1, sf::Texture* walk2, int w){
	//head
	mHead = createSprite(head, 0, 0, w, msFHeadHeight);
	mHead->setPosition(msFDinoPos.x, msFDinoPos.y);
	mHead->setScale(msDinoSpriteScale, msDinoSpriteScale);
	//neck
	mNeck = createSprite(head, 0, msFHeadHeight, w, msFNeckHeight);
	mNeck->setPosition(msFDinoPos.x, msFDinoPos.y + msFHeadHeight * msDinoSpriteScale);
	mNeck->setScale(msDinoSpriteScale, msDinoSpriteScale);
	//walk1
	mWalk1 = createSprite(walk1, 0, msFHeadHeight + msFNeckHeight, w, msFBodyHeight);
	mWalk1->setPosition(msFDinoPos.x, msFDinoPos.y + (msFHeadHeight + msFNeckHeight) * msDinoSpriteScale);
	mWalk1->setScale(msDinoSpriteScale, msDinoSpriteScale);
	//walk2
	mWalk2 = createSprite(walk2, 0, msFHeadHeight + msFNeckHeight, w, msFBodyHeight);
	mWalk2->setPosition(msFDinoPos.x, msFDinoPos.y + (msFHeadHeight + msFNeckHeight) * msDinoSpriteScale);
	mWalk2->setScale(msDinoSpriteScale, msDinoSpriteScale);

	mBody = mWalk1;
}

void Entity::createDinoMSprites(sf::Texture* head, sf::Texture* walk1, sf::Texture* walk2, int w){
	//head
	mHead = createSprite(head, 0, 0, w, msMHeadHeight);
	mHead->setPosition(msMDinoPos.x, msMDinoPos.y);
	mHead->setScale(msDinoSpriteScale, msDinoSpriteScale);
	//neck
	mNeck = createSprite(head, 0, msMHeadHeight, w, msMNeckHeight);
	mNeck->setPosition(msMDinoPos.x, msMDinoPos.y + msMHeadHeight * msDinoSpriteScale);
	mNeck->setScale(msDinoSpriteScale, msDinoSpriteScale);
	//walk1
	mWalk1 = createSprite(walk1, 0, msMHeadHeight + msMNeckHeight, w, msMBodyHeight);
	mWalk1->setPosition(msMDinoPos.x, msMDinoPos.y + (msMHeadHeight + msMNeckHeight) * msDinoSpriteScale);
	mWalk1->setScale(msDinoSpriteScale, msDinoSpriteScale);
	//walk2
	mWalk2 = createSprite(walk2, 0, msMHeadHeight + msMNeckHeight, w, msMBodyHeight);
	mWalk2->setPosition(msMDinoPos.x, msMDinoPos.y + (msMHeadHeight + msMNeckHeight) * msDinoSpriteScale);
	mWalk2->setScale(msDinoSpriteScale, msDinoSpriteScale);

	mBody = mWalk1;
}

void Entity::createPowerUpSprite(sf::Texture* orb){
	//power up
	mOrb = createSprite(orb, 0, 0, msPowerUpSpriteW, msPowerUpSpriteH);
	mOrb->setScale(msPowerUpSpriteScale, msPowerUpSpriteScale);
}

sf::Sprite * Entity::createSprite(sf::Texture * tex, int x, int y, int w, int h)
{
	sf::IntRect srcRect;

	srcRect.left = x;
	srcRect.top = y;
	srcRect.width = w;
	srcRect.height = h;

	sf::Sprite *s = new sf::Sprite(*tex, srcRect);
	return s;
}

void Entity::setEnitityTex(sf::Texture * head, sf::Texture * walk1, sf::Texture * walk2, bool flip, bool dinom)
{
	int w = (int)head->getSize().x;
	int x = 0;
	int width = w;
	mHead->setTexture(*head);
	mNeck->setTexture(*head);
	mWalk1->setTexture(*walk1);
	mWalk2->setTexture(*walk2);
	if (flip){
		x = width;
		width = -width;
	}
	if (!dinom) { //dinof
		mHead->setTextureRect(sf::IntRect(x, 0, width, msFHeadHeight));
		mNeck->setTextureRect(sf::IntRect(x, msFHeadHeight, width, msFNeckHeight));
		mWalk1->setTextureRect(sf::IntRect(x, msFNeckHeight + msFHeadHeight, width, msFBodyHeight));
		mWalk2->setTextureRect(sf::IntRect(x, msFNeckHeight + msFHeadHeight, width, msFBodyHeight));
	}
	else { //dinom
		mHead->setTextureRect(sf::IntRect(x, 0, width, msMHeadHeight));
		mNeck->setTextureRect(sf::IntRect(x, msMHeadHeight, width, msMNeckHeight));
		mWalk1->setTextureRect(sf::IntRect(x, msMNeckHeight + msMHeadHeight, width, msMBodyHeight));
		mWalk2->setTextureRect(sf::IntRect(x, msMNeckHeight + msMHeadHeight, width, msMBodyHeight));
	}
	mBody = mWalk1;
}

void Entity::Move(int dx, int dy)
{
	//move this entity dx units away from current x coordinate
	//and dy units away from current y coordinate
	mRect.left += dx;
	mRect.top += dy;
}

void Entity::Update(float delta)
{
    //
    // update position based on velocity
    //

	//get current velocity
	float cvx = mVelocityX;
	float cvy = mVelocityY;
	
	//adjust velocity for acceleration
	cvy += mAcceleration*delta;

	//cap velocity (falling speed at 150px/s) (rising speed at 200px/s)
	cvy = (cvy > 150.0f ? 150.0f : cvy);
	cvy = (cvy < -200.0f ? -200.0f : cvy);
	SetVelocity(cvx, cvy);
	
	//use delta to get displacement
	int dx = (int)(cvx*delta);
	int dy = (int)(cvy*delta);
	//get new position
	Move(dx, dy);

	//update the power up
	if (mType > POWERUP::NONE){
		mPowerUpMoveDistance += abs(dy);
		if (mPowerUpMoveDistance > msPowerUpMoveRange){
			mVelocityY = -mVelocityY;
			mPowerUpMoveDistance = 0.0f;
		}
		mOrb->setPosition((float)mRect.left, (float)mRect.top);
	}
	if (mType == POWERUP::NONE) {
		sf::FloatRect headRect = mHead->getGlobalBounds();
		sf::FloatRect neckRect = mNeck->getGlobalBounds();
		sf::FloatRect bodyRect = mBody->getGlobalBounds();
		//update head and neck sprites for player
		if (mIsPlayer) {
			int heightOffset = mRect.top - 10;
			int neckheight = msFNeckHeight;
			if (!mIsBlueDino) {
				heightOffset = mRect.top - 22;
				neckheight = msMNeckHeight;
			}
			mHead->setPosition((float)headRect.left, (float)heightOffset);
			mNeck->setPosition((float)mNeck->getPosition().x, (float)(heightOffset + headRect.height));
			float neckYScale = (bodyRect.top - (heightOffset + headRect.height)) / neckheight;
			mNeck->setScale(0.25, neckYScale);

			//body being shown to simulate walking

			mWalkDuration += delta;
			if (mWalkDuration > msStrideLength) {
				mBody = (mBody == mWalk1) ? mWalk2 : mWalk1;
				mWalkDuration = 0.0f;
			}
		}
		if (mIsOther) {
			int widthOffset = mRect.left - 2;
			int heightOffset = mRect.top - 10;
			int neckheight = msFNeckHeight;
			if (!mIsBlueDino) {
				heightOffset = mRect.top - 22;
				neckheight = msMNeckHeight;
			}
			//update head sprite
			mHead->setPosition((float)widthOffset, (float)heightOffset);
			//update neck sprite
			mNeck->setPosition((float)widthOffset, (float)(heightOffset + headRect.height));
			float neckYScale = (bodyRect.top - (heightOffset + headRect.height)) / neckheight;
			mNeck->setScale(mNeck->getScale().x, neckYScale);
			neckRect = mNeck->getGlobalBounds(); // get most recent
												 //update body sprite
			mBody->setPosition((float)widthOffset, (float)(heightOffset + headRect.height + neckRect.height));
			mWalk1->setPosition((float)widthOffset, (float)(heightOffset + headRect.height + neckRect.height));
			mWalk2->setPosition((float)widthOffset, (float)(heightOffset + headRect.height + neckRect.height));

			//body being shown to simulate walking

			mWalkDuration += delta;
			if (mWalkDuration > msStrideLength) {
				mBody = (mBody == mWalk1) ? mWalk2 : mWalk1;
				mWalkDuration = 0.0f;
			}
		}
	}
}

void Entity::Draw(sf::RenderWindow & window) const
{
	if (mIsPlayer || mIsOther){
		window.draw(*mHead);
		window.draw(*mNeck);
		window.draw(*mBody);
	}
	if (mType > NONE){
		window.draw(*mOrb);
	}
}

void Entity::CleanUp()
{
	if(mHead != nullptr)
	delete mHead;
	mHead = nullptr;
	if (mNeck != nullptr)
	delete mNeck;
	mNeck = nullptr;
	if (mWalk1 != nullptr)
	delete mWalk1;
	mWalk1 = nullptr;
	if (mWalk2 != nullptr)
	delete mWalk2;
	mWalk2 = nullptr;
	mBody = nullptr;
	if(mOrb != nullptr)
	delete mOrb;
	mOrb = nullptr;
}
