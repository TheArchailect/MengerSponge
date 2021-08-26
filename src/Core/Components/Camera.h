#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Event/EventManager.h"

struct CAMERA_STATE
{
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool forward = false;
	bool backward = false;
};

class Camera
{
public:
	Camera(int width, int height);
	void ViewPortResize(const Event<CameraEvent>& e);
	void RegisterCallbacks();
	void Update(const Event<CameraEvent>& e);
	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
	glm::vec3 GetPostition() const;
	glm::vec3 GetForward() const;
	void Reset(glm::vec3 pos, float y, float p);

private:
	void Rotate(const Event<CameraEvent>& e);
	void Forward(const Event<CameraEvent>& e);
	void Backward(const Event<CameraEvent>& e);
	void Left(const Event<CameraEvent>& e);
	void Right(const Event<CameraEvent>& e);
	void Up(const Event<CameraEvent>& e);
	void Down(const Event<CameraEvent>& e);

private:
	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::vec3 m_Up;
	float FOV;
	float m_Aspect;
	float m_CameraSpeed;
	CAMERA_STATE m_State;
	float m_Yaw;
	float m_Pitch;
	glm::vec3 m_Position;
	glm::vec3 m_Forward;

};


