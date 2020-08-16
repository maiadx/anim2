#include <Anim2/Anim.h>
#include <stdlib.h>


#define NUM_PARTICLES 100

int main()
{
	float colorBg[3] = { 0.14f, 0.14f, 0.14f };
	AnimSetBackgroundColor(colorBg);

	float particlePositions[NUM_PARTICLES][3];
	float particleColors[NUM_PARTICLES][3];

	for(int i = 0; i < NUM_PARTICLES; i++)
	{
		particlePositions[i][0] = (((float)rand()) / RAND_MAX) * 20 - 10; 
		particlePositions[i][1] = (((float)rand()) / RAND_MAX) * 20 - 10; 
		particlePositions[i][2] = (((float)rand()) / RAND_MAX) * 20 - 10; 

		particleColors[i][0] = (((float)rand()) / RAND_MAX); 
		particleColors[i][1] = (((float)rand()) / RAND_MAX); 
		particleColors[i][2] = (((float)rand()) / RAND_MAX); 
	}


	int timestepsElapsed = 0;

	while(42)
	{

		for(unsigned int i = 0; i < NUM_PARTICLES; i++)
		{
			AnimDrawSphere(particlePositions[i], particleColors[i], 1);
		}


			AnimEndFrame();

	}


	AnimShutdown();
	return 0;
}