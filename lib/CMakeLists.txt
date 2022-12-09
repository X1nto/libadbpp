cmake_minimum_required (VERSION 3.8)

project("ADBPP")

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} 
    PRIVATE 
        "src/adb/connection.cpp" 
        "src/adb/protocol/protocol.cpp"
        "src/adb/protocol/serialization.cpp" 
        "src/adb/protocol/util.cpp"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

