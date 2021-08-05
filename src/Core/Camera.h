#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../Event/EventManager.h"

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
	glm::quat ToQuaternion(float yaw, float pitch, float roll);
	float Yaw;
	float Pitch;
	glm::vec3 m_Position;

private:
	void Rotate(const Event<CameraEvent>& e);
	void Forward(const Event<CameraEvent>& e);
	void Backward(const Event<CameraEvent>& e);
	void Left(const Event<CameraEvent>& e);
	void Right(const Event<CameraEvent>& e);
	void Up(const Event<CameraEvent>& e);
	void Down(const Event<CameraEvent>& e);

private:
	glm::mat4 Projection;
	glm::mat4 View;
	glm::vec3 m_Forward;
	glm::vec3 m_Up;
	float FOV;
	float Aspect;
	float m_CameraSpeed;
	CAMERA_STATE m_State;

};


