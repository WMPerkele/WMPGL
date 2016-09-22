#include "sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>

namespace WMPEngine{

	sprite::sprite()
	{
		vboID = 0;
	}


	sprite::~sprite()
	{
		if (vboID != 0)
		{
			glDeleteBuffers(1, &vboID);
		}
	}


	void sprite::init(float x, float y, float w, float h, std::string texturePath)
	{
		xPos = x;
		yPos = y;
		width = w;
		height = h;

		texture = ResourceManager::getTexture(texturePath);



		if (vboID == 0)
			glGenBuffers(1, &vboID);

		//Vertexes for a rectangle
		Vertex vertexData[6];

		//First triangle
		vertexData[0].setPosition(x + w, y + h);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + h);
		vertexData[1].setUV(0.0f, 1.0f);


		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + w, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + w, y + h);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[4].setColor(255, 255, 255, 255);
		}

		vertexData[1].setColor(0, 0, 255, 255);

		vertexData[4].setColor(0, 255, 0, 255);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		

		//Draw the 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}