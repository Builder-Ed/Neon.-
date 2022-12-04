#pragma once

#include<glm.hpp>
#include<gtx/rotate_vector.hpp>
//#include<gtc/matrix_transform.hpp>
class LightSpot
{
public:
	LightSpot(glm::vec3 _LSPos, glm::vec3 _LSAngles, glm::vec3 _LSColor = glm::vec3(1.0f, 1.0f, 1.0f));

	void UpdateDirection();
	glm::vec3 LSPos;
	glm::vec3 LSAngles;
	glm::vec3 LSDirection=glm::vec3(0,0,1.0f);
	glm::vec3 LSColor;

	float CosPhi = 0.9f;
};

