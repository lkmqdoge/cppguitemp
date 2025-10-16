cmake_minimum_required(VERSION 3.17)
project(glplayground)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty)
find_package(OpenGL REQUIRED)

find_package(SDL3 QUIET)


set(CPPLOT_NAME cpplot)

# ------------------------- qrlx
add_subdirectory(lib)


# ------------------------- cpplot 
file(GLOB cpplot_SRC "src/cpplot/*.cxx")
add_executable(${CPPLOT_NAME}
    WIN32
    src/cpplot.cxx
    ${cpplot_SRC}
)

target_compile_definitions(${CPPLOT_NAME}
    PRIVATE SDL_MAIN_USE_CALLBACKS)

target_link_libraries(${CPPLOT_NAME}
    PRIVATE SDL3::SDL3
            OpenGL::GL
            glad
            imgui
            qrlx
)

# warnings on
target_compile_options(${CPPLOT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_include_directories(${CPPLOT_NAME}  
    PRIVATE ${SDL3_INCLUDE_DIRS}
            ./src/cpplot/
)

# adding dll in exe folder on windows
if (WIN32)
    add_custom_command(
            TARGET ${CPPLOT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:${CPPLOT_NAME}>"
            VERBATIM
    )
    add_custom_command(
            TARGET ${CPPLOT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:glad>" "$<TARGET_FILE_DIR:${CPPLOT_NAME}>"
            VERBATIM
    )
endif()
