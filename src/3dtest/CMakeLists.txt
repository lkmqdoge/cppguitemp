set(EXNAME 3dtest)

file(GLOB EXSRC "*.cpp")

add_executable(${EXNAME}
    WIN32
    ${EXSRC}
)

target_link_libraries(${EXNAME}
    PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glad
        imgui
        qrlx
        glm
)

target_compile_options(${EXNAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
#   $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_include_directories(${EXNAME}
    PRIVATE ${SDL3_INCLUDE_DIRS}
            .
)

add_custom_command(
    TARGET  ${EXNAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${EXNAME}>/resources)

# adding dll in exe folder on windows
if (WIN32)

add_custom_command(
        TARGET ${EXNAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:${EXNAME}>"
        VERBATIM)
add_custom_command(
        TARGET ${EXNAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:glad>" "$<TARGET_FILE_DIR:${EXNAME}>"
        VERBATIM)

endif()
