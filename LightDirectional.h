#pragma once

#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
//#include<gtc/matrix_transform.hpp>
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _LDPos, glm::vec3 _LDAngles, glm::vec3 _LDColor=glm::vec3(1.0f,1.0f,1.0f));
	void UpdateDirection();
	glm::vec3 LDPos;
	glm::vec3 LDAngles;
	glm::vec3 LDColor;
	glm::vec3 LDDirection = glm::vec3(0, 0, 1.0f);

	
};

