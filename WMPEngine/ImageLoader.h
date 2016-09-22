#pragma once
#include "GLTexture.h"
#include <string>
namespace WMPEngine{

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);

	};
}
