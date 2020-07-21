#include "pch.h"
#include "Renderer/RenderObjects/Camera.h"
#include "Core/Log.h"
#include "Utils/Math.h"
#include <GLFW/glfw3.h>
using namespace Anim;

Camera::Camera(const glm::vec3& pos, const glm::vec3& rot) : pivot(pos)
{
	this->roll = Math::ToRadians(rot.x);
	this->pitch = Math::ToRadians(rot.y);
	this->yaw = Math::ToRadians(rot.z);
	this->zoom = 0.0f;
	position = glm::vec3(0,0,0);
	velocity = glm::vec3(0,0,0);
	
    angleAroundPivot = M_PI;
    distToPivot = 30;
	zoom = 0;
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
		this->camAspectRatio = ((const WindowResizeEvent&)e).GetScreenWidth() / ((const WindowResizeEvent&)e).GetScreenHeight();
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
	distToPivot += mouse.GetDScroll() * 2 * distToPivot *  dt;
	distToPivot = Math::Max(distToPivot, NEAR_PLANE);

	if(mouse.IsButtonDown(MouseCode::M_BUTTON_RIGHT) || mouse.IsButtonDown(MouseCode::M_BUTTON_MID))
	{
		if(keyboard.IsKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			float dx = mouse.GetDX() * Math::Max(distToPivot, 2.0f)/500.0f;
			float dy = mouse.GetDY() * Math::Max(distToPivot, 2.0f)/500.0f;

			pivot.x -= dx * cosf(yaw) - dy * sinf(pitch) * sinf(yaw);
			pivot.y += dy * cosf(pitch);
			pivot.z -= dx * sinf(yaw) + dy * sinf(pitch) * cosf(yaw);

		} else {
			pitch -= mouse.GetDY()/200;
			angleAroundPivot += mouse.GetDX()/200;
		}
	}

	float h_distance = distToPivot * cosf(pitch);
	float v_distance = distToPivot * sinf(pitch); 

	float theta = angleAroundPivot;
	float x_offset = h_distance * sinf(theta);
	float z_offset = h_distance * cosf(theta);
	
	yaw = M_PI - angleAroundPivot;
	position.x = pivot.x - x_offset; 
	position.z = pivot.z - z_offset;
	position.y = pivot.y + v_distance;
}


Mat4 Camera::GetViewMatrix()
{
	return Math::GenerateViewMatrix({position.x, position.y, position.z}, {pitch, yaw, roll});
}

const Mat4& Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

Mat4 Camera::GetViewProjectionMatrix()
{
	return viewMatrix * projectionMatrix;
}

void Camera::GenerateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(FOV+zoom), camAspectRatio, NEAR_PLANE, FAR_PLANE);	
}

// glm::mat4& Camera::ResetProjectionMatrix()
// {
// 	GenerateProjectionMatrix();
// 	return projectionMatrix;
// }

void Camera::SetPivot(glm::vec3& pivot)
{
	this->pivot = pivot;
}

glm::vec3& Camera::GetPosition()
{
	return position;
}

void Camera::SetZoom(float z)
{
	if(z < MAX_ZOOM)
	{
		this->zoom = MAX_ZOOM;
	} else if(z > MIN_ZOOM) {
		this->zoom = MIN_ZOOM;
	} else {
	this->zoom = z;
	}
}