#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace WMPEngine{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);
		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		//Setters
		void setPosition(const glm::vec2& newPosition){ position = newPosition;  needsMatrixUpdate = true; }
		void setScale(float newScale){ scale = newScale; needsMatrixUpdate = true; }
		//Getters
		float getScale() { return scale; }
		glm::vec2 getPosition() { return position; }
		glm::mat4 getCameraMatrix() { return cameraMatrix; }

	private:
		int screenWidth, screenHeight;
		bool needsMatrixUpdate;
		float scale;
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;

	};
}

