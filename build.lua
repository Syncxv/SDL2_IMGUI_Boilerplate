
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

sdl2dll = "{COPY} \"%{wks.location}deps/SDL2/lib/x64/SDL2.dll\" \"%{cfg.targetdir}\""

workspace "SDL2 and IMGUI Boilerplate"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SDL2 and IMGUI Boilerplate"
project "SDL2 and IMGUI Boilerplate"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { 
      "src/**.h", 
      "src/**.cpp",
      "deps/imgui/*.cpp",
   }

   includedirs { "src", "deps/SDL2/include", "deps/imgui" }
   libdirs { "deps/SDL2/lib/x64" }

   links { "SDL2main", "SDL2" }

   targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
   objdir ("./bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      postbuildcommands { sdl2dll }
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      postbuildcommands { sdl2dll }
      defines { "RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      postbuildcommands { sdl2dll }
      kind "WindowedApp"
      defines { "DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"