#include "InputManager.h"

namespace WMPEngine
{

	InputManager::InputManager() : mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		for (auto& it : keyMap)
		{
			prevKeyMap[it.first] = it.second;
		}
	}


	void InputManager::setMouseCoords(float x, float y)
	{
		mouseCoords.x = x;
		mouseCoords.y = y;
	}


	void InputManager::pressKey(unsigned int keyID)
	{
		keyMap[keyID] = true;
	}
	
	void InputManager::releaseKey(unsigned int keyID)
	{
		keyMap[keyID] = false;
	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		
		auto it = keyMap.find(keyID);
		if (it != keyMap.end())
			return it->second;
		else
			return false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{

		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
		{
			bool isPressed;
			return true;
		}

		return false;
	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = prevKeyMap.find(keyID);
		if (it != prevKeyMap.end())
			return it->second;
		else
			return false;
	}
}
