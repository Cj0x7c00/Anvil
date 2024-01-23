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
            "ANV_BUILD_SHARED",
            "VULKAN_SDK=\"%{VULKAN_SDK}\""
        }

        files
        {
            "Anvil/core/src/**.cpp",
            "Anvil/core/src/**.hpp",
            "Anvil/core/src/**.h"
        }

        includedirs
        {
            "Anvil/include",
            "Anvil/core/src",
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

        if os.target() == "windows" then
            postbuildcommands
            {
                '{COPYFILE} "%{wks.location}/bin/'.. outdir ..'/Anvil/Anvil.dll" "%{wks.location}/bin/'.. outdir ..'/Forge"'
            }   
        end


        filter "configurations:Debug"
            defines "DEBUG"
            optimize "on"

        filter "configurations:Release"
            defines "RELEASE"
            optimize "on"