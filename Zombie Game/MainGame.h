#pragma once

#include "GameObjects.h"
#include "Textures.h"

#include <TRXEngine/Window.h>
#include <TRXEngine/GLSLProgram.h>
#include <TRXEngine/InputManager.h>
#include <TRXEngine/Camera2D.h>
#include <TRXEngine/SpriteBatch.h>
#include <TRXEngine/Timing.h>

enum class GAME_STATE
{
	PLAY,
	EXIT
};


class MainGame
{
public:
	MainGame();
	~MainGame();
	/// runs the game
	void run();

private:
	/// Initialize the core systsems
	void initSystems();

	/// Initializes the shaders
	void initShaders();

	/// Initialize assets like player, npc, and map
	void initAssets();

	/// Main game loop
	void gameLoop();

	/// Handles input processing
	void processInput();

	/// Renders the game
	void drawGame();

	/// cleanup functions
	void cleanup();
	
	/// Member variables
	int m_screen_width{};
	int m_screen_height{};
	float m_fps{};
	int m_player_speed{};

	GAME_STATE m_game_state{};
	GameObjects m_game_objects{};

	TRXEngine::Window m_window{};   
	TRXEngine::GLSLProgram m_texture_program{};   
	TRXEngine::InputManager m_input_manager{};  
	TRXEngine::Camera2D m_camera{};
	TRXEngine::SpriteBatch m_sprite_batch{};
	TRXEngine::FpsLimiter m_fps_limiter{};
};