workspace "Anvil-2D"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release"
    }

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Anvil"
    location "Anvil"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("build/bin/" .. outdir .. "/%{prj.name}")
    objdir( "build/bin-int/" .. outdir .. "/%{prj.name}")

    files
    {

        "./Anvil/core/src/**.hpp",
        "./Anvil/core/src/**.cpp"

    }

    includedirs
    {
        "./Anvil/core/include/",
        "./Anvil/core/include/glfw/include"
    }

    links
    {
        "glfw",
        "vulkan"
    }

filter "configurations:Debug"
    defines "DEBUG"
    optimize "on"

filter "configurations:Release"
    defines "RELEASE"
    optimize "on"