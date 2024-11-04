set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE "LibFoo")
target_link_libraries(${EXECUTABLE_NAME} PRIVATE "LibBar")
target_link_libraries(${EXECUTABLE_NAME} PRIVATE "render")
target_link_libraries(${EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE cxxopts::cxxopts)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE imgui::imgui)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE implot::implot)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${EXECUTABLE_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${EXECUTABLE_NAME}
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${EXECUTABLE_NAME})
endif()
