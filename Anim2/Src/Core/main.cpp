#include "Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace Anim;



void Init()
{
    std::cout << "Initializing..." << std::endl;
    Renderer::Init();

}

void Shutdown()
{
    std::cout << "Shutting down..." << std::endl;
    Renderer::Shutdown();
}

void RunCommand(std::vector<std::string>& inputCmd)
{
    if(inputCmd[0] == "gr")                             /* graph */
    {
        std::string name = inputCmd[1];                 /* first arg of graph is name, then data */
        std::vector<float> data(inputCmd.size()-2);
        
        for(uint32_t i = 2; i < inputCmd.size(); i++)
        {
            data[i-2] = atof(inputCmd[i].c_str());
        }

        Plot plot;
        plot.name = name;
        plot.data = data;
        //std::cout << "Recieved command to graph stuff" << std::endl;

        
        Renderer::DrawPlot(plot);

    } else if(inputCmd[0] == "sp")                      /* draw a sphere */
    {

    } else if(inputCmd[0] == "ef")                      /* end frame */
    {
        //std::cout << "end frame" << std::endl;
        Renderer::EndFrame();
        Renderer::BeginFrame();
    }
}

/* grabs input from stdio */
void PollUserInput()
{
    std::string input;
    std::getline(std::cin, input);
    std::stringstream stream(input);
    
    std::string token;
    std::vector<std::string> tokens;

    while(std::getline(stream, token, ' '))
    {
        tokens.push_back(token);    
    }

    RunCommand(tokens);     
  
}


int main()
{
    Init();
 
    Renderer::BeginFrame();
    int i = 0;

    float frameTime = 0;
    float deltaTime = 0;
    float prevTime = glfwGetTime();

    while(Renderer::GetWindow().IsRunning())
    {
        Renderer::GetWindow().PollEvents();
        if(frameTime > 1/120.0f)                /* limiting fps to 120 for now */
        {
            PollUserInput();
            frameTime = 0;
        }

        deltaTime = (glfwGetTime() - prevTime);
		prevTime = glfwGetTime();
		frameTime += deltaTime;
    }

    Shutdown();

    return 0;
}