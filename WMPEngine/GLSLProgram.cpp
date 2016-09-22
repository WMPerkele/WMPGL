#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

namespace WMPEngine{
	GLSLProgram::GLSLProgram() : programID(0), vertexShaderID(0), fragmentShaderID(0), numAttributes(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath)
	{
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (vertexShaderID == 0)
			fatalError("Vertex shader failed to be created");

		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (fragmentShaderID == 0)
			fatalError("Fragment shader failed to be created");

		compileShader(vertexShaderFilePath, vertexShaderID);
		compileShader(fragmentShaderFilepath, fragmentShaderID);
	}

	void GLSLProgram::linkShaders()
	{
		//Vertex and fragment shaders are succesfully compiled
		//Now time to link them together into a program
		programID = glCreateProgram();

		//Attach our shaders to our program
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

		//Link our program
		glLinkProgram(programID);

		//Note the different functions here:: glGetProgram* instea of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
		//Incase linking fails do stuff below
		if (isLinked == GL_FALSE)
		{
			GLint maxLenght = 0;
			std::vector<GLchar> errorLog(maxLenght);
			glGetProgramInfoLog(programID, maxLenght, &maxLenght, &errorLog[0]);

			glDeleteProgram(programID);
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			std::printf("%s \n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " not found in shader");
		}

		return location;
	}


	void GLSLProgram::use()
	{
		glUseProgram(programID);
		for (int i = 0; i < numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}
	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShader(const std::string &filePath, GLuint id)
	{
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail())
		{
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line))
			fileContents += line + "\n";

		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);

			std::printf("%s \n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");
		}
	}
}
