#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));

}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}


glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position+Forward, WorldUp);
}
void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);		   
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
void Camera::ProcessMouseInput(float deltaX, float deltaY) {


	
		Pitch -= (deltaY * SenseY) / 4;
		Yaw -= (deltaX * SenseX) / 4;
		if (Pitch > 1.5) {
			Pitch = 1.5;
		}
		else if (Pitch < -1.5) {
			Pitch = -1.5;
		}
		//printf("%f", Pitch);
		UpdateCameraVectors();
}
void Camera::UpdateCameraPosition() {
	Position += Forward * speedZ *0.05f+Right*speedX*0.025f+Up*speedY*0.0425f;
	//Position += glm::normalize(glm::cross(Forward, Up)) * speedX * 0.025f;
}