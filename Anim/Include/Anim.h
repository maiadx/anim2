#ifndef ANIM_HEADER
#define ANIM_HEADER
#include <stdio.h>


void AnimEndFrame()
{
   printf("ef\n");
}

void AnimSetBackgroundColor(float color[3])
{
    printf("cc %f %f %f\n", color[0], color[1], color[2]);
}

void AnimDrawSphere(float position[3], float color[3], float scale)
{   
    printf("sp %f %f %f %f %f %f %f\n", position[0], position[1], position[2], color[0], color[1],color[2], scale);
}

/* C does not support function overloading, so I had to change the name of this function to maintain compatibility. */
void AnimDrawSphereIJK(float i, float j, float k, float color[3], float scale)
{
    printf("sp %f %f %f %f %f %f %f\n", i, j, k, color[0], color[1], color[2], scale);
}

/* Load Compute Shader given filepath to .comp file [this feature is not yet fully supported.] */
void AnimLoadComputeShader(const char* filepath)
{
    printf("cs %s\n", filepath);
}

void AnimAddCSParticle(float initPosition[3], float initVelocity[3], float mass)
{

}

void AnimRunComputeShader()
{
    
}

void AnimDrawPlot()
{

}

void AnimDrawText(const char* msg)
{
    printf("dt %s\n", msg);
}

void AnimConsoleLog(const char* msg)
{
    printf("cl %s\n", msg);
}

void AnimShutdown()
{
    printf("ex\n");
}

#endif