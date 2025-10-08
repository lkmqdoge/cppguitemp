
file(GLOB qrlx_SRC
    "src/*.cxx"
)

add_library(qrlx
    ${qrlx_SRC}
)

target_include_directories(qrlx 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(qrlx
    PRIVATE SDL3::SDL3
    PRIVATE SDL3_image::SDL3_image
    PRIVATE imgui
    PRIVATE OpenGL::GL
    PRIVATE glad
)