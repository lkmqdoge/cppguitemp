# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
# cmake --build build 

cmake_minimum_required(VERSION 3.16)
project(BulletHellGame VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Adding Raylib
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(  ${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add SDL3 support
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.18)
else()
    message(STATUS "Using local SDL3")
endif()

# add SDL_Image
find_package(SDL3_Image QUIET)
if (NOT SDL3_Image_FOUND)
    message(STATUS "Getting SDL_Image from Github")
    include_dependency(SDL_Image https://github.com/libsdl-org/SDL_image.git release-3.2.4)
else()
    message(STATUS "Using local SDL_Image")
endif()

add_executable(${PROJECT_NAME}
    WIN32
    src/main.cpp
)


target_include_directories(${PROJECT_NAME}  PUBLIC ${SDL3_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME}  PRIVATE SDL_MAIN_USE_CALLBACKS)

# link all libraries to the project
target_link_libraries(${PROJECT_NAME} 
    PRIVATE SDL3::SDL3
    PRIVATE SDL3_image::SDL3_image SDL3::SDL3
)

# i dont even fucking know what this does
if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:BulletHellGame>"
            VERBATIM
    )
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3_image::SDL3_image>" "$<TARGET_FILE_DIR:BulletHellGame>"
            VERBATIM
    )
endif()
