workspace "Anvil-2D"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release"
    }

    outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    VULKAN_SDK = os.getenv("VULKAN_SDK")

    project "Anvil"
        location "Anvil"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        targetdir("build/bin/" .. outdir .. "/%{prj.name}")
        objdir( "build/bin-int/" .. outdir .. "/%{prj.name}")

        files
        {

            "Anvil/core/src/**.hpp",
            "Anvil/core/src/**.cpp"

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
            "%{VULKAN_SDK}/Lib"
        }

        if os.target() == "windows" then
            links
            {
                "glfw3",   -- just glfw for mac
                "vulkan-1" -- just vulkan for mac
            }
        end
        
        if os.target() == "macosx" then
            links
            {
                "glfw",   -- just glfw for mac
                "vulkan" -- just vulkan for mac
            }
        end

    filter "configurations:Debug"
        defines "DEBUG"
        optimize "on"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "on"