#pragma once
//#ifndef CAMERA_H
//#define CAMERA_H
//#endif // !CAMERA_H

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
class Camera {
public:
Camera(glm::vec3 position ,glm::vec3 target,glm::vec3 worldup);
Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
glm::vec3 Position;
glm::vec3 Forward;
glm::vec3 Right;
glm::vec3 Up;
glm::vec3 WorldUp;
float Pitch;
float Yaw;
float SenseX=0.0121f;
float SenseY=0.0121f;
float speedX = 0;
float speedY = 0;
float speedZ = 0;


glm::mat4 GetViewMatrix();
void ProcessMouseInput(float deltaX, float deltaY);
void UpdateCameraPosition();
private:
	void UpdateCameraVectors();
};
