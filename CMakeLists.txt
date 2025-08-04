cmake_minimum_required(VERSION 3.10)
project(ProjectTheia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent for external libraries
include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        v1.90.1
)
FetchContent_MakeAvailable(imgui)

# Add source files
add_executable(theia src/main.cpp src/Initialization.cpp src/Gravity.cpp src/Integrator.cpp src/Renderer.cpp)

# Link libraries
target_link_libraries(theia PRIVATE glfw glm imgui)

# ImGui specific setup (assuming OpenGL3 backend)
target_include_directories(theia PRIVATE ${imgui_SOURCE_DIR})
target_compile_definitions(theia PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# Add ImGui sources (example, adjust as needed)
target_sources(theia PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
