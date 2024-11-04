set(EXE_SOURCES "main.cpp" "cycle.cpp")
set(EXE_HEADERS "cycle.hpp")

add_executable("main" ${EXE_SOURCES} ${EXE_HEADERS})
#set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
#add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries("main" PRIVATE "LibFoo")
target_link_libraries("main" PRIVATE "LibBar")
target_link_libraries("main" PRIVATE "render")
target_link_libraries("main" PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries("main" PRIVATE fmt::fmt)
target_link_libraries("main" PRIVATE spdlog::spdlog)
target_link_libraries("main" PRIVATE cxxopts::cxxopts)

target_link_libraries("main" PRIVATE glfw)
target_link_libraries("main" PRIVATE OpenGL::GL)
target_link_libraries("main" PRIVATE imgui::imgui)
target_link_libraries("main" PRIVATE implot::implot)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        #${EXECUTABLE_NAME}
        "main"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        #${EXECUTABLE_NAME}
        "main"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("main")#${EXECUTABLE_NAME})
endif()
