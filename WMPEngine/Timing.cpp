#include "Timing.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
namespace WMPEngine
{
	FPSLimiter::FPSLimiter()
	{

	}

	void FPSLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::setMaxFPS(float maxFPS)
	{
		this->maxFPS = maxFPS;
	}

	void FPSLimiter::begin()
	{
		startTicks = SDL_GetTicks();
	}

	float FPSLimiter::end()
	{
		CalculateFPS();

		float frameTicks = SDL_GetTicks() - startTicks;

		//limit the fps to the max FPS
		if (1000.0f / maxFPS > frameTicks)
			SDL_Delay(1000.0f / maxFPS - frameTicks);

		return fps;
	}

	void FPSLimiter::CalculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static auto prevTicks = SDL_GetTicks();

		GLuint currentTicks;
		currentTicks = SDL_GetTicks();

		frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

		prevTicks = currentTicks;

		int count;

		currentFrame++;

		if (currentFrame < NUM_SAMPLES)
			count = currentFrame;
		else count = NUM_SAMPLES;

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
			fps = 1000.0f / frameTimeAverage;
		else fps = 60.0f;
	}
}