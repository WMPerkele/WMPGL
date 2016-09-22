#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <WMPEngine/GLSLProgram.h>
#include <WMPEngine/GLTexture.h>
#include <WMPEngine/sprite.h>
#include <WMPEngine/Window.h>
#include <WMPEngine/Camera2D.h>
#include <WMPEngine/InputManager.h>
#include <WMPEngine/Timing.h>
#include <WMPEngine/SpriteBatch.h>
#include <vector>

enum class EngineState
{
	EPlaying,
	EExit
};

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	void initSystems();
	void initShader();
	void processInput();
	void gameLoop();
	void render();

	WMPEngine::Window gameWindow;
	EngineState currentState;
	int screenWidth;
	int screenHeight;

	WMPEngine::GLSLProgram colorShaderProgram;
	WMPEngine::InputManager inputManager;
	WMPEngine::FPSLimiter FPSlimiter;
	WMPEngine::Camera2D camera;
	WMPEngine::SpriteBatch spriteBatch;

	float maxFPS;
	float fps;
	float time;
};