#pragma once

#include <TRXEngine/SpriteBatch.h>

#include "Player.h"
#include "Enemy.h"

#include "Vector"

class GameObjects
{
public:
	GameObjects();
	~GameObjects();

	void init();
	void update();
	void draw(TRXEngine::SpriteBatch& sprite_batch);
	void cleanup();

	/// Player functions
	void fireProjectile(glm::vec2 target, float speed) { m_player1.fireProjectile(target, speed); }
	/// setters
	void setPlayerPosition(glm::vec2 position) { m_player1.setPosition(position); }
	/// getters
	glm::vec2 const getPlayerPosition() { return m_player1.getPosition(); }

private:
	Player m_player1{};
	std::vector<Enemy*> m_enemies{};

	void checkEnemyCollisionsWithProjectiles();
};

