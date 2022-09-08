#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"
#include "Entity.h"
#include "Components.h"
#include "input.h"
#include "EngineTime.h"
#include "Log.h"

#include "UI/inspector.h"


using namespace core;

Camera::Camera(float aspect, float fov, float near, float far) :
	m_aspect{ aspect },
	m_fov	{ fov },
	m_near	{ near },
	m_far	{ far }
{}


glm::mat4 Camera::GetProjection(float aspect, float fov, float near, float far)
{
	m_aspect = aspect;
	m_fov = fov;
	m_near = near;
	m_far = far;
	return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::GetProjection()
{
	return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 5), glm::vec3(0, 1, 0));
	/*
	return glm::lookAt(GetTransform()->position, 
		GetTransform()->position + 
		GetTransform()->Front,
		GetTransform()->Up);
	*/
}

void Camera::OnStart()
{
	/*
	Component::OnStart();
	GetTransform()->position = glm::vec3(0.f, 0.f, 5.f);
	GetTransform()->rotation.y = -90.0f;
	UpdateCameraVectors();
	LOG_INFO("Camera Component Start");
	*/
}

void Camera::OnUpdate()
{

	/*
	glm::vec3 movement = v_axis * GetTransform()->Front + 
						-h_axis * GetTransform()->Right + 
						-u_axis * GetTransform()->Up;

	if (Input::GetMouseButtonDown(SDL_BUTTON_RIGHT))
		mouseDown = true;
	if (Input::GetMouseButtonUp(SDL_BUTTON_RIGHT))
		mouseDown = false;

	if (mouseDown) {
		GetTransform()->rotation.y += -Input::mouseVelocity.x * MouseSensitivity;
		GetTransform()->rotation.x += Input::mouseVelocity.y * MouseSensitivity;
	}

	GetTransform()->position += movement * Time::GetDelta() * speed;
	
	UpdateCameraVectors();
	*/
}

void Camera::UpdateCameraVectors()
{
	/*
	glm::vec3 front;
	front.x = cos(glm::radians(GetTransform()->rotation.y)) * cos(glm::radians(GetTransform()->rotation.x));
	front.y = sin(glm::radians(GetTransform()->rotation.x));
	front.z = sin(glm::radians(GetTransform()->rotation.y)) * cos(glm::radians(GetTransform()->rotation.x));
	GetTransform()->Front = glm::normalize(front);

	GetTransform()->Right = glm::normalize(glm::cross(GetTransform()->Front, GetTransform()->WorldUp));
	GetTransform()->Up = glm::normalize(glm::cross(GetTransform()->Right, GetTransform()->Front));
	*/
}
