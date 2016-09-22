#pragma once
namespace WMPEngine
{
	class FPSLimiter
	{
	public:
		FPSLimiter();

		void setMaxFPS(float maxFPS);

		void init(float targetFPS);

		void begin();

		//Returns the current fps
		float end();
	private:
		void CalculateFPS();
		float maxFPS;
		float fps;
		float frameTime;
		unsigned int startTicks;
	};
}