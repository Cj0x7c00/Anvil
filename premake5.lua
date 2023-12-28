workspace "AnvilEngine"
    architecture "x64"
    startproject "Anvil"

    configurations 
    {
        "Debug",
        "Release"
    }

    outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


VULKAN_SDK = os.getenv("VULKAN_SDK")



group "Dependencies"
    include "Anvil/include/glfw"
group ""

group "Engine"
    
    project "Anvil"
        location "Anvil"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        warnings "off"

        targetdir("build/bin/" .. outdir .. "/%{prj.name}")
        objdir( "build/bin-int/" .. outdir .. "/%{prj.name}")

        files
        {
            "core/src/**.hpp",
            "core/src/**.cpp",
        }

        includedirs
        {
            "Anvil/include",
            "Anvil/include/glm",
            "Anvil/include/glfw/include",
            "%{VULKAN_SDK}/include"
        }

        libdirs 
        {
            "%{VULKAN_SDK}/Lib",
            "include/glfw/bin/".. outdir .."/GLFW/"
        }


        if os.target() == "windows" then
            links
            {
                "GLFW",   
                "vulkan-1" 
            }
        end

        if os.target() == "macosx" then
            links
            {
                "GLFW",  
                "vulkan" 
            }
        end

        filter "configurations:Debug"
        defines "DEBUG"
        optimize "on"

        filter "configurations:Release"
        defines "RELEASE"
        optimize "on"

group ""