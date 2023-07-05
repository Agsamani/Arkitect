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
		"src/**.cpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/entt/include/**.hpp",

		"vendor/json/**.hpp"
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
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.json}",
        "%{IncludeDir.Box2D}",
		"%{IncludeDir.msdfgen}",
		"%{IncludeDir.msdfatlasgen}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"imgui",
		"Box2D",
		"msdf-atlas-gen"
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