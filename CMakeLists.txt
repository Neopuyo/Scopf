cmake_minimum_required(VERSION 3.0.0)
project(scop VERSION 0.1.0)

# Glfw lib downloaded form glfw.org and compiled using cmake command into
set(GLFW_STATIC_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/libglfw3.a")
set(GLFW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include/")
set(INCLUDE_DEPENDENCIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/")
set(GLAD_INCLUDE_DIR_GTC "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad")
set(ERROR_HANDLING_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/tools")
set(WINDOW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Window")
set(SHADER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Shader")
set(VERTEX_ARRAY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/VertexArray")
set(VERTEX_BUFFER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/VertexBuffer")
set(FILE_LOADER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/loader")
set(CAMERA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Camera/")
set(OBJLOADER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/ObjLoader/")
set(BMPLOADER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/BMPLoader/")
set(FT_GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/ft_glm/")

# compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# compiler asked for using this define
add_definitions(-D GLM_ENABLE_EXPERIMENTAL)


add_executable(
  scop
  dependencies/glad/glad.h
  dependencies/glad/glad.c
  dependencies/tools/errorHandling.h
  dependencies/tools/errorHandling.cpp
  dependencies/loader/texture.cpp
 
  src/scop.cpp
  src/Window/Window.cpp
  src/Shader/Shader.cpp
  src/VertexArray/VertexArray.cpp
  src/VertexBuffer/VertexBuffer.cpp
  src/Camera/Camera.cpp
  src/ObjLoader/ObjLoader.cpp
  src/BMPLoader/BMPLoader.cpp
  src/ft_glm/ft_glm.cpp
)

include_directories(
  ${GLFW_INCLUDE_DIRS} 

  # TO GET GLM LIB LOCALLY (no need on NUC) # [!] wont keept this in project
  ${INCLUDE_DEPENDENCIES}
  
  ${GLAD_INCLUDE_DIR_GTC}
  ${ERROR_HANDLING_INCLUDE_DIR}
  ${WINDOW_INCLUDE_DIR}
  ${SHADER_INCLUDE_DIR}
  ${VERTEX_ARRAY_INCLUDE_DIR}
  ${VERTEX_BUFFER_INCLUDE_DIR}
  ${FILE_LOADER_INCLUDE_DIR}
  ${CAMERA_INCLUDE_DIR}
  ${OBJLOADER_INCLUDE_DIR}
  ${BMPLOADER_INCLUDE_DIR}
  ${FT_GLM_INCLUDE_DIR}
)

find_package(OpenGL REQUIRED)

target_link_libraries(
  scop
  ${OPENGL_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES} 
)