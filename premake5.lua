workspace "Rum"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    toolset "clang"

project "example"
    kind "ConsoleApp"
    language "C"
    location "build/scripts"
    objdir "build/obj/"
    targetdir "build/bin/"
    files {
        "example/main.c"
    }
    includedirs {
        "include",
        "src",
        "src/backends",
        "src/backends/glad",
        "src/backends/GLFW",
        "src/backends/KHR",
    }
    links {
        "rum",
        "X11",
        "m"
    }

project "rum"
    kind "StaticLib"
    objdir "build/obj/"
    targetdir "build/bin/"
    language "C"
    location "build/scripts"

    files {
        "src/rum.c",

        "src/backends/glad.c",
		"src/backends/GLFW/glfw3.h",
		"src/backends/GLFW/glfw3native.h",
        "src/backends/internal.h",
		"src/backends/platform.h",
		"src/backends/mappings.h",
		"src/backends/context.c",
		"src/backends/init.c",
		"src/backends/input.c",
		"src/backends/monitor.c",
		"src/backends/platform.c",
		"src/backends/vulkan.c",
		"src/backends/window.c",
		"src/backends/egl_context.c",
		"src/backends/osmesa_context.c",
		"src/backends/null_platform.h",
		"src/backends/null_joystick.h",
		"src/backends/null_joystick.c",
        "src/backends/null_init.c",
		"src/backends/null_monitor.c",
		"src/backends/null_window.c",
    }

    includedirs {
        "include",
        "src",
        "src/backends",
        "src/backends/glad",
        "src/backends/GLFW",
        "src/backends/KHR",
    }

    filter "system:windows"
        files {
			"src/backends/win32_init.c",
			"src/backends/win32_joystick.c",
			"src/backends/win32_module.c",
			"src/backends/win32_monitor.c",
			"src/backends/win32_time.c",
			"src/backends/win32_thread.c",
			"src/backends/win32_window.c",
			"src/backends/wgl_context.c",
			"src/backends/egl_context.c",
			"src/backends/osmesa_context.c"
        }

        defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        links {
			"Dwmapi"
		}

    filter "system:linux"
        files {
			"src/backends/x11_init.c",
			"src/backends/x11_monitor.c",
			"src/backends/x11_window.c",
			"src/backends/xkb_unicode.c",
			"src/backends/posix_time.c",
			"src/backends/posix_thread.c",
			"src/backends/posix_module.c",
			"src/backends/posix_poll.c",
			"src/backends/glx_context.c",
			"src/backends/egl_context.c",
			"src/backends/osmesa_context.c",
			"src/backends/linux_joystick.c"
        }
        defines {
            "_GLFW_X11"
        }
        links {
            "X11",
            "m"
        }