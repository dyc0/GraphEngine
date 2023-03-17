cmake_minimum_required(VERSION 3.11)

project(SDOS_GRAPH_ENGINE VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUGGING "Toggle debugging mode for symbol generation etc." ON)
option(ENABLE_TESTING "Choose whether to compile test files." ON)

if(DEBUGGING)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

if(DEBUGGING)
  target_compile_options(compiler_flags INTERFACE
    -Wall -Wextra -Wshadow -Wformat=2 -Wunused
  )
else()
  target_compile_options(compiler_flags INTERFACE
    -O3 -march=native
  )
endif()

# FIND OpenGL, GLEW, GLM and SDL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(glm_DIR /usr/lib/cmake/glm)
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_library(GraphicsEngine STATIC)

list(APPEND GRAPH_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/display.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh.cpp
     )

target_sources(GraphicsEngine PUBLIC ${GRAPH_SOURCES})
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(GraphicsEngine PUBLIC ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glm::glm ${SDL2_LIBRARIES} compiler_flags)


add_executable(example example.cpp)
target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(example PUBLIC GraphicsEngine ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glm::glm ${SDL2_LIBRARIES} compiler_flags)


# Copy resource files
add_custom_target(resources_folder ALL)
add_custom_command(TARGET resources_folder PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:example>/res)

#add_subdirectory(LIBRARY)
#list(APPEND XR_LIBS XRaySimulator)
#
#if(ENABLE_TESTING)
#  add_subdirectory(TESTS)
#endif()
#
#add_executable(solution solution.cpp)
#target_link_libraries(solution ${XR_LIBS} compiler_flags)
#
#add_executable(all_variations all_variations.cpp)
#target_link_libraries(all_variations ${XR_LIBS} compiler_flags)
#
#add_executable(photon_distribution photon_distribution.cpp)
#target_link_libraries(photon_distribution ${XR_LIBS} compiler_flags)


