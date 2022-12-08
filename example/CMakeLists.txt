cmake_minimum_required (VERSION 3.8)

project("ADBPPExample")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} example.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE
        example.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ADBPP)
