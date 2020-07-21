#include <Anim2/Anim.h>

int main()
{

	float position[3] = { -1, -11, 1 };
	float positionB[3] = { 1, 4, -5 };

	float color[3] = { 0, 0, 1 };
	float colorB[3] = { 0.5f, 0.0f, 0.0f };
	
	float colorBackground[3] = { 0.14f, 0.14f, 0.14f };
	AnimSetClearColor(colorBackground);

	while(1)
	{
		AnimDrawSphere(position, color, 1.0f);
		AnimDrawSphere(positionB, colorB, 1.5f);

		AnimEndFrame();
	}

	return 0;
}