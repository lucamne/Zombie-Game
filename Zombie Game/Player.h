#pragma once

#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/ImageLoader.h>
#include <TRXEngine/GLTexture.h>

#include<glm/glm.hpp>

#include <string>

class Player
{
public:
	Player();
	Player(const std::string& path_to_texture, glm::vec2 init_posiiton, int width, int height);
	~Player();

	void draw(TRXEngine::SpriteBatch& sprite_batch);

	/// setters
	void setPosition(glm::vec2 position) { m_position = position; }
	/// getters
	glm::vec2 const getPosition() { return m_position; }

private:
	glm::vec2 m_position{};
	int m_width{};
	int m_height{};
	// holds texture information
	TRXEngine::GLTexture m_texture{};
};

