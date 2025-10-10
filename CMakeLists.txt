cmake_minimum_required(VERSION 3.16)
project(cppguitemp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# pkg_check_modules(EGL REQUIRED egl)

add_subdirectory(glad)
add_subdirectory(thirdparty)


add_executable(${PROJECT_NAME}
    WIN32
    src/cppPlot.cpp
)

target_compile_definitions(${PROJECT_NAME}  PRIVATE SDL_MAIN_USE_CALLBACKS)

target_include_directories(${PROJECT_NAME}  
    PUBLIC  ${SDL3_INCLUDE_DIRS}
            # ${EGL_INCLUDE_DIRS}
)

# link all libraries to the project
target_link_libraries(${PROJECT_NAME}
    PRIVATE OpenGL::GL
    PRIVATE glad
    PRIVATE extern
    # PRIVATE ${EGL_LIBRARIES}
)

add_executable(EXAMPLE
    WIN32
    src/imguiexample.cpp
)

target_include_directories(EXAMPLE  
    PUBLIC  ${SDL3_INCLUDE_DIRS}
            ${EGL_INCLUDE_DIRS}
)
target_link_libraries(EXAMPLE PRIVATE
    extern
)


# adding dll in exe folder on windows
if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:glad>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
endif()
