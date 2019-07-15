#pragma once
namespace sf {
	class RenderWindow;
}

class AGameState {

private:
	bool mOpaque;
	bool mPaused;
public:
	AGameState(bool opaque = true) : mOpaque(opaque), mPaused(false) {
	}

	bool isOpaque() {
		return mOpaque;
	}

	virtual void Update(float delta) = 0;
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void Init() = 0;
	virtual void Deinit() = 0;
	virtual bool IsInit() = 0;
	virtual void Pause() {
		mPaused = true;
	}
	virtual void Resume() {
		mPaused = false;
	}
	virtual bool isPaused() {
		return mPaused;
	}

};