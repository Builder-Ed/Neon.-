#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 _LDPos, glm::vec3 _LDAngles, glm::vec3 _LDColor) :
	LDPos(_LDPos),
	LDAngles(_LDAngles),	
	LDColor(_LDColor)
	{
	UpdateDirection();
	}



void LightDirectional::UpdateDirection() {
	//ResetDirectionToZ
	LDDirection = glm::vec3(0, 0, 1.0f);
	LDDirection = glm::rotateZ(LDDirection, LDAngles.z);
	LDDirection = glm::rotateX(LDDirection, LDAngles.x);
	LDDirection = glm::rotateY(LDDirection, LDAngles.y);
	LDDirection = -1.0f * LDDirection;
}

