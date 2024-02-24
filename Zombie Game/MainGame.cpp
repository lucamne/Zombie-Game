/// Zombie Game!!

#include <TRXEngine/TRXEngine.h>
#include <TRXEngine/ResourceManager.h>

#include "MainGame.h"

MainGame::MainGame()
	:m_screen_width{700},
	m_screen_height{700},
	m_fps{ 0 },
	m_player_speed{5},
	m_game_state {GAME_STATE::PLAY}
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::initSystems()
{
	// initialize SDL
	TRXEngine::init();
	// init window
	m_window.create("Zombie Game", m_screen_width, m_screen_width, 0);

	m_camera.init(m_screen_width, m_screen_height);

	m_sprite_batch.init();

	m_fps_limiter.init(60.0f);

	initShaders();

	initAssets();
}

void MainGame::initShaders()
{
	m_texture_program.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_texture_program.addAtrribute("vertexPosition");
	m_texture_program.addAtrribute("vertexColor");
	m_texture_program.addAtrribute("vertexUV");
	m_texture_program.linkShaders();
}

void MainGame::initAssets()
{
}

void MainGame::gameLoop()
{
	while (m_game_state == GAME_STATE::PLAY)
	{
		m_fps_limiter.begin();

		processInput();
		// if player moves camera must move as well
		m_camera.update();


		drawGame();

		m_fps = m_fps_limiter.end();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt{};
	// Continously looped through events until there are no more events to process
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_game_state = GAME_STATE::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_input_manager.setMouseCoords(static_cast<float>(evnt.motion.x), static_cast<float>(evnt.motion.y));
			break;
		case SDL_KEYDOWN:
			m_input_manager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_input_manager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_input_manager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_input_manager.releaseKey(evnt.button.button);
			break;
		}
	}

	// if keys w, a, s, d are pressed, move character up, left, down, right respectively
	if (m_input_manager.isKeyPressed(SDLK_w))
	{
	}
	if (m_input_manager.isKeyPressed(SDLK_a))
	{
	}
	if (m_input_manager.isKeyPressed(SDLK_s))
	{
	}
	if (m_input_manager.isKeyPressed(SDLK_d))
	{
	}
	// if mouse button is pressed shoot projectiles at direction of mouse
	if (m_input_manager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		// convert relative screen coordinates to world coordinates
		glm::vec2 mouse_coords{ m_input_manager.getMouseCoords() };
		mouse_coords = m_camera.convertScreenToWorld(mouse_coords);

	}
}

void MainGame::drawGame()
{
	// set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// tell graphics card we are using this texture program
	m_texture_program.use();
	// multiple textures can be loaded so need to set active texture bank
	glActiveTexture(GL_TEXTURE0);
	// get location of uniform playerTexture variable in shader
	GLint texture_location = m_texture_program.getUniformLocation("playerTexture");
	// link texture location to texture bank 0
	glUniform1i(texture_location, 0);

	/// update camera matrix uniform variable
	GLint camera_matrix_location = m_texture_program.getUniformLocation("P");
	glm::mat4 camera_matrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(camera_matrix_location, 1, GL_FALSE, &(camera_matrix[0][0]));

	// sprite batch is cleared and can now be drawed to
	m_sprite_batch.begin();
	// end sorts sprite batch by texture for efficient rendering
	m_sprite_batch.end();
	// redner sprite batch
	m_sprite_batch.renderBatch();

	m_texture_program.unuse();
	// swap buffer and draw everything to the screen
	m_window.swapBuffer();
}

void MainGame::cleanup()
{
}
