project "Forge"
        location "Forge"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        warnings "off"

        targetdir("bin/" .. outdir .. "/%{prj.name}")
        objdir( "bin-int/" .. outdir .. "/%{prj.name}")

        files
        {
            "Forge/src/**.h",
            "Forge/src/**.cpp"
        }

        includedirs
        {
            "Anvil/",
            "Anvil/include/glm",
            "Anvil/include/entt/single_include"
        }

        libdirs 
        {
            root_dir .. "/build/bin/".. outdir .."/Anvil" -- Anvil.lib path
        }


        links
        {
            "Anvil"
        }

        if os.target() == "windows" then
            postbuildcommands
            {
                '{COPYFILE} "%{wks.location}bin/'.. outdir ..'/Anvil/Anvil.dll" "%{wks.location}bin/'.. outdir ..'/Forge"'
            }   
        end

        filter "configurations:Debug"
            defines "DEBUG"
            optimize "on"
            linkoptions { "/SUBSYSTEM:CONSOLE" }
            kind "ConsoleApp"

        filter "configurations:Release"
            defines "RELEASE"
            optimize "on"
            linkoptions { "/SUBSYSTEM:WINDOWS" }
            kind "WindowedApp"