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

include "Arkitect"
include "TestGame"