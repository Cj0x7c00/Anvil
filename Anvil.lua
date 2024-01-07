project "Anvil"
        location "Anvil"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        warnings "off"

        targetdir("bin/" .. outdir .. "/%{prj.name}")
        objdir( "bin-int/" .. outdir .. "/%{prj.name}")

        defines
        {
            "ANV_BUILD_SHARED"
        }

        files
        {
            "Anvil/core/src/**.cpp",
            "Anvil/core/src/**.hpp"
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
            "include/glfw/".. outdir .."/GLFW"
        }


        
        links
        {
            "GLFW",
            "vulkan-1"
        }


        filter "configurations:Debug"
            defines "DEBUG"
            optimize "on"

        filter "configurations:Release"
            defines "RELEASE"
            optimize "on"