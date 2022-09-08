#include "CameraSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Entity.h"
#include "input.h"
#include "EngineTime.h"

void core::InitCameraTransform(Transform& transform, glm::vec3 pos, glm::vec3 eulers)
{
	transform.position = pos;
	transform.rotation = eulers;
}

void core::UpdateCameraTransform(Transform& transform)
{
	glm::vec3 front;
	front.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	front.y = sin(glm::radians(transform.rotation.x));
	front.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	transform.Front = glm::normalize(front);
	transform.Right = glm::normalize(glm::cross(transform.Front, transform.WorldUp));
	transform.Up = glm::normalize(glm::cross(transform.Right, transform.Front));
}

void core::UpdateCameraProj(CameraComponent& cameraComponent, float aspect, float fov, float near, float far)
{
	cameraComponent.m_aspect = aspect;
	cameraComponent.m_fov = fov;
	cameraComponent.m_near = near;
	cameraComponent.m_far = far;
	cameraComponent.proj = glm::perspective(glm::radians(fov), aspect, near, far);
}

void core::UpdateCameraProj_Aspect(CameraComponent& cameraComponent, float aspect)
{
	cameraComponent.m_aspect = aspect;
	cameraComponent.proj = 
		glm::perspective(glm::radians(cameraComponent.m_fov), cameraComponent.m_aspect, cameraComponent.m_near, cameraComponent.m_far);
}

void core::UpdateCameraProj_Fov(CameraComponent& cameraComponent, float fov)
{
	cameraComponent.m_fov = fov;
	cameraComponent.proj = 
		glm::perspective(glm::radians(cameraComponent.m_fov), cameraComponent.m_aspect, cameraComponent.m_near, cameraComponent.m_far);
}

void core::FlyCameraUpdate(Transform& transform, CameraComponent& cameraComponent)
{
	if (Input::GetKey(SDLK_w)) {
		cameraComponent.v_axis = 1;
	}
	else if (Input::GetKeyUp(SDLK_w)) {
		cameraComponent.v_axis = 0;
	}

	if (Input::GetKey(SDLK_s)) {
		cameraComponent.v_axis = -1;
	}
	else if (Input::GetKeyUp(SDLK_s)) {
		cameraComponent.v_axis = 0;
	}

	if (Input::GetKey(SDLK_a)) {
		cameraComponent.h_axis = 1;
	}
	else if (Input::GetKeyUp(SDLK_a)) {
		cameraComponent.h_axis = 0;
	}

	if (Input::GetKey(SDLK_d)) {
		cameraComponent.h_axis = -1;
	}
	else if (Input::GetKeyUp(SDLK_d)) {
		cameraComponent.h_axis = 0;
	}

	if (Input::GetKey(SDLK_q)) {
		cameraComponent.u_axis = 1;
	}
	else if (Input::GetKeyUp(SDLK_q)) {
		cameraComponent.u_axis = 0;
	}

	if (Input::GetKey(SDLK_e)) {
		cameraComponent.u_axis = -1;
	}
	else if (Input::GetKeyUp(SDLK_e)) {
		cameraComponent.u_axis = 0;
	}

	glm::vec3 movement = cameraComponent.v_axis * transform.Front +
		-cameraComponent.h_axis * transform.Right +
		-cameraComponent.u_axis * transform.Up;


	if (Input::GetMouseButton(SDL_BUTTON_RIGHT)) {
		transform.rotation.y += -Input::mouseVelocity.x * cameraComponent.MouseSensitivity * Time::GetDelta();
		transform.rotation.x += Input::mouseVelocity.y * cameraComponent.MouseSensitivity * Time::GetDelta();
	}

	transform.position += movement * Time::GetDelta() * cameraComponent.speed;

	UpdateCameraTransform(transform);
}

