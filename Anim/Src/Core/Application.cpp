#include "pch.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Core/AssetManager.h"

using namespace Anim;

Application::Application() 
{
	frameTime = 0;
	deltaTime = 0;
	
	Log::Info("Initializing...");
}	

void Application::Init()
{
	AssetManager* assetManager = &AssetManager::Get();
	
	Camera* camera = &frame.GetCamera();
	Renderer::GetWindow().GetMouseDispatcher().AddListener(camera);
	Renderer::GetWindow().GetKeyDispatcher().AddListener(camera);
	
	gui.Init();
}


void Application::Run()
{
	deltaTime = 0;
	frameTime = 0;
	lastTime = glfwGetTime();

	while (Renderer::GetWindow().IsRunning())
	{
		ScanInput();
	}
}

void Application::RunCommand(std::vector<std::string>& inputCmd)
{
    if(inputCmd[0] == "sp") {                   /* draw a sphere */
    
		Vec3 position, color = {0,0,0};
		position.x = atof(inputCmd[1].c_str());
		position.y = atof(inputCmd[2].c_str());
		position.z = atof(inputCmd[3].c_str());

		color.x = atof(inputCmd[4].c_str());
		color.y = atof(inputCmd[5].c_str());
		color.z = atof(inputCmd[6].c_str());

		float scale = atof(inputCmd[7].c_str());

		frame.CreateSphere(position, color, scale);
	
    }  else if(inputCmd[0] == "cc") { 				 		/* set new clear color bg */
		Vec3 color;
		color.x = atof(inputCmd[1].c_str());
		color.y = atof(inputCmd[2].c_str());
		color.z = atof(inputCmd[3].c_str());

		Renderer::SetBackgroundColor(color);

	} else if(inputCmd[0] == "dt") {   			     		/* draw text */
		
		std::stringstream ss;
		for(int i = 1; i < inputCmd.size(); i++)
		{
			ss << inputCmd[i] << " ";
		}
		Log::Info("recieved text.");
		Log::Info(ss.str().c_str());
		gui.DrawUserText(ss.str());

	} else if(inputCmd[0] == "gr") {                            /* graph */
    
        std::string name = inputCmd[1];                 	   /* first arg of graph is name, then data */
        std::vector<float> data(inputCmd.size()-2);
        
        for(uint32_t i = 2; i < inputCmd.size(); i++)
        {
            data[i-2] = atof(inputCmd[i].c_str());
        }

        // Plot plot;
        // plot.name = name;
        // plot.data = data;
    	//std::cout << "Recieved command to graph stuff" << std::endl;
        // Renderer::DrawPlot(plot);

    } else if(inputCmd[0] == "ef") {                 /* end frame */
    
		Renderer::Begin();
		Renderer::Submit(frame, frameTime);
		gui.Update(frame, frameTime);
		Renderer::End();
		frame.ClearFrame();
		frameTime = 0;

		deltaTime = (glfwGetTime() - lastTime);
		lastTime = glfwGetTime();
		frameTime += deltaTime;
    }
}

/* input redirected from stdio */
void Application::ScanInput()
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


void Application::Exit()
{
	Log::Info("Exiting...");
}


int main()
{
	Application app;
	app.Init();
	app.Run(); 
	app.Exit();
	
	return 0;
}