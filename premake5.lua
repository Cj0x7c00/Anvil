workspace "AnvilEngine"

    architecture "x64"
    startproject "Forge" -- editor
    

    configurations 
    {
        "Debug",
        "Release"
    }

    VULKAN_SDK = os.getenv("VULKAN_SDK")
    print("Vulkan SDK: ", VULKAN_SDK)
    outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    root_dir = os.getcwd() .. "/"
    print("Root Directory: ", root_dir)
    vendor_dir = root_dir .. "Anvil/include/"
    print("Vendor Directory: ", vendor_dir)

    group "Dependencies"
        include "Anvil/include/glfw/glfw.lua"
    group ""

    group "Engine"
        include "Anvil.lua"
    group ""

    group "Tools"
        include "Forge.lua"
    group ""