#include "GameStateManager.h"
#include "MainMenuGS.h"
#include "SplashGS.h"
#include "AssetManager.h"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

int main(int argc, char *argv[]) {
	
	GameStateManager::getInstance().Push(MainMenuGS::getInstance());
	GameStateManager::getInstance().Push(SplashGS::getInstance());
	return GameStateManager::getInstance().Play();

}