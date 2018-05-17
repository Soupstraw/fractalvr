enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)

message(STATUS ${GLM_INCLUDE_DIRS})

find_package (GLEW REQUIRED)
find_package (SDL2 REQUIRED)
find_package (OpenVR REQUIRED)
find_package (GLM REQUIRED)
find_package (OpenGL REQUIRED)

file(GLOB FRACTALVR_SOURCES
  ${CMAKE_SOURCE_DIR}/include
  main.cpp
)
message ("${GLEW_LIBRARY}")

add_definitions (-Dstricmp=strcasecmp)
add_definitions (-Dstrnicmp=strncasecmp)

include_directories (${OPENVR_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

add_executable(fractalvr CMainApplication.cpp CGLRenderModel.cpp main.cpp Matrices.cpp)
target_include_directories (fractalvr PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries (fractalvr ${MINGW32_LIBRARY} glew32s ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${OPENVR_LIBRARIES})
set_target_properties(fractalvr PROPERTIES LINKER_LANGUAGE CXX)

install (TARGETS fractalvr DESTINATION ${CMAKE_SOURCE_DIR}/bin)
