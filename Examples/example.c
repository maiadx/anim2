#include <Anim2/Anim.h>
#include <math.h>
#include <stdlib.h>

#define NUM_BALLS 1000

int main()
{
	float colorBackground[3] = { 0.14f, 0.14f, 0.14f };
	AnimSetBackgroundColor(colorBackground);
	
	float ballColor[3] = { 0.2f, 0.2f, 0.9f };

	float ballPositions[NUM_BALLS][3];

	for(int i = 0; i < NUM_BALLS; i++)
	{
		ballPositions[i][0] = ((20*(float) rand())/RAND_MAX); // = { ((20*(float) rand())/RAND_MAX), ((20*(float) rand())/RAND_MAX), ((20*(float) rand())/RAND_MAX) };
		ballPositions[i][1] = ((20*(float) rand())/RAND_MAX);
		ballPositions[i][2] = ((20*(float) rand())/RAND_MAX);
	}

	while(1)
	{
		for(int i = 0; i < NUM_BALLS; i++)
		{
			AnimDrawSphere(ballPositions[i], ballColor, 0.5f);
		}

		AnimEndFrame();
	}

	return 0;
}