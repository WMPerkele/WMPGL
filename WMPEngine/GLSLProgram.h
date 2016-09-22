#pragma once
#include <string>
#include <GL/glew.h>

namespace WMPEngine{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();
	private:

		void compileShader(const std::string& filePath, GLuint id);
		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;
		int numAttributes;

	};
}

