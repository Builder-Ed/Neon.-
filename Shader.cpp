#include <fstream>
#include <sstream>
#include<iostream>
#include "Shader.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

using namespace std;
Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw exception("Failed.To.Open.Vertex/Fragment.File:(");
		}
		vertexSStream<<vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
		//printf(vertexSource);
		//printf(fragmentSource);

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource,NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex,"VERTEX");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception&ex)
	{
		printf(ex.what());
	}
}
void Shader::use() {
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x,param.y,param.z);
}

void Shader::SetUniform1f(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::SetUniform1i(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}

void Shader::CheckCompileErrors(unsigned int ID, std::string type) {
	int success;
	char infolog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID,512,NULL,infolog);
			cout << "Shader.Compile.Error:\n" << infolog <<endl;

		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infolog);
			cout << "Program.Linking.Error:\n" << infolog << endl;
		}
	}
}








//Shader::~Shader() {
//	
//}
