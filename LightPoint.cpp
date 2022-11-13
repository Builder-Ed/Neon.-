#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _LPPos, glm::vec3 _LPAngles, glm::vec3 _LPColor) :
	LPPos	(_LPPos),
	LPAngles	(_LPAngles),
	LPColor	(_LPColor)
	 {
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

}

