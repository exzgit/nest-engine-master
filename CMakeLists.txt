cmake_minimum_required(VERSION 3.16)
project(NestEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binary path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ========================
# >> Include Paths
# ========================
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/glad/include
    ${PROJECT_SOURCE_DIR}/external/glm
)

# ========================
# >> Source Files
# ========================
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.hpp
    include/**/*.hpp
)

# Glad Source
set(GLAD_SRC external/glad/src/glad.c)

# ========================
# >> Add Executable
# ========================
add_executable(nest-engine ${SRC_FILES} ${GLAD_SRC})

# ========================
# >> Link Libraries
# ========================
find_package(OpenGL REQUIRED)

target_link_libraries(nest-engine PRIVATE OpenGL::GL)

# ========================
# >> Add GLFW Module
# ========================
add_subdirectory(external/glfw)
include_directories(external/glfw/include)
target_link_libraries(nest-engine PRIVATE glfw)


# ========================
# >> Tiny Obj Loader
# ========================
add_library(tinyobjloader STATIC 
    ${PROJECT_SOURCE_DIR}/include/tiny_obj_loader.cc
)

target_include_directories(tinyobjloader PUBLIC 
    ${PROJECT_SOURCE_DIR}/include/tiny_obj_loader.h
)

target_link_libraries(nest-engine PRIVATE tinyobjloader)

# ========================
# >> Definitions & Flags
# ========================
target_compile_definitions(nest-engine PRIVATE NEST_ENGINE_BUILD)
