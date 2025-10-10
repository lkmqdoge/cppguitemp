add_subdirectory(SDL)

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

add_library(extern INTERFACE)

target_link_libraries(extern INTERFACE
    SDL3::SDL3
    imgui
)
