#pragma once

#include <WMPEngine/Window.h>
#include <WMPEngine/GLSLProgram.h>
#include <WMPEngine/Camera2D.h>
#include <WMPEngine/InputManager.h>
#include <WMPEngine/SpriteBatch.h>

#include "Player.h"
#include "Level.h"
#include "Bullet.h"

class Zombie;

enum class GameState {
    PLAY,
    EXIT
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

    /// Initializes the level and sets up everything
    void initLevel();

    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

    /// Updates all agents
    void updateAgents();

    /// Updates all bullets
    void updateBullets();

    /// Checks the victory condition
    void checkVictory();

    /// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

    /// Member Variables
    WMPEngine::Window _window; ///< The game window
    
    WMPEngine::GLSLProgram _textureProgram; ///< The shader program

    WMPEngine::InputManager _inputManager; ///< Handles input

    WMPEngine::Camera2D _camera; ///< Main Camera

    WMPEngine::SpriteBatch _agentSpriteBatch; ///< Draws all agents

    std::vector<Level*> _levels; ///< vector of all levels

    int _screenWidth, _screenHeight;

    float _fps;

    int _currentLevel;

    Player* _player;
    std::vector<Human*> _humans; ///< Vector of all humans
    std::vector<Zombie*> _zombies; ///< Vector of all zombies
    std::vector<Bullet> _bullets;

    int _numHumansKilled; ///< Humans killed by player
    int _numZombiesKilled; ///< Zombies killed by player

    GameState _gameState;
};

