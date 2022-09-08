#include "Component.h"
#include "Log.h"

#include <random>
#include <limits>     /* time */
#include "Entity.h"
#include "SDL.h"
#include "input.h"
#include "EngineTime.h"

#include "Components.h"


//core::Transform* transform = nullptr;


core::Component::Component() :
	UUID{ 0 }
{
	std::random_device rd;    
	std::mt19937_64 eng(rd());
	std::uniform_int_distribution<uint64_t> distr;
	UUID = distr(eng);
	mouseDown = false;
	h_axis = 0;
	v_axis = 0;
	u_axis = 0;

	LOG_INFO("Component Constructed ");
	
}

void core::Component::OnAwake()
{
	LOG_INFO("entitty onAwake " << entity->name);
}

void core::Component::OnStart()
{
	
	transform = &entity->GetComponet<Transform>();
	transform->rotation.y = -90;
	
	transform->position.x = 0;
	transform->position.y = 0;
	transform->position.z = 8;

	LOG_INFO("entitty onStart " << entity->name);
	UpdateCameraVectors();
}

void core::Component::OnUpdate()
{

	if (Input::GetKey(SDLK_w)) {
		v_axis = 1;
	}
	else if (Input::GetKeyUp(SDLK_w)) {
		v_axis = 0;
	}

	if (Input::GetKey(SDLK_s)) {
		v_axis = -1;
	}
	else if (Input::GetKeyUp(SDLK_s)) {
		v_axis = 0;
	}

	if (Input::GetKey(SDLK_a)) {
		h_axis = 1;
	}
	else if (Input::GetKeyUp(SDLK_a)) {
		h_axis = 0;
	}

	if (Input::GetKey(SDLK_d)) {
		h_axis = -1;
	}
	else if (Input::GetKeyUp(SDLK_d)) {
		h_axis = 0;
	}

	if (Input::GetKey(SDLK_q)) {
		u_axis = 1;
	}
	else if (Input::GetKeyUp(SDLK_q)) {
		u_axis = 0;
	}

	if (Input::GetKey(SDLK_e)) {
		u_axis = -1;
	}
	else if (Input::GetKeyUp(SDLK_e)) {
		u_axis = 0;
	}
	
	glm::vec3 movement = v_axis * entity->GetComponet<Transform>().Front +
						-h_axis * entity->GetComponet<Transform>().Right +
						-u_axis * entity->GetComponet<Transform>().Up;


	if (Input::GetMouseButton(SDL_BUTTON_RIGHT)) {
		entity->GetComponet<Transform>().rotation.y += -Input::mouseVelocity.x * MouseSensitivity * Time::GetDelta();
		entity->GetComponet<Transform>().rotation.x += Input::mouseVelocity.y * MouseSensitivity * Time::GetDelta();
	}

	entity->GetComponet<Transform>().position += movement * Time::GetDelta() * speed;

	UpdateCameraVectors();
}


void core::Component::UpdateCameraVectors()
{

	glm::vec3 front;
	front.x = cos(glm::radians(entity->GetComponet<Transform>().rotation.y)) * cos(glm::radians(entity->GetComponet<Transform>().rotation.x));
	front.y = sin(glm::radians(entity->GetComponet<Transform>().rotation.x));
	front.z = sin(glm::radians(entity->GetComponet<Transform>().rotation.y)) * cos(glm::radians(entity->GetComponet<Transform>().rotation.x));
	entity->GetComponet<Transform>().Front = glm::normalize(front);

	entity->GetComponet<Transform>().Right = glm::normalize(glm::cross(entity->GetComponet<Transform>().Front, entity->GetComponet<Transform>().WorldUp));
	entity->GetComponet<Transform>().Up = glm::normalize(glm::cross(entity->GetComponet<Transform>().Right, entity->GetComponet<Transform>().Front));
}
	


void core::Component::OnApplicationClose()
{
	LOG_INFO("entitty onAppClosed " << entity->name);

}


