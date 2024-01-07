workspace "AnvilEngine"

    architecture "x64"
    startproject "Forge" -- editor

    configurations 
    {
        "Debug",
        "Release"
    }

    outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    root_dir = "Anvil"

    VULKAN_SDK = os.getenv("VULKAN_SDK")



    group "Dependencies"
        include "Anvil/include/glfw/glfw.lua"
    group ""

    group "Engine"
        include "Anvil.lua"
    group ""

    group "Tools"
        include "Forge.lua"
    group ""