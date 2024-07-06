workspace("Renderer")
location("Generated")
language("C++")
architecture("x86_64")
configurations({ "Debug", "Release" })

filter({ "configurations:Debug" })
symbols("On")
filter({ "configurations:Release" })
optimize("On")
filter({})

targetdir("Build/Bin/%{prj.name}/%{cfg.longname}")
objdir("Build/Obj/%{prj.name}/%{cfg.longname}")

function includeGLFW()
	includedirs("Libraries/GLFW/include")
end

function linkGLFW()
	libdirs("Libraries/GLFW/lib-vc2022")

	-- Our static lib should not link against GLFW
	filter("kind:not StaticLib")
	links("glfw3")
	filter({})
end

function includeGLAD()
	includedirs("Libraries/GLAD/include")
end

function linkGLAD()
	libdirs("Libraries/GLAD/src")

	filter("kind: not StaticLib")
	links("glfw3")
	filter({})
end

function useStbImage()
  includedirs "Projects/stbImage"
end

-- Our first project, the static library
project("ExampleLib")
  kind("StaticLib")
  files("Projects/ExampleLib/**")

  includeGLFW()

function useExampleLib()
	includedirs("Projects/ExampleLib")
	links("ExampleLib")

	linkGLFW()
end

project("GLAD")
kind("StaticLib")
files("Libraries/GLAD/**")

includeGLAD()
linkGLAD()

function useGLAD()
	includedirs("Libraries/GLAD")
	links("GLAD")
	includeGLAD()
	linkGLAD()
end

-- The windowed app
project("App")
kind("ConsoleApp")
files("Projects/App/**")

includedirs("Projects/ExampleLib")

useExampleLib()

filter({ "system:windows" })
links({ "OpenGL32" })

filter({ "system:not windows" })
links({ "GL" })

function includeLinmath()
	includedirs("Libraries/Linmath/Include")
end

project("Renderer")
kind("ConsoleApp")
files("Projects/Renderer/**")

includedirs({ "Projects/Renderer", "Libraries/GLAD" })
useGLAD()

useStbImage()

includeLinmath()

includeGLFW()
linkGLFW()

filter("system:windows")
links("OpenGL32")

filter("system: not windows")
links("GL")

function includeCatch()
	includedirs("Libraries/Catch/Include")
	defines("CATCH_CPP11_OR_GREATER")
end

project("UnitTests")
kind("ConsoleApp")

files("Projects/UnitTests/**")

includeCatch()
useExampleLib()
