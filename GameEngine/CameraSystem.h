#pragma once
#include "Components.h"
#include "glm/glm.hpp";

namespace core {
	void InitCameraTransform(Transform& transform, glm::vec3 pos, glm::vec3 eulers);
	void UpdateCameraTransform(Transform& transform);
	void UpdateCameraProj(CameraComponent& cameraComponent, float aspect, float fov, float near, float far);
	void UpdateCameraProj_Aspect(CameraComponent& cameraComponent, float aspect);
	void UpdateCameraProj_Fov(CameraComponent& cameraComponent, float fov);

	void FlyCameraUpdate(Transform& transform, CameraComponent& cameraComponent);
}