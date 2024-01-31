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
            "Forge/src/**.hpp",
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
            "Anvil/build/bin/".. outdir .."/Anvil" -- Anvil.lib path
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

        filter "configurations:Release"
        defines "RELEASE"
        optimize "on"