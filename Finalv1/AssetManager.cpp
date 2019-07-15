#include "AssetManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
template <typename T>
AssetManager<T>::~AssetManager()
{
	cleanUp();
}

template <typename T>
void AssetManager<T>::cleanUp()
{
	for (auto it = mAssets.begin(); it == mAssets.end(); it++) {
		delete it->second;
		it->second = nullptr;
	}
	mAssets.clear();
}

template <typename T>
T * AssetManager<T>::getAsset(std::string filename)
{
	//Checks if the texture is loaded and creates the sprite
	if (loadAsset(filename)) {
		return mAssets[filename];
	}
	return nullptr;
}

template <typename T>
bool AssetManager<T>::loadAsset(std::string filename)
{
	//First check if the texture is already loaded.
	auto it = mAssets.find(filename);
	if (it != mAssets.end()) {
		//File has already been loaded
		return true;
	}
	//File has not been loaded, attempt to load.
	T *asset = new T;
	if (asset->loadFromFile(filename)) {
		//File loaded successfully.
		mAssets[filename] = asset;
		return true;
	}
	//File did not load successfully.
	// Maybe an error message?
	delete asset;
	return false;
}

template class AssetManager<sf::Font>;
template class AssetManager<sf::Texture>;
template class AssetManager<sf::SoundBuffer>;