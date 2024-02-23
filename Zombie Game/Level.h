#pragma once


#include "Player.h"

#include <TRXEngine/SpriteBatch.h>

#include <string>

class Level
{
public:
	Level();
	~Level();

	void init();

	void draw(TRXEngine::SpriteBatch& sprite_batch);
	
	/// setters


private:
	// holds path to texture used for main player
	std::string PLAYER1_TEXTURE_PATH{};
	// main playable character
	Player m_player1{};
};