#pragma once

#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
//#include<gtc/matrix_transform.hpp>
class LightPoint
{
public:
	LightPoint(glm::vec3 _LPPos, glm::vec3 _LPAngles, glm::vec3 _LPColor = glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 LPPos;
	glm::vec3 LPAngles;
	glm::vec3 LPColor;

	float constant;
	float linear;
	float quadratic;
	float CosPhi;
};

