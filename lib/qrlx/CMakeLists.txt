
file(GLOB qrlx_SRC "src/*.cpp")

add_library(qrlx
    ${qrlx_SRC}
)

target_include_directories(qrlx
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(qrlx
    PRIVATE SDL3::SDL3
            imgui
            OpenGL::GL
            glad
            glm
)
