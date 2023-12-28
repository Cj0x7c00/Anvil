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
    include "Anvil/"
group ""
