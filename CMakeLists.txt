cmake_minimum_required(VERSION 2.8) 
project(lua-c-api-tutorials)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_C_FLAGS  "-O2 -pipe -fPIC -Wall -fmessage-length=0")

include_directories(/usr/local/include)
include_directories(/usr/local/openresty/luajit/include/luajit-2.1)

link_libraries(m lua-5.1 dl)

install(DIRECTORY src/ DESTINATION bin FILES_MATCHING PATTERN "*.lua")

add_subdirectory(src)