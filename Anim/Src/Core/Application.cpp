#include "pch.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Core/AssetManager.h"

using namespace Anim;

Application::Application() : m_FrameTime(0), m_DeltaTime(0), m_ShouldClose(false)
{
	
	Log::Info("Initializing...");
}	

void Application::Init()
{
	AssetManager* assetManager = &AssetManager::Get();
	
	Camera* camera = Renderer::GetCamera();
	Renderer::GetWindow().GetMouseDispatcher().AddListener(camera);
	Renderer::GetWindow().GetKeyDispatcher().AddListener(camera);
	
	m_Gui.Init();
}

void Application::Run()
{
	m_DeltaTime = 0;
	m_FrameTime = 0;
	m_LastTime = glfwGetTime();

	do
	{
		if (std::cin.eof())
		{
			m_ShouldClose = true;
			return;
		}
		ScanInput();

		/* code */
	} while (Renderer::GetWindow().IsRunning() && !m_ShouldClose);
	
}


const char* TokensToString(std::vector<std::string>& inputCmd, uint32 startIndex)
{
	std::stringstream ss;
	for(int i = startIndex; i < inputCmd.size(); i++)
	{
		ss << inputCmd[i] << " ";
	}
	return ss.str().c_str();
}

void Application::RunCommand(std::vector<std::string>& inputCmd)
{
    if(inputCmd[0] == "sp") {                   /* draw a sphere */
    
		glm::vec3 position, color = {0,0,0};
		position.x = atof(inputCmd[1].c_str());
		position.y = atof(inputCmd[2].c_str());
		position.z = atof(inputCmd[3].c_str());

		color.x    = atof(inputCmd[4].c_str());
		color.y    = atof(inputCmd[5].c_str());
		color.z    = atof(inputCmd[6].c_str());

		float scale = atof(inputCmd[7].c_str());

		m_Frame.CreateSphere(position, color, scale);
	
    }  else if(inputCmd[0] == "cc") { 				 			/* set new clear color bg */
		glm::vec3 color;
		color.x = atof(inputCmd[1].c_str());
		color.y = atof(inputCmd[2].c_str());
		color.z = atof(inputCmd[3].c_str());

		Renderer::SetBackgroundColor(color);

	} else if(inputCmd[0] == "dt") {   			     			/* draw text */
		
		m_Gui.DrawUserText(TokensToString(inputCmd, 1));

	} else if(inputCmd[0] == "pl") {                            /* graph */
    
        std::string name = inputCmd[1];                 	    /* first arg of 'plot' command is name, followed by the data */
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

    } else if(inputCmd[0] == "lc")
	{
		RunComputeShaderProgram(inputCmd[1]);

	} else if(inputCmd[0] == "cl")
	{
		Log::Info(TokensToString(inputCmd, 1));


	}else if(inputCmd[0] == "ef") {                 /* end frame */
    
		Renderer::Begin();
		Renderer::Submit(m_Frame, m_FrameTime);

		m_Gui.Update(m_Frame, m_FrameTime);
		
		Renderer::End();
		m_Frame.ClearFrame();

		m_FrameTime = 0;
		m_DeltaTime = (glfwGetTime() - m_LastTime);
		m_LastTime = glfwGetTime();
		m_FrameTime += m_DeltaTime;
    } else if(inputCmd[0] == "!") {

		printf("%s\n", TokensToString(inputCmd, 1));
	} else if(inputCmd[0] == "ex")
	{
		m_ShouldClose = true;
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

/* Client-side design of Compute Shader portion of the API is still ongoing, so Compute Shaders are currently disabled. */
void Application::RunComputeShaderProgram(const std::string& filepath)
{
	// std::vector<Particle> particles;

	// while(true)
	// {
	// 	std::string input;
	// 	std::getline(std::cin, input);
	// 	std::stringstream stream(input);
	// 	std::string token;
	// 	std::vector<std::string> tokens;

	// 	while(std::getline(stream, token, ' '))
	// 		tokens.push_back(token);    

	// 	if(tokens[0] == "ap")
	// 	{
	// 		glm::vec3 position = { atof(tokens[0].c_str()), atof(tokens[1].c_str()), atof(tokens[2].c_str()) };
	// 		glm::vec3 velocity = { atof(tokens[3].c_str()), atof(tokens[4].c_str()), atof(tokens[5].c_str()) };
	// 		glm::vec3 color    = { atof(tokens[6].c_str()), atof(tokens[7].c_str()), atof(tokens[8].c_str()) };
	// 		float mass = atof(tokens[9].c_str());

	// 		particles.emplace_back(position, velocity, color, mass);

	// 	} else if(tokens[0] == "rc") {
	// 		break;
	// 	}
	
	// }

	// GLComputeShader computeShader(particles, filepath, 512);

	// while(true)
	// {
	// 	Renderer::Begin();
	// 	Renderer::RunComputeShader();
	// 	Renderer::End();
	// }

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