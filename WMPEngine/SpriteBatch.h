#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

namespace WMPEngine{

	enum class GlyphSortType
	{
		ENONE,
		EFRONT_TO_BACK,
		EBACK_TO_FRONT,
		ETEXTURE
	};
	struct Glyph
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex botLeft;
		Vertex topRight;
		Vertex botRight;
	};
	struct RenderBatch
	{
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
			numVertices(NumVertices), texture(Texture) {	}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};
	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::ETEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
		
		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint vbo;
		GLuint vao;

		GlyphSortType sortType;

		std::vector<Glyph*> glyphs;

		std::vector<RenderBatch> renderBatches;
		
	};
}

