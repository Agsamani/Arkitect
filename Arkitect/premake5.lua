project "Arkitect"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ktpch.h"
    pchsource "src/ktpch.cpp"

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
	{
		"src"
	}

    filter "system:windows"
		systemversion "latest"

        filter "configurations:Debug"
		defines "KT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KT_RELEASE"
		runtime "Release"
		optimize "on"

    filter ""