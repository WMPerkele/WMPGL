#pragma once

#include <WMPEngine/Window.h>
#include <WMPEngine/GLSLProgram.h>
#include <WMPEngine/Camera2D.h>
#include <WMPEngine/InputManager.h>
#include <WMPEngine\SpriteBatch.h>
#include "Board.h"
#include "SQLWriter.h"

enum class GameState
{
	EPlay,
	EExit
};
enum class CheckerState
{
	PickingMan,
	PickingTile,
	None
};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();

    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

    /// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

    /// Member Variables
    WMPEngine::Window window; ///< The game window
    
    WMPEngine::GLSLProgram textureProgram; ///< The shader program

    WMPEngine::InputManager inputManager; ///< Handles input

    WMPEngine::Camera2D camera; ///< Main Camera

	WMPEngine::SpriteBatch spriteBatch;

	const int SCREEN_WIDTH =  1024;
	const int SCREEN_HEIGHT = 768;
	GameState state = GameState::EPlay;
	CheckerState playState = CheckerState::PickingMan;
	int playerTurn;
	Men* chosenMan;
	Board gameBoard;
	SQLWriter* writer;
	int turnCount;
};

