workspace "Anim"
	architecture "x64"
	startproject "Anim"
	
	configurations {
		"Debug",
		"Release"
	}

	flags {
		"MultiProcessorCompile"
	}
	
	outputdir = "%{cfg.buildcfg}"
	
IncludePaths = {}
IncludePaths["glfw"]   = "Anim/Vendor/glfw"
IncludePaths["glad"]   = "Anim/Vendor/glad"
IncludePaths["glm"]    = "Anim/Vendor/glm"
	
project "Anim"
	location "Anim"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
    includedirs {

        "%{prj.name}/Src",
        "%{prj.name}/Include",
		"%{prj.name}/",
		"%{prj.name}/Vendor/jpl",

		"%{prj.name}/Vendor/glm",
		"%{prj.name}/Vendor/imgui",
        "%{prj.name}/Vendor/glad/include/",
		"%{prj.name}/Vendor/glfw/include/"
    }
	
	targetdir ("./Bin/%{cfg.buildcfg}/")
	objdir ("./Bin/Int/" .. outputdir .. "/anim2")
	
	pchheader "%{prj.name}/Src/pch.h"
	pchsource "%{prj.name}/Src/pch.cpp"

	files {
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.hpp",
        "%{prj.name}/Src/**.cpp",
        "%{prj.name}/Include/*.cpp",
        "%{prj.name}/Include/*.h",

		"%{prj.name}/Vendor/imgui/*.h",
		"%{prj.name}/Vendor/imgui/*.cpp"
	}
	
	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}
	
	defines {
		
	}

	filter "system:linux"
		links {
			"GLFW",
			"GLAD",
			"X11",
			"dl",
			"pthread"
		}

		defines {"_X11", "ANIM_PLATFORM_LINUX"}

	filter "system:windows"
		defines {"_WINDOWS", "ANIM_UNSUPPORTED_PLATFORM"}

	filter "configurations:Debug"
		defines { "LOG_BUILD_DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"
		flags {"LinkTimeOptimization"}	


include "Anim/Vendor/glfw/glfw.lua"
include "Anim/Vendor/glad/glad.lua"