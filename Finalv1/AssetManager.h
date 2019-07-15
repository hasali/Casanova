#pragma once

#include <string>
#include <map>

namespace sf {
	class Texture;
	class Font;
	class SoundBuffer;
}

template <typename T>
class AssetManager
{
public:
	static AssetManager &getInstance() {
		static AssetManager instance;
		return instance;
	}
private:
	AssetManager() { }
	AssetManager(AssetManager const &);
	AssetManager &operator=(AssetManager const &);

public:
	~AssetManager();
	void cleanUp();

	T *getAsset(std::string filename);
	bool loadAsset(std::string filename);

private:
	std::map<std::string, T *> mAssets;
};

typedef AssetManager<sf::Texture> TextureManager;
//typedef AssetManager<sf::Font> FontManager;
using FontManager = AssetManager<sf::Font>;
typedef AssetManager<sf::SoundBuffer> SoundManager;