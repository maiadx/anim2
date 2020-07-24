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

void AnimDrawPlot()
{

}

void AnimDrawText(const char* msg)
{
    printf("dt %s\n", msg);
}

#endif