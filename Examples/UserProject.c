#include "../Anim2/Include/Anim2.h"
/* This one header file is all you need to use Anim2. */

/* UserProject: This is where I test all the front-facing 
   features that a user would actually need to use. 
*/


int main()
{
    float arrayA[6] = {7.0f, 2.0f, 3.0f, 4.0f, -4.45f, 8.79f};
    float arrayB[6] = {0.0f, 12.0f, -4.0f, 7.0f, -4.45f, -1.79f};

    while(1)
    {
        DrawGraph("graph_A", arrayA, 6);
        DrawGraph("graph_B", arrayB, 6);
        EndFrame();
    }

    return 0;
}