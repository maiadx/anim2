#pragma once
#include "pch.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"
#include "Core/Log.h"
#include "Utils/Math.h"
#include "Utils/Memory.h"

namespace Anim 
{ 
	/* structs to track state of mouse + keyboard */
	struct MouseStates
	{
		bool mouseButtons[3] = {false, false, false};
		bool middle = false;
		float mouseDX = 0.0f;
		float mouseDY = 0.0f;
		float prevMouseDX = 0.0f;
		float prevMouseDY = 0.0f;
		float deltaScroll = 0.0f;

		bool IsButtonDown(MouseCode mc)
		{
			return mouseButtons[mc];
		}	
		
		void SetButton(MouseCode mc, bool flag)
		{
			mouseButtons[mc] = flag;
		}

		void SetPosition(float x, float y)
		{
			if(mouseButtons[0] || mouseButtons[1] || mouseButtons[2])
			{
				mouseDX += (x - prevMouseDX);
				mouseDY += (y - prevMouseDY);

			}
				prevMouseDY = y;
				prevMouseDX = x;
		}
		
		float GetDX()
		{
			float dx = mouseDX;
			mouseDX = 0;
			return dx;
		}

		float GetDY()
		{
			float dy = mouseDY;
			mouseDY = 0;
			return dy;
		}

		void SetDScroll(float scroll_y)
		{
			deltaScroll += scroll_y;
		}

		float GetDScroll()
		{
			float dy = deltaScroll;
			deltaScroll = 0;
			return dy;
		}
	};


	struct KeyboardStates {
		bool keys[348];
		void Init()
		{
			for(unsigned int i = 0; i < 91; i++)
			{
				keys[i] = false;
			}
		}
		bool IsKeyDown(int keycode)
		{
			return keys[keycode];
		}

		void SetKeyStatus(int keycode, bool flag)
		{
			keys[keycode] = flag;
		}
	};


	class Camera : public EventListener
	{
		void KeyEventRecieved(int keyCode, bool isPressed);

	protected:
		void GenerateProjectionMatrix();
		MouseStates mouse;
		KeyboardStates keyboard;

		glm::vec3 m_Position;
		glm::vec3 m_Velocity;
		/* --- */

		glm::vec3 m_Pivot;							/* point the camera rotates around */
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		float m_Yaw;
		float m_Pitch;
		float m_Roll;
		float m_Zoom;
		float m_AspectRatio = 1920.0f/1080.0f;	/* default aspect ratio */

		float m_ZoomSpeed;
		float m_MoveSpeed;
		float m_AngleAroundPivot;
		float m_DistToPivot;
		glm::vec3 m_DeltaPos;


		const float FOV = 60.0f;				/* 60 -> ~80 is recommended */
		const float NEAR_PLANE = 0.01f;			/* min clipping dist. */
		const float FAR_PLANE = 10000.0f;		/* max clipping dist. */

		const double MIN_ZOOM = 22;
		const double MAX_ZOOM = -22;


		const float DEFAULT_MOVE_SPEED = 6.5;
		const float DEFAULT_ROT_SPEED = 80;



	public:
		Camera(const glm::vec3& pos, const glm::vec3& rot);
		~Camera();

		void OnAttach();
		void OnEvent(const Event &e);


		void Update(float dt);
		
		glm::vec3& GetPosition();
		inline float GetZoom()  { return m_Zoom;  }
		inline float GetRoll()  { return m_Roll;  }
		inline float GetPitch() { return m_Pitch; }
		inline float GetYaw()   { return m_Yaw;   }

		const glm::mat4& GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetViewProjectionMatrix();

		void SetPivot(glm::vec3& pivot);
		void SetZoom(float zoom);
		void SetPitch(float pitch);
		void SetYaw(float yaw);
};
}