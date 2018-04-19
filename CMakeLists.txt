project (fractalvr)
cmake_minimum_required (VERSION 2.6)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (OPENVR_INCLUDE_DIR ${OPENVR_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/openvr/headers")

add_subdirectory (src)
