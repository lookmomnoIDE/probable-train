cmake_minimum_required(VERSION 3.5)
project("assignment5")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)


add_executable(${PROJECT_NAME}
	src/main.cpp
    )

target_include_directories(${PROJECT_NAME} PRIVATE include)


# Link static C/C++ runtime and Windows libraries
if(WIN32)

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

    target_link_libraries(${PROJECT_NAME} 
    	winmm
    	gdi32
    	dwmapi
        imm32
    )
endif()