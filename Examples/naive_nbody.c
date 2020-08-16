#include <Anim2/Anim.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define NUM_PARTICLES 10
#define GRAV_CONST (-4 * M_PI * M_PI)

typedef struct
{
	float position[3];
	float velocity[3];
	float color[3];
	float mass;
} Particle;

float mag(float vector[3])
{
	return sqrt( (vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]) );
}


void SetInitialConditions(Particle particles[NUM_PARTICLES])
{
	for(unsigned int i = 0; i < NUM_PARTICLES; i++)
	{
		particles[i].position[0] = (((float)rand()) / RAND_MAX) * 20 - 10; 
		particles[i].position[1] = (((float)rand()) / RAND_MAX) * 20 - 10; 
		particles[i].position[2] = (((float)rand()) / RAND_MAX) * 20 - 10; 

		particles[i].velocity[0] = 0;
		particles[i].velocity[1] = 0;
		particles[i].velocity[2] = 0;

		particles[i].color[0] = (((float)rand()) / RAND_MAX); 
		particles[i].color[1] = (((float)rand()) / RAND_MAX); 
		particles[i].color[2] = (((float)rand()) / RAND_MAX); 

		particles[i].mass = 100;
	}
}

void UpdateParticles(Particle* particles, float dt)
{
	for(unsigned int i = 0; i < NUM_PARTICLES; i++)
	{
		for(unsigned int j = 0; j < 3; j++)
			particles[i].position[j] += particles[i].velocity[j] * dt/2.0f;
	}

	for(unsigned int i = 0; i < NUM_PARTICLES-1; i++)
	{
		for(unsigned int j = i+1; j < NUM_PARTICLES; j++)
		{
			if(i != j)
			{
				/* displacement vector */
				float disp[3] = { (particles[i].position[0] - particles[j].position[0]), 
						          (particles[i].position[1] - particles[j].position[1]), 
						          (particles[i].position[2] - particles[j].position[2]) };

				float force[3];
				float forceB[3];

				for(unsigned int k = 0; k < 3; k++)
				{
					force[k] = (disp[k] * GRAV_CONST * particles[i].mass * particles[j].mass) / pow(mag(disp), 3); 
					forceB[k] = -1 * force[k];

					particles[i].velocity[k] += force[k] * dt * 1.0f/particles[i].mass; 
					particles[j].velocity[k] += force[k] * dt * 1.0f/particles[j].mass;
				}

				//printf("force %d: %f %f %f\n", i, force[0], force[1], force[2]);

				//printf("vel %d: %f %f %f\n", i, particles[i].velocity[0], particles[i].velocity[0], particles[i].velocity[0]);
			}
		}
	}

	for(unsigned int i = 0; i < NUM_PARTICLES; i++)
	{
		for(unsigned int j = 0; j < 3; j++)
			particles[i].position[j] += particles[i].velocity[j] * dt/2.0f;
	}

}


int main()
{
	float colorBg[3] = { 0.14f, 0.14f, 0.14f };
	AnimSetBackgroundColor(colorBg);

	Particle particles[NUM_PARTICLES];

	SetInitialConditions(particles);

  	float totalTime = 0.0f;
  	float dt = 0.0001f;

	const int stepsPerFrame = 100;
	unsigned int steps = 1;
	unsigned int years = 0;

	while(1)
	{
		if(steps % stepsPerFrame == 0)
		{
			for(int i = 0; i < NUM_PARTICLES; i++)
			{
				AnimDrawSphere(particles[i].position, particles[i].color, 1.0f);
			}
			AnimEndFrame();
			dt = 0;
		}

		UpdateParticles(particles, dt);

		totalTime += dt;
		if(totalTime >= 1.0f)
		{
			//AnimDrawText("A year has elapsed.");
      
      		totalTime = 0.0f;
			if(++years > 25000)
			{
				return 0;
			}
    	}
    	steps++;
	}
	return 0;
}