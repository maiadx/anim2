#include "pch.h"
#include "Renderer/RenderObjects/Camera.h"
#include "Core/Log.h"
#include "Utils/Math.h"
#include <GLFW/glfw3.h>
using namespace Anim;

Camera::Camera(const glm::vec3& position, const glm::vec3& rotation) : m_Pivot(position)
{
	m_Roll = Math::ToRadians(rotation.x);
	m_Pitch = Math::ToRadians(rotation.y);
	m_Yaw = Math::ToRadians(rotation.z);
	
	m_Zoom = 0.0f;
	m_Position = glm::vec3(0,0,0);
	m_Velocity = glm::vec3(0,0,0);
	
    m_AngleAroundPivot = M_PI;
    m_DistToPivot = 30;
	Update(0);

	for(int i = 0; i < 348; i++)
	{
		keyboard.SetKeyStatus(i, false);
	}

	GenerateProjectionMatrix();
}

Camera::~Camera()
{
	
}

void Camera::OnAttach()
{

}

void Camera::KeyEventRecieved(int keyCode, bool isPressed)
{
    keyboard.SetKeyStatus(keyCode, isPressed);
}

void Camera::OnEvent(const Event& e)
{
	switch (e.GetType())
	{
	case EventType::KEY_PRESS:
		KeyEventRecieved(((const KeyPressEvent&) e).GetKeyCode(), true);
		break;
	case EventType::KEY_RELEASE:
		KeyEventRecieved(((const KeyReleaseEvent&)e).GetKeyCode(), false);
		break;
	case EventType::MOUSE_BUTTON_PRESS:
		mouse.SetButton(((const MousePressEvent&) e).GetMouseCode(), true);
		break;
	case EventType::MOUSE_BUTTON_RELEASE:
		mouse.SetButton(((const MouseReleaseEvent&)e).GetMouseCode(), false);
		break;
	case EventType::MOUSE_MOVE:
		//const MouseMoveEvent& mouse_event = ((const MouseMoveEvent&)e);
		mouse.SetPosition(((const MouseMoveEvent&)e).GetX(), ((const MouseMoveEvent&)e).GetY());
		break;
	case EventType::MOUSE_SCROLL:
		mouse.SetDScroll(((const MouseScrollEvent&)e).GetYOffset() * -3);
		break;
	case EventType::WINDOW_RESIZE:
		this->m_AspectRatio = ((const WindowResizeEvent&)e).GetScreenWidth() / ((const WindowResizeEvent&)e).GetScreenHeight();
		break;
	default:
		break;
	}
}





// void Camera::Move(glm::vec3& pos, glm::vec3& dRot)
// {

// }

void Camera::Update(float dt)
{
	m_DistToPivot += mouse.GetDScroll() * 2 * m_DistToPivot *  dt;
	m_DistToPivot = Math::Max(m_DistToPivot, NEAR_PLANE);

	if(mouse.IsButtonDown(MouseCode::M_BUTTON_RIGHT) || mouse.IsButtonDown(MouseCode::M_BUTTON_MID))
	{
		if(keyboard.IsKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			float dx = mouse.GetDX() * Math::Max(m_DistToPivot, 2.0f)/500.0f;
			float dy = mouse.GetDY() * Math::Max(m_DistToPivot, 2.0f)/500.0f;

			m_Pivot.x -= dx * cosf(m_Yaw) - dy * sinf(m_Pitch) * sinf(m_Yaw);
			m_Pivot.y += dy * cosf(m_Pitch);
			m_Pivot.z -= dx * sinf(m_Yaw) + dy * sinf(m_Pitch) * cosf(m_Yaw);

		} else {
			m_Pitch -= mouse.GetDY()/200;
			m_AngleAroundPivot += mouse.GetDX()/200;
		}
	}

	float h_distance = m_DistToPivot * cosf(m_Pitch);
	float v_distance = m_DistToPivot * sinf(m_Pitch); 

	float theta = m_AngleAroundPivot;
	float x_offset = h_distance * sinf(theta);
	float z_offset = h_distance * cosf(theta);
	
	m_Yaw = M_PI - m_AngleAroundPivot;
	m_Position.x = m_Pivot.x - x_offset; 
	m_Position.z = m_Pivot.z - z_offset;
	m_Position.y = m_Pivot.y + v_distance;
}


glm::mat4 Camera::GetViewMatrix()
{
	return Math::GenerateViewMatrix({m_Position.x, m_Position.y, m_Position.z}, {m_Pitch, m_Yaw, m_Roll});
}

const glm::mat4& Camera::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 Camera::GetViewProjectionMatrix()
{
	return m_ViewMatrix * m_ProjectionMatrix;
}

void Camera::GenerateProjectionMatrix()
{
	m_ProjectionMatrix = glm::perspective(glm::radians(FOV+m_Zoom), m_AspectRatio, NEAR_PLANE, FAR_PLANE);	
}

// glm::mat4& Camera::ResetProjectionMatrix()
// {
// 	GenerateProjectionMatrix();
// 	return projectionMatrix;
// }

void Camera::SetPivot(glm::vec3& pivot)
{
	m_Pivot = pivot;
}

glm::vec3& Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetZoom(float zoom)
{
	if(zoom < MAX_ZOOM)
	{
		m_Zoom = MAX_ZOOM;
	} else if(zoom > MIN_ZOOM) {
		m_Zoom = MIN_ZOOM;
	} else {
	m_Zoom = zoom;
	}
}