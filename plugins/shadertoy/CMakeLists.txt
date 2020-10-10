project( GLXTests ) 
cmake_minimum_required( VERSION 2.8.7 )
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules ${CMAKE_MODULE_PATH})

add_definitions(-DUSE_GLEW)
 
  
add_executable(gl3Tex glx_testRenderToTexture.c glx3.c shader_loader.c matrix4x4Tools.c matrixOpenGL.c)
target_link_libraries(gl3Tex rt m GL GLU GLEW X11)  
set_target_properties(gl3Tex PROPERTIES 
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
                      )


