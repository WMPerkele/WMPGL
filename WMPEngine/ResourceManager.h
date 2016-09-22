#pragma once
#include "TextureCache.h"
#include <string>
namespace WMPEngine{

	class ResourceManager
	{
	public:

		static GLTexture getTexture(std::string texturePath);


	private:
		static TextureCache textureCache;
	};
}
