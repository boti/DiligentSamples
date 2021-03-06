cmake_minimum_required (VERSION 3.6)

project(Tutorial00_HelloWin32 CXX)

set(SOURCE
    src/Tutorial00_HelloWin32.cpp
)

add_executable(Tutorial00_HelloWin32 WIN32 ${SOURCE})
target_include_directories(Tutorial00_HelloWin32 PRIVATE "../../../DiligentCore")

target_compile_definitions(Tutorial00_HelloWin32 
PRIVATE 
    UNICODE
    D3D11_SUPPORTED=$<BOOL:${D3D11_SUPPORTED}>
    D3D12_SUPPORTED=$<BOOL:${D3D12_SUPPORTED}>
    GL_SUPPORTED=$<BOOL:${GL_SUPPORTED}>
    VULKAN_SUPPORTED=$<BOOL:${VULKAN_SUPPORTED}>
)

set_target_properties(Tutorial00_HelloWin32 PROPERTIES
    FOLDER Tutorials
)

if(MSVC)

    target_compile_definitions(Tutorial00_HelloWin32 PRIVATE ENGINE_DLL=1)

    if(D3D11_SUPPORTED)
        add_dependencies(Tutorial00_HelloWin32 GraphicsEngineD3D11-shared)
    endif()
    if(D3D12_SUPPORTED)
        add_dependencies(Tutorial00_HelloWin32 GraphicsEngineD3D12-shared)
    endif()
    if(GL_SUPPORTED)
        add_dependencies(Tutorial00_HelloWin32 GraphicsEngineOpenGL-shared)
    endif()
    if(VULKAN_SUPPORTED)
        add_dependencies(Tutorial00_HelloWin32 GraphicsEngineVk-shared)
    endif()
    copy_required_dlls(Tutorial00_HelloWin32)

else()

    target_compile_definitions(Tutorial00_HelloWin32 PRIVATE ENGINE_DLL=0)

	# MinGW - use static libraries
    if(D3D11_SUPPORTED)
        target_link_libraries(Tutorial00_HelloWin32 PRIVATE GraphicsEngineD3D11-static)
    endif()
    if(D3D12_SUPPORTED)
        target_link_libraries(Tutorial00_HelloWin32 PRIVATE GraphicsEngineD3D12-static)
    endif()
    if(GL_SUPPORTED)
        target_link_libraries(Tutorial00_HelloWin32 PRIVATE GraphicsEngineOpenGL-static)
    endif()
    if(VULKAN_SUPPORTED)
        target_link_libraries(Tutorial00_HelloWin32 PRIVATE GraphicsEngineVk-static)
    endif()

endif()
