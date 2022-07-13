project "TestGame"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
	{
		"%{wks.location}/Arkitect/src"
	}

    links
	{
		"Arkitect"
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