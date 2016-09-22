#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
namespace WMPEngine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);
		
		/// Returns true if key is held down
		bool isKeyDown(unsigned int keyID);

		/// Returns true if key was pressed
		bool isKeyPressed(unsigned int keyID);

		glm::vec2 getMouseCoords() const { return mouseCoords; }

	private:
		bool wasKeyDown(unsigned int keyID);
		std::unordered_map<unsigned int, bool> keyMap;
		std::unordered_map<unsigned int, bool> prevKeyMap;
		glm::vec2 mouseCoords;
	};
}
