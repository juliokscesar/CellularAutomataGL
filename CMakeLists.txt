cmake_minimum_required(VERSION 3.28)
project(CellularAutomata)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "/Od")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif()

set(SRC_DIR src)
set(SRC_FILES 
    ext/glad/src/glad.c
    ext/griffinLogCpp/src/griffinLog/griffinLog.cpp

    ${SRC_DIR}/main.cpp
)

add_executable(autom ${SRC_FILES})

if (WIN32)
    set(GLFW_DIR ${PROJECT_SOURCE_DIR}/ext/glfw-win64)
    if (MSVC)
        set(GLFW_LIB_DIR ${GLFW_DIR}/lib-vc2022)

        target_sources(autom PUBLIC 
            ${SRC_DIR}/core/errors.h
            ${SRC_DIR}/core/logging.h
        )
    else()
        set(GLFW_LIB_DIR ${GLFW_DIR}/lib-mingw-w64)
    endif()

    target_include_directories(autom PUBLIC ${GLFW_DIR}/include)
    target_link_directories(autom PUBLIC ${GLFW_LIB_DIR})
    target_link_libraries(autom PUBLIC
        glfw3
    )
else()
    target_link_libraries(autom PUBLIC
        glfw3
        GL
        X11
        pthread
        Xrandr
        Xi
        dl
    )
endif()

target_include_directories(autom PUBLIC 
    ext/glad/include
    ext/griffinLogCpp/src
    ext
    ${SRC_DIR}
)