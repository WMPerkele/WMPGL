#include "MainGame.h"

#include <WMPEngine/WMPEngine.h>
#include <WMPEngine\Timing.h>

#include <SDL/SDL.h>
#include <iostream>

MainGame::MainGame() 
{
	state = GameState::EPlay;
	playerTurn = 1;
	turnCount = 1;
}

MainGame::~MainGame() 
{
    // IMPLEMENT THIS!
}

void MainGame::run()
{
	initSystems();

	gameLoop();
}

void MainGame::initSystems() 
{
	WMPEngine::init();

	window.create("SQLCheckers", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	initShaders();

	camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	glm::vec2 temp = camera.getPosition();
	temp.x += 64 * 4;
	temp.y += 64 * 4;
	camera.setPosition(temp);

	gameBoard.init();
	
	spriteBatch.init();

	writer = new SQLWriter();
	writer->init();
	writer->AddPlayer("Player1");
	writer->AddPlayer("Player2");
	writer->AddGame(1, 2);
	writer->AddTurn(0, playerTurn);
}

void MainGame::initShaders() 
{
    // Compile our color shader
    textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    textureProgram.addAttribute("vertexPosition");
    textureProgram.addAttribute("vertexColor");
    textureProgram.addAttribute("vertexUV");
    textureProgram.linkShaders();
}

void MainGame::gameLoop() 
{
	//sets up the limit for fps
	WMPEngine::FPSLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);
	while (state != GameState::EExit)
	{
		fpsLimiter.begin();

		inputManager.update();

		processInput();
		
		camera.update();

		switch (playState)
		{
		case CheckerState::PickingMan:
			Men* man;
			man = gameBoard.hoveredMan(camera.convertScreenToWorld(inputManager.getMouseCoords()));
			if (man != nullptr && inputManager.isKeyPressed(SDL_BUTTON_LEFT) && man->GetOwner() == playerTurn)
			{
				chosenMan = man;
				playState = CheckerState::PickingTile;
				std::cout << "man picked" << std::endl;
			}
			man = nullptr;
			break;
		case CheckerState::PickingTile:
			BoardTile* tile;
			tile = gameBoard.hoveredTile(camera.convertScreenToWorld(inputManager.getMouseCoords()));
			if (tile != nullptr && inputManager.isKeyPressed(SDL_BUTTON_LEFT))
			{
				if (gameBoard.MoveIsLegal(chosenMan, tile))
				{
					std::cout << "Move is legal" << std::endl;
					BoardTile* movedTile;
					movedTile = gameBoard.MovePiece(chosenMan, tile->GETX(), tile->GETY());
					if (movedTile)
					{
						std::cout << "Piece moved" << std::endl;
						writer->AddMove(movedTile->GETX(), movedTile->GETY(), turnCount++, chosenMan->GetID());
						if (playerTurn == 1)
							playerTurn = 2;
						else if (playerTurn == 2)
							playerTurn = 1;


						writer->AddTurn(0, playerTurn);
						playState = CheckerState::PickingMan;
					}
				}
			}
			if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
			{
				chosenMan = nullptr;
				playState = CheckerState::PickingMan;
			}
			break;
		case CheckerState::None:
			break;
		}


		//Implement all the game updates here
		drawGame();

		fpsLimiter.end();

	}
}

void MainGame::processInput() 
{
    SDL_Event evnt;
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) 
	{
        switch (evnt.type) 
		{
            case SDL_QUIT:
				state = GameState::EExit;
                break;
            case SDL_MOUSEMOTION:
                inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                inputManager.releaseKey(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame() 
{
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix
	glm::mat4 projectionMatrix = camera.getCameraMatrix();
	GLint pUniform = textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Implement any drawing below this

	spriteBatch.begin();

	gameBoard.draw(spriteBatch);

	spriteBatch.end();

	spriteBatch.renderBatch();
   
	textureProgram.unuse();
    // Swap our buffer and draw everything to the screen!

    window.swapBuffer();
}