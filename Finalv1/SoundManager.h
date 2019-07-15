#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
class SoundManager
{
public:

	static SoundManager &getInstance() 
	{
		static SoundManager instance;
		return instance;
	}

	~SoundManager();
private:
	SoundManager() {}
	SoundManager(SoundManager const &);
	SoundManager &operator=(SoundManager const &);

public:
	void cleanUp();
	void getSound(std::string filename);
	bool loadSound(std::string filename);

private:
	std::vector<std::string*> mSounds;
};

