workspace "Anim2"
	architecture "x64"
	startproject "Anim2"
	
	configurations {
		"Release", "Debug"
	}
	
	filter "configurations:Debug"
	runtime "Debug"
	symbols "On"
	flags {"LinkTimeOptimization"}	

    
	filter "configurations:Release"
    runtime "Release"
    optimize "Speed"
    flags {"LinkTimeOptimization", "MultiProcessorCompile"}	

	
outputdir = "%{prj.name}/Bin"
	
project "Anim2"
	location "Anim2"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
    includedirs {

		"%{prj.name}/Src",
		"%{prj.name}/Include",
		"%{prj.name}/",

		"%{prj.name}/Vendor/glm",
		"%{prj.name}/Vendor/imgui",
        "%{prj.name}/Vendor/glad/include/",
		"%{prj.name}/Vendor/glfw/include/"
    }
	
	targetdir ("./Bin/")
	objdir ("./Bin/Int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "%{prj.name}/Include/pch.h"
	pchsource "%{prj.name}/Include/pch.cpp"
    
	files {
        "%{prj.name}/Src/**.h",
        "%{prj.name}/Src/**.hpp",
        "%{prj.name}/Src/**.cpp",
		"%{prj.name}/Include/**.h",

		"%{prj.name}/Vendor/imgui/*.h",
		"%{prj.name}/Vendor/imgui/*.cpp"
	}
	
	defines {}
	
	links { "GLAD", "GLFW" }

	defines {
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}

	filter "system:linux"
		links {
			"GLFW",
			"GLAD",
			"X11",
			"dl",
			"pthread"
		}

		defines {"_X11", "JUNO_PLATFORM_LINUX"}

	filter "system:windows"
		defines { "ANIM_UNSUPPORTED_PLATFORM" }

include "Anim2/Vendor/glfw/glfw.lua"
include "Anim2/Vendor/glad/glad.lua"