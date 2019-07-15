#include "SoundManager.h"
#include <SFML/Audio.hpp>


SoundManager::~SoundManager()
{
	cleanUp();
}
void SoundManager::cleanUp()
{
	for (auto it = mSounds.begin(); it == mSounds.end(); it++) {
		//delete i;
		//it = nullptr;
	}
	//mAssets.clear();
}