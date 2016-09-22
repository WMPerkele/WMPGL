#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
namespace WMPEngine{

	void fatalError(std::string errorString)
	{
		std::cout << errorString << SDL_GetError() << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(69);

	}
}