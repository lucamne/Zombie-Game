#include "Level.h"

Level::Level()
	:PLAYER1_TEXTURE_PATH{ "Textures/jimmy_jump/PNG/CharacterLeft_Standing.png" }
{
}
Level::~Level()
{
}

void Level::init()
{
	m_player1.init(PLAYER1_TEXTURE_PATH,glm::vec2(0,0),50,50);
}

void Level::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	m_player1.draw(sprite_batch);
}
