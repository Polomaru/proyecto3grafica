cmake_minimum_required(VERSION 3.16)
project(superficie)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
add_subdirectory(external)

add_executable(superficie basic_lighting_diffuse.cpp)
target_link_libraries(superficie PRIVATE OpenGL::GL OpenGL::GLU glfw glad glm::glm stb_image dl X11)