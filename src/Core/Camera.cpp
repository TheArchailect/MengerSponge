#include "Camera.h"
#include <iostream>
#include "Application.h"

Camera::Camera(int width, int height)
{
	Pitch = -25;
	Yaw = -90;
	m_CameraSpeed = 8.0f;
	Aspect = (float)width / (float)height;
	FOV = 65.0f;
	m_Forward = glm::vec3(0.0f, 0.0f, -1.0f); // gets recalculated immidiately 
	m_Position = glm::vec3(0.0f, 15.0f, 35.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	Projection = glm::perspective(glm::radians(FOV), Aspect, 0.1f, 1000.0f);
	RegisterCallbacks();
}

void Camera::RegisterCallbacks()
{
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::VIEWPORT_RESIZE, std::bind(&Camera::ViewPortResize, this, std::placeholders::_1));
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_ROTATION, std::bind(&Camera::Rotate, this, std::placeholders::_1));
	// translation
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_BACKWARD, std::bind(&Camera::Backward, this, std::placeholders::_1));
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_FORWARD, std::bind(&Camera::Forward, this, std::placeholders::_1));
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_DOWN, std::bind(&Camera::Down, this, std::placeholders::_1));
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_UP, std::bind(&Camera::Up, this, std::placeholders::_1));
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_LEFT, std::bind(&Camera::Left, this, std::placeholders::_1));
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::CAMERA_RIGHT, std::bind(&Camera::Right, this, std::placeholders::_1));
	// tick
	EventManager::Get().CameraDispatcher.Subscribe(CameraEvent::TICK, std::bind(&Camera::Update, this, std::placeholders::_1));
}

void Camera::Update(const Event<CameraEvent>& e)
{
	float DeltaTime = Application::Get().GetUtils().m_DeltaTime;

	m_Forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	m_Forward.y = sin(glm::radians(Pitch));
	m_Forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	m_Forward = glm::normalize(m_Forward);
	// update the translation
	if (m_State.forward) m_Position += (m_CameraSpeed * m_Forward) * DeltaTime;
	if (m_State.backward) m_Position -= (m_CameraSpeed * m_Forward) * DeltaTime;
	if (m_State.left) m_Position -= (m_CameraSpeed * glm::normalize(glm::cross(m_Forward, m_Up))) * DeltaTime;
	if (m_State.right) m_Position += (m_CameraSpeed * glm::normalize(glm::cross(m_Forward, m_Up))) * DeltaTime;
	if (m_State.up) m_Position += (m_CameraSpeed * m_Up) * DeltaTime;
	if (m_State.down) m_Position -= (m_CameraSpeed * m_Up) * DeltaTime;
}

void Camera::ViewPortResize(const Event<CameraEvent>& e)
{
	Aspect = (float)e.windowWidth / (float)e.windowHeight;
	Projection = glm::perspective(glm::radians(FOV), Aspect, 0.1f, 1000.0f);
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

glm::mat4 Camera::GetProjection() const
{
	return Projection;
}

glm::quat Camera::ToQuaternion(float yaw, float pitch, float roll)
{
	float cy = cos(yaw * 0.5);
	float sy = sin(yaw * 0.5);
	float cp = cos(pitch * 0.5);
	float sp = sin(pitch * 0.5);
	float cr = cos(roll * 0.5);
	float sr = sin(roll * 0.5);

	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

void Camera::Rotate(const Event<CameraEvent>& e)
{
	
	Yaw += (e.m_CameraRotation.yaw * m_CameraSpeed) * Application::Get().GetUtils().m_DeltaTime;

	if (Yaw > 360.0f)
	{
		Yaw = 0;
	}
	else if (Yaw < -360)
	{
		Yaw += 360.0f;
	}

	if (Pitch > 87.0f)
	{
		Pitch = 87.0f;
	}
	else if (Pitch < -87.0f)
	{
		Pitch = -87.0f;
	}
	else
	{
		Pitch += (e.m_CameraRotation.pitch * m_CameraSpeed) * Application::Get().GetUtils().m_DeltaTime;
	}
}

void Camera::Forward(const Event<CameraEvent>& e)
{
	m_State.forward = e.b_CameraUpdate;
}

void Camera::Backward(const Event<CameraEvent>& e)
{
	m_State.backward = e.b_CameraUpdate;
}

void Camera::Left(const Event<CameraEvent>& e)
{
	m_State.left = e.b_CameraUpdate;
}

void Camera::Right(const Event<CameraEvent>& e)
{
	m_State.right = e.b_CameraUpdate;
}

void Camera::Up(const Event<CameraEvent>& e)
{
	m_State.up = e.b_CameraUpdate;
}

void Camera::Down(const Event<CameraEvent>& e)
{
	m_State.down = e.b_CameraUpdate;
}
