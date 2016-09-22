#include "ResourceManager.h"
namespace WMPEngine{

	TextureCache ResourceManager::textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return textureCache.getTexture(texturePath);
	}
}