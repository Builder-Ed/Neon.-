#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _LSPos, glm::vec3 _LSAngles, glm::vec3 _LSColor) :
	LSPos(_LSPos),
	LSAngles(_LSAngles),
	LSColor(_LSColor)
{
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	glm::vec3 LSPos;
	glm::vec3 LSAngles;
	glm::vec3 LSColor;
	glm::vec3 LSDirection = glm::vec3(0, 0, 1.0f);

	
}

