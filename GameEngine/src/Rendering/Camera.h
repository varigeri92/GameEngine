#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace core {
}
	class Camera
	{
	public:
		
		Camera(float aspect, float fov, float near, float far);

		glm::mat4 GetProjection(float aspect, float fov, float near, float far);
		glm::mat4 GetProjection();

		glm::mat4 GetView();
		void OnStart();
		void OnUpdate();



		float MovementSpeed;
		float Zoom;

	private:
		float m_aspect;
		float m_fov;
		float m_near; 
		float m_far;

		bool mouseDown;

		float v_axis, h_axis, u_axis;
		const float MouseSensitivity = 3.f;
		const float speed = 1.5f;

		void UpdateCameraVectors();
	};
