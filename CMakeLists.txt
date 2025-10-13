cmake_minimum_required(VERSION 3.17)
project(cppguitemp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty)
find_package(OpenGL REQUIRED)


# ------------------------- Main app 
add_executable(${PROJECT_NAME}
    WIN32
    src/cppPlot.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE SDL_MAIN_USE_CALLBACKS)

target_link_libraries(${PROJECT_NAME}
    PRIVATE SDL3::SDL3
            OpenGL::GL
            glad
            imgui
)

target_include_directories(${PROJECT_NAME}  
    PRIVATE ${SDL3_INCLUDE_DIRS}
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
