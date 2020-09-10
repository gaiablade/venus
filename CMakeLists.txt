cmake_minimum_required(VERSION 3.17)
project(venus)

set(CMAKE_CXX_STANDARD 20)

include_directories(Graphics)

add_library(venus
        Graphics/Camera.cpp
        Graphics/Camera.hpp
        Graphics/Circle.cpp
        Graphics/Circle.hpp
        Graphics/Cube.cpp
        Graphics/Cube.hpp
        Graphics/gen_purpose_testing.cpp
        Graphics/GLCall.cpp
        Graphics/GLCall.hpp
        Graphics/IBuffer.cpp
        Graphics/IBuffer.hpp
        Graphics/mat4.cpp
        Graphics/mat4.hpp
        Graphics/Mesh.cpp
        Graphics/Mesh.hpp
        Graphics/Model.cpp
        Graphics/Model.hpp
        Graphics/NoCamera.cpp
        Graphics/NoCamera.hpp
        Graphics/Orthographic3dCamera.cpp
        Graphics/Orthographic3dCamera.hpp
        Graphics/OrthographicCamera.cpp
        Graphics/OrthographicCamera.hpp
        Graphics/Perspective3dCamera.cpp
        Graphics/Perspective3dCamera.hpp
        Graphics/Rect.cpp
        Graphics/Rect.hpp
        Graphics/Renderer.cpp
        Graphics/Renderer.hpp
        Graphics/sample_texture.hpp
        Graphics/Shader.cpp
        Graphics/Shader.hpp
        Graphics/simpleflips.hpp
        Graphics/Sprite.cpp
        Graphics/Sprite.hpp
        Graphics/Tex2d.cpp
        Graphics/Tex2d.hpp
        Graphics/VArray.cpp
        Graphics/VArray.hpp
        Graphics/VAttributes.cpp
        Graphics/VAttributes.hpp
        Graphics/VBuffer.cpp
        Graphics/VBuffer.hpp
        Graphics/vec2.cpp
        Graphics/vec2.hpp
        Graphics/vec3.hpp
        Graphics/vec4.hpp
        Graphics/Window.cpp
        Graphics/Window.hpp Graphics.hpp
        vendor/stb_image/stb_image.cpp
        vendor/stb_image/stb_image.h Graphics/Keycodes.hpp Game/Collider.cpp Game/Collider.hpp Graphics/mat2.cpp Graphics/mat2.hpp System/Functions.hpp Game.hpp System.hpp Graphics/ColorRect.cpp Graphics/ColorRect.hpp)
