if(PLATFORM_WIN32 OR PLATFORM_LINUX)
    cmake_minimum_required (VERSION 3.13)
else()
    cmake_minimum_required (VERSION 3.6)
endif()

function(add_tutorial TUTORIAL_NAME SOURCE INCLUDE SHADERS ASSETS)

	set_source_files_properties(${SHADERS} PROPERTIES VS_TOOL_OVERRIDE "None")
	set(ALL_ASSETS ${ASSETS} ${SHADERS})
	add_target_platform_app(${TUTORIAL_NAME} "${SOURCE}" "${INCLUDE}" "${ALL_ASSETS}")

	set_source_files_properties(${ALL_ASSETS} PROPERTIES 
		VS_DEPLOYMENT_LOCATION "."
		MACOSX_PACKAGE_LOCATION "Resources" 
	)
    
	if(PLATFORM_WIN32)
		set_target_properties(${TUTORIAL_NAME} PROPERTIES 
			VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
		)
        if(MSVC)
		    copy_required_dlls(${TUTORIAL_NAME})
        endif()
        append_sample_base_win32_source(${TUTORIAL_NAME})
	elseif(PLATFORM_UNIVERSAL_WINDOWS)
			append_sample_base_uwp_source(${TUTORIAL_NAME})
	endif()

	target_include_directories(${TUTORIAL_NAME}
	PRIVATE	
		src
	)

	target_link_libraries(${TUTORIAL_NAME}
	PRIVATE
		NativeAppBase
		BuildSettings
		SampleBase 
	)
	set_common_target_properties(${TUTORIAL_NAME})

	if(MSVC)
		# Disable MSVC-specific warnings
		# - w4201: nonstandard extension used: nameless struct/union
		target_compile_options(${TUTORIAL_NAME} PRIVATE /wd4201)
	endif()
	
	set_target_properties(${TUTORIAL_NAME} PROPERTIES
		FOLDER Tutorials
	)

	source_group("src" FILES ${SOURCE} ${INCLUDE})
	source_group("assets" FILES ${ALL_ASSETS})	
    
    target_sources(${TUTORIAL_NAME} PRIVATE readme.md)
    set_source_files_properties(
        readme.md PROPERTIES HEADER_FILE_ONLY TRUE
    )

    if(PLATFORM_WIN32 OR PLATFORM_LINUX)
        # Copy assets to target folder
        add_custom_command(TARGET ${TUTORIAL_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/assets"
                "\"$<TARGET_FILE_DIR:${TUTORIAL_NAME}>\"")
    endif()

    if(INSTALL_DILIGENT_SAMPLES)
        # Install instructions
        file(RELATIVE_PATH TUTORIAL_REL_PATH "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
        install(TARGETS     ${TUTORIAL_NAME}
                DESTINATION ${TUTORIAL_REL_PATH})
        if(PLATFORM_LINUX OR PLATFORM_WIN32)
            install(DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
                    DESTINATION ${TUTORIAL_REL_PATH})
            get_supported_backends(BACKEND_LIBRARIES)
            install(TARGETS  ${BACKEND_LIBRARIES}
                    RUNTIME DESTINATION ${TUTORIAL_REL_PATH}
                    LIBRARY DESTINATION ${TUTORIAL_REL_PATH}
                    ARCHIVE DESTINATION ${TUTORIAL_REL_PATH})
        endif()
    endif()

endfunction()

if(PLATFORM_WIN32)
    add_subdirectory(Tutorial00_HelloWin32)
elseif(PLATFORM_LINUX)
    add_subdirectory(Tutorial00_HelloLinux)
endif()
add_subdirectory(Tutorial01_HelloTriangle)
add_subdirectory(Tutorial02_Cube)
add_subdirectory(Tutorial03_Texturing)
add_subdirectory(Tutorial04_Instancing)
add_subdirectory(Tutorial05_TextureArray)
add_subdirectory(Tutorial06_Multithreading)
add_subdirectory(Tutorial07_GeometryShader)
add_subdirectory(Tutorial08_Tessellation)
add_subdirectory(Tutorial09_Quads)
add_subdirectory(Tutorial10_DataStreaming)
add_subdirectory(Tutorial11_ResourceUpdates)