

#include <WMPEngine/WMPEngine.h>
#include <WMPEngine/Errors.h>
#include <WMPEngine/ResourceManager.h>
#include "Engine.h"
#include <iostream>
#include <string>




Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::run()
{

}

void Engine::initSystems()
{

}

void Engine::initShader()
{
	colorShaderProgram.compileShaders("Shaders/colorShading.vert.txt", "Shaders/colorShading.frag.txt");
	colorShaderProgram.addAttribute("vertexPosition");
	colorShaderProgram.addAttribute("vertexColor");
	colorShaderProgram.addAttribute("vertexUV");
	colorShaderProgram.linkShaders();
}

void Engine::gameLoop()
{
	while (currentState != EngineState::EExit)
	{
		FPSlimiter.begin();

		processInput();
		time += 0.60f;

		camera.update();
		render();
	}
}

void Engine::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:				currentState = EngineState::EExit; break;
		case SDL_KEYDOWN:			inputManager.pressKey(event.key.keysym.sym); break;
		case SDL_KEYUP:				inputManager.releaseKey(event.key.keysym.sym); break;
		case SDL_MOUSEBUTTONDOWN:	inputManager.pressKey(event.button.button);	break;
		case SDL_MOUSEBUTTONUP:		inputManager.releaseKey(event.button.button); break;
		case SDL_MOUSEMOTION:		inputManager.setMouseCoords(event.motion.x, event.motion.y); break;
		}
	}
}

void Engine::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Drawing code here

	gameWindow.swapBuffer();
}