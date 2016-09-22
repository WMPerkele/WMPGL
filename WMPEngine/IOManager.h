#pragma once
#include <string>
#include <vector>
namespace WMPEngine{

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}

