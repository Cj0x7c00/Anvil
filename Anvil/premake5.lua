
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
            "include",
            "include/glm",
            "include/glfw/include",
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