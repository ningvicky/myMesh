CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_C_COMPILER "/opt/local/bin/gcc")  
SET(CMAKE_CXX_COMPILER "/opt/local/bin/g++")
project(mesh)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

FIND_PACKAGE (OpenGL REQUIRED)
FIND_PACKAGE (GLFW REQUIRED)

#Debug mode
#ADD_DEFINITIONS(-g )

#Release Mode
ADD_DEFINITIONS(-s -O3 )

include_directories(${GLFW_INCLUDE_DIRS})

#create the executable
SET(EXEC mesh.x)
ADD_EXECUTABLE(${EXEC} main.cpp shader_utils.cpp cube.cpp mesh.cpp)

TARGET_LINK_LIBRARIES (${EXEC}
   ${OPENGL_gl_LIBRARY}
   ${OPENGL_glu_LIBRARY}
   ${GLFW_LIBRARIES}

)
