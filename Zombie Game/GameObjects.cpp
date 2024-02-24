#include "GameObjects.h"
#include "Textures.h"

GameObjects::GameObjects()
{
}

GameObjects::~GameObjects()
{
}

void GameObjects::init()
{
	m_player1 = Player(TEXTURES::PLAYER, glm::vec2{ 0 }, 50, 50);
	m_enemies.push_back(new Enemy(TEXTURES::ENEMY, glm::vec2(0, 250), 50, 50));
}

void GameObjects::update()
{
	m_player1.update();

	checkEnemyCollisionsWithProjectiles();

	for (int i{ 0 }; i < m_enemies.size();)
	{
		if (m_enemies[i]->getState() == ENEMY_STATE::DEAD)
		{
			m_enemies[i] = m_enemies.back();
			m_enemies.pop_back();
		}
		else 
		{ i++; }
	}
}

void GameObjects::draw(TRXEngine::SpriteBatch& sprite_batch)
{
	// draw player
	m_player1.draw(sprite_batch);
	for (Enemy* enemy : m_enemies)
	{
		enemy->draw(sprite_batch);
	}
}

void GameObjects::cleanup()
{
	m_player1.cleanup();
	for (Enemy* enemy : m_enemies)
	{
		delete enemy;
	}
}

void GameObjects::checkEnemyCollisionsWithProjectiles()
{
	// loop through all enemies and then all projectiles to check for collisions
	const std::vector<Projectile*>& projectiles{ m_player1.getProjectiles() };
	for (Enemy* enemy : m_enemies)
	{
		// get information on enemy position and hitbox
		glm::vec2 enemy_position{ enemy->getPosition()};
		int enemy_width{ enemy->getWidth() };
		int enemy_height{ enemy->getHeight() };
		for (Projectile* projectile : projectiles)
		{
			// only check the center point of projectile
			glm::vec2 projectile_center{ projectile->getCenterPosition() };

			if (projectile_center.x >= enemy_position.x && projectile_center.x <= enemy_position.x + enemy_width && projectile_center.y >= enemy_position.y && projectile_center.y <= enemy_position.y + enemy_height)
			{
				enemy->kill();
			}

		}
	}
}
