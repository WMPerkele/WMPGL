#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>
namespace WMPEngine{
	class sprite
	{
	public:
		sprite();
		~sprite();

		void init(float x, float y, float w, float h, std::string texturePath);

		void draw();
	private:
		int xPos;
		int yPos;
		int width;
		int height;
		GLuint vboID;
		GLTexture texture;

	};
}

