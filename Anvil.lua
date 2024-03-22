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
            "Anvil/core/src/**.h",

            -- ImGui
            "Anvil/include/imgui/*.cpp",
            "Anvil/include/imgui/*.h",
            "Anvil/include/imgui/backends/imgui_impl_glfw.cpp",
            "Anvil/include/imgui/backends/imgui_impl_glfw.h",
            "Anvil/include/imgui/backends/imgui_impl_vulkan.cpp",
            "Anvil/include/imgui/backends/imgui_impl_vulkan.h"
        }

        includedirs
        {
            "Anvil/include",
            "Anvil/core/src",
            "Anvil/include/glm",
            "Anvil/include/imgui",
            "Anvil/include/glfw/include",
            "Anvil/include/entt/single_include",
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
            "shaderc_combined",
            "vulkan-1"
        }

        postbuildcommands
        {
            '{COPYFILE} "%{wks.location}bin/'.. outdir ..'/Anvil/Anvil.dll" "%{wks.location}bin/'.. outdir ..'/Forge"'
        } 

        buildoptions { "/MP" }

        filter "configurations:Debug"
            defines "DEBUG"
            optimize "on"

        filter "configurations:Release"
            defines "RELEASE"
            optimize "on"