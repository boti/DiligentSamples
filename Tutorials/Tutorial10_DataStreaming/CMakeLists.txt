cmake_minimum_required (VERSION 3.6)

project(Tutorial10_DataStreaming CXX)

set(SOURCE
    src/Tutorial10_DataStreaming.cpp
)

set(INCLUDE
    src/Tutorial10_DataStreaming.h
)

set(SHADERS
    assets/polygon.vsh
    assets/polygon.psh
    assets/polygon_batch.vsh
    assets/polygon_batch.psh
)

set(ASSETS
    assets/DGLogo0.png
    assets/DGLogo1.png
    assets/DGLogo2.png
    assets/DGLogo3.png
)

add_tutorial("Tutorial10_DataStreaming" "${SOURCE}" "${INCLUDE}" "${SHADERS}" "${ASSETS}")
target_link_libraries(Tutorial10_DataStreaming PRIVATE TextureLoader)
if(PLATFORM_LINUX)
    target_link_libraries(Tutorial10_DataStreaming PRIVATE pthread)
endif()