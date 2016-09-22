#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
namespace WMPEngine{

	enum EWindowFlags
	{
		EINVISIBLE = 0x1,
		EFULLSCREEN = 0x2,
		EBORDERLESS = 0x4
	};
	class Window
	{
	public:
		Window();
		~Window();

		void swapBuffer();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		int getScreenWidth() { return screenWidth; }
		int getScreenHeight() { return screenHeight; }
	private:
		SDL_Window* sdlWindow;
		int screenWidth, screenHeight;
	};
}
