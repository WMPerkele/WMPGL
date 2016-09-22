#include "Camera2D.h"
namespace WMPEngine{

	Camera2D::Camera2D() : position(0.0, 0.0), cameraMatrix(1.0f), scale(1.0f), needsMatrixUpdate(true), screenWidth(640), screenHeight(480), orthoMatrix(1.0f)
	{
	}


	Camera2D::~Camera2D()
	{
	}
	void Camera2D::init(int screenWidth, int screenHeight)
	{
		this->screenHeight = screenHeight;
		this->screenWidth = screenWidth;
		orthoMatrix = glm::ortho(0.0f, (float)this->screenWidth, 0.0f, (float)this->screenHeight);

	}

	void Camera2D::update()
	{
		if (needsMatrixUpdate)
		{
			glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);
			glm::vec3 scale(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;
			needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
	{
		//Invert y coords;
		screenCoords.y = screenHeight - screenCoords.y;
		//Make it so that the 0 is the center
		screenCoords -= glm::vec2(screenWidth / 2, screenHeight / 2);
		//Scale the coordinates
		screenCoords /= scale;
		//Translate with the camera position
		screenCoords += position;

		return screenCoords;
	}
}