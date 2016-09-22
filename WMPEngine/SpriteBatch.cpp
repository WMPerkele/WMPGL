#include "SpriteBatch.h"
#include <algorithm>
namespace WMPEngine{

	SpriteBatch::SpriteBatch() : vbo(0), vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}


	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType)
	{
		this->sortType = sortType;
		renderBatches.clear();
		for (int i = 0; i < glyphs.size(); i++)
			delete glyphs[i];

		glyphs.clear();
	}
	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatches();

	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->botLeft.color = color;
		newGlyph->botLeft.setPosition(destRect.x, destRect.y);
		newGlyph->botLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->botRight.color = color;
		newGlyph->botRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->botRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		glyphs.push_back(newGlyph);

	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(vao);

		for (int i = 0; i < renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}
	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(glyphs.size() * 6);

		if (glyphs.empty())
			return;

		int offset = 0;
		int cv = 0; //current vertex
		renderBatches.emplace_back(offset, 6, glyphs[0]->texture);
		vertices[cv++] = glyphs[0]->topLeft;
		vertices[cv++] = glyphs[0]->botLeft;
		vertices[cv++] = glyphs[0]->botRight;
		vertices[cv++] = glyphs[0]->botRight;
		vertices[cv++] = glyphs[0]->topRight;
		vertices[cv++] = glyphs[0]->topLeft;
		offset += 6;

		for (int i = 1; i < glyphs.size(); i++)
		{
			if (glyphs[i]->texture != glyphs[i - 1]->texture)
				renderBatches.emplace_back(offset, 6, glyphs[i]->texture);
			else
				renderBatches.back().numVertices += 6;

			vertices[cv++] = glyphs[i]->topLeft;
			vertices[cv++] = glyphs[i]->botLeft;
			vertices[cv++] = glyphs[i]->botRight;
			vertices[cv++] = glyphs[i]->botRight;
			vertices[cv++] = glyphs[i]->topRight;
			vertices[cv++] = glyphs[i]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//orhan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() *sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
 	}


	void SpriteBatch::createVertexArray()
	{
		if (vao == 0)
			glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		if (vbo == 0)
			glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attrivute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGlyphs()
	{
		switch (sortType)
		{
		case GlyphSortType::EBACK_TO_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::EFRONT_TO_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::ETEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
		}
	}
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}
}

