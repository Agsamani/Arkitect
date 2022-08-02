project "Arkitect"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rktpch.h"
    pchsource "src/rktpch.cpp"

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    includedirs
	{
		"src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"imgui"
	}

    filter "system:windows"
		systemversion "latest"

        filter "configurations:Debug"
		defines "RKT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RKT_RELEASE"
		runtime "Release"
		optimize "on"

    filter ""