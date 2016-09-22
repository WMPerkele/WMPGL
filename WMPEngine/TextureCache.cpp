#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace WMPEngine{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		auto itr = textureMap.find(texturePath);

		//If the map doesnt have the texture
		if (itr == textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it into the map
			textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
		return itr->second;
	}
}
