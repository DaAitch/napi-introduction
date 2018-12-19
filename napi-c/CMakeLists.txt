cmake_minimum_required(VERSION 3.11)

project (square)
file(GLOB SOURCE_FILES "src/*.c")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

include_directories(${CMAKE_JS_INC})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})