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

    targetdir("bin/" .. outdir .. "/%{prj.name}")
    objdir( "bin-int/" .. outdir .. "/%{prj.name}")

    files
    {
        "./Anvil/core/src/anvApplication.cpp",
        "./Anvil/core/src/anvApplication.hpp",

        "./Anvil/core/src/Layer/anvLayer.cpp",
        "./Anvil/core/src/Layer/anvLayer.hpp",

        

        "./Anvil/core/src/anvpch.cpp", 
        "./Anvil/core/src/Vulkan/Model/anvModel.cpp",
        "./Anvil/core/src/Vulkan/anvDevice.cpp",
        "./Anvil/core/src/Vulkan/anvPipeline.cpp",
        "./Anvil/core/src/Vulkan/anvRenderer.cpp",
        "./Anvil/core/src/Vulkan/anvSwapChain.cpp",
        "./Anvil/core/src/Vulkan/simpleRenderSystem.cpp",
        "./Anvil/core/src/Util/Time/anvTimestep.cpp",
        "./Anvil/core/src/Window/window_manager.cpp",
        "./Anvil/core/src/sandbox.cpp",
        
        "./Anvil/core/src/Layer/anvLayerStack.cpp ",
        "./Anvil/core/src/Layer/anvLayerStack.hpp ",

        "./Anvil/core/src/sandboxApp.cpp",
        "./Anvil/core/src/**.hpp",
        "./Anvil/core/src/**.cpp"

    }

    excludes
    {
        "./Anvil/core/src/include/"
    }

    links
    {
        "glfw",
        "vulkan"
    }

filter "configurations:Debug"
    defines "DEBUG"
    optimize "on"