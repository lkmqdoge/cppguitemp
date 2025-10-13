
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(  ${libName}
    GIT_REPOSITORY ${gitURL}
    GIT_TAG        ${gitTag}
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(${libName})
endfunction()


# ------------------------------ SDL3 -------------------------------
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.18)
else()
    message(STATUS "Using local SDL3")
endif()

# ------------------------------ glad  ------------------------------
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

target_link_libraries(imgui PRIVATE
    SDL3::SDL3
)