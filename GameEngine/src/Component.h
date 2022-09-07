#pragma once
#include "Engine.h"
#include "EngineTime.h"


namespace core
{
	struct Entity;
	struct Transform;

	class Component
	{
	public:
		
		Component();

		virtual void OnAwake();
		virtual void OnStart();
		virtual void OnUpdate();
		
		void OnApplicationClose();

		Entity* entity = nullptr;
		Transform* transform = nullptr;

	protected:
		uint64_t UUID;


		//TEST::
		void UpdateCameraVectors();
		
		bool mouseDown;
		float v_axis, h_axis, u_axis;
		float MouseSensitivity = 3.f;
		float speed = 5.f;

		friend class Engine;
	};
}

