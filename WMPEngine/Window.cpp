#include "Window.h"
#include "Errors.h"

namespace WMPEngine{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}
	/* FullScreen 2, Borderless 4, Fullscreen and borderless 6*/
	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & EINVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (currentFlags & EFULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (currentFlags & EBORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;


		sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (sdlWindow == NULL)
			fatalError("Window couldnt be created");

		SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);
		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created");


		GLenum error = glewInit();
		if (error != GLEW_OK)
			fatalError("Could not initialize glew");

		std::printf("***  OpenGL Version: %s  ***", glGetString(GL_VERSION));



		glClearColor(0.5, 0.5, 1, 1);

		//Turns off VSYNC
		SDL_GL_SetSwapInterval(0);

		//Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(sdlWindow);
	}
}
