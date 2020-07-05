#include <stdio.h>
#include <stdint.h>
/* This is the standalone header file that contains the abstractions to
   send messages to Anim2 from the Client program via stdio redirection 
*/

void DrawGraph(char* name, float * data, uint32_t size)
{
   printf("gr %s", name);
   for(uint32_t i = 0; i < size; i++)
   {
      printf(" %f", data[i]);
   }
   printf("\n");
}

void EndFrame()
{
   printf("ef\n");
}

