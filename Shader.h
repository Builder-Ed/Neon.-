#pragma once
#include<string>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; //ShaderProgramID.Define
	enum IMGSlot {
		IMGDiffuse,
		IMGSPECULAR

	};
	void use();
	void SetUniform3f(const char* paramNameString,glm::vec3 param);
	void SetUniform1f(const char* paramNameString,float param);
	void SetUniform1i(const char* paramNameString,int slot);
private:
	void CheckCompileErrors(unsigned int ID,std::string type);
	//~Shader();
};

