solution "MassiveEnet"
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	configuration { "Debug" }
		targetdir "../bin/debug"

	configuration { "Release" }
		targetdir "../bin/release"

	configuration { "Release" }
		targetdir "../bin/release"

	configuration { "Release" }
		targetdir "../bin/release"		


project "myEnetTest"
	kind "ConsoleApp"
	language "C++"
	--location "."
	includedirs{
		"../include"
	}
	libdirs{
		"../vendor/lib/**"
	}
	files {"../*.cpp"}
	links {"enet"}
	flags {"ExtraWarnings", "FatalWarnings"}
	if os.is("macosx") then
		libdirs{ "../vendor/lib/**","/usr/local/lib/" }
	end
		configuration{"x32"}
			links {"enet"}
		configuration{"vs*","x64"}
			links{ "enet64", "ws2_32", "winmm" }
		configuration{"gmake"}
			buildoptions{ "-std=c++11" }
	    configuration { "Debug"}
	       	defines { "DEBUG" }
	        flags { "Symbols" }
	 
	    configuration { "Release" }
	        defines { "NDEBUG" }
	        flags { "Optimize" }  	