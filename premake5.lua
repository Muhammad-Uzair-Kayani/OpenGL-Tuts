workspace "Renderer"
    architecture "x64"
    startproject "Renderer"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Glad"
include "GLFW"
include "Renderer"