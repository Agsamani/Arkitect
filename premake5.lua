include "Dependencies.lua"

workspace "Arkitect"
    architecture "x64"
    startproject "TestGame"

    configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Arkitect/vendor/GLFW"
group ""

include "Arkitect"
include "TestGame"