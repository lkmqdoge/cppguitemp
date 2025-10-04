cmake_minimum_required(VERSION 3.16)
project(cppguitemp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(  ${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# ------------------------------ SLD3 ---------------------------
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.18)
else()
    message(STATUS "Using local SDL3")
endif()

# ------------------------------ SLD3_Image---------------------------
find_package(SDL3_Image QUIET)
if (NOT SDL3_Image_FOUND)
    message(STATUS "Getting SDL_Image from Github")
    include_dependency(SDL_Image https://github.com/libsdl-org/SDL_image.git release-3.2.4)
else()
    message(STATUS "Using local SDL_Image")
endif()

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

# pkg_check_modules(EGL REQUIRED egl)
# pkg_check_modules(GL REQUIRED gl)

add_subdirectory(glad)

# ------------------------------ ImgGui ---------------------------
add_library(imgui
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_sdl3.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_sdlgpu3.cpp
)

target_include_directories(imgui PUBLIC
    imgui
    imgui/backends
    ${SDL3_INCLUDE_DIRS}
)
target_link_libraries(imgui
    PRIVATE SDL3::SDL3
)

add_executable(${PROJECT_NAME}
    WIN32
    src/main.cpp
)


target_include_directories(${PROJECT_NAME}  
    PUBLIC  ${SDL3_INCLUDE_DIRS}
#    PRIVATE ${EGL_INCLUDE_DIRS}
    # PRIVATE ${GL_INCLUDE_DIRS}
)


target_compile_definitions(${PROJECT_NAME}  PRIVATE SDL_MAIN_USE_CALLBACKS)

# link all libraries to the project
target_link_libraries(${PROJECT_NAME}
    PRIVATE SDL3::SDL3
    PRIVATE SDL3_image::SDL3_image
    PRIVATE imgui
    PRIVATE OpenGL::GL
    PRIVATE glad
    # PRIVATE ${EGL_LIBRARIES}
    # PRIVATE ${GL_LIBRARIES}
)

add_executable(EXAMPLE
    WIN32
    src/imguiexample.cpp
)

target_include_directories(EXAMPLE  
    PUBLIC  ${SDL3_INCLUDE_DIRS}
    #    PRIVATE ${EGL_INCLUDE_DIRS}
    	 PRIVATE ${GL_INCLUDE_DIRS}
)
target_link_libraries(EXAMPLE
    PRIVATE SDL3::SDL3
    PRIVATE SDL3_image::SDL3_image
    PRIVATE imgui
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
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3_image::SDL3_image>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:glad>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM
    )
endif()
