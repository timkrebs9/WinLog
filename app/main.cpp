#include <filesystem>
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "config.hpp"
#include "cycle.hpp"
#include "foo.h"
#include "render.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>


using json = nlohmann::json;
//namespace fs = std::filesystem;

static void glfw_error_callback(int error, const char *description);

int main(int argc, char **argv)
{
    //std::cout << "JSON: " << NLOHMANN_JSON_VERSION_MAJOR << "."
    //          << NLOHMANN_JSON_VERSION_MINOR << "."
    //          << NLOHMANN_JSON_VERSION_PATCH << '\n';
    //std::cout << "FMT: " << FMT_VERSION << '\n';
    //std::cout << "CXXOPTS: " << CXXOPTS__VERSION_MAJOR << "."
    //          << CXXOPTS__VERSION_MINOR << "." << CXXOPTS__VERSION_PATCH
    //          << '\n';
    //std::cout << "SPDLOG: " << SPDLOG_VER_MAJOR << "." << SPDLOG_VER_MINOR
    //          << "." << SPDLOG_VER_PATCH << '\n';
    //std::cout << "\n\nUsage Example:\n";
    //
    //
    //
    //const auto welcome_message =
    //    fmt::format("Welcome to {} v{}\n", project_name, project_version);
    //spdlog::info(welcome_message);
    //
    //cxxopts::Options options(project_name.data(), welcome_message);
    //
    //options.add_options("arguments")("h,help", "Print usage")(
    //    "f,filename",
    //    "File name",
    //    cxxopts::value<std::string>())(
    //    "v,verbose",
    //    "Verbose output",
    //    cxxopts::value<bool>()->default_value("false"));
    //
    //auto result = options.parse(argc, argv);
    //
    //if (argc == 1 || result.count("help"))
    //{
    //    std::cout << options.help() << '\n';
    //    return 0;
    //}
    //
    //// Read files
    //auto filename = std::string{};
    //auto verbose = false;
    //
    //if (result.count("filename"))
    //{
    //    filename = result["filename"].as<std::string>();
    //}
    //else
    //{
    //    return 1;
    //}
    //
    //verbose = result["verbose"].as<bool>();
    //
    //if (verbose)
    //{
    //    fmt::print("Opening file: {}\n", filename);
    //}
    //
    //auto ifs = std::ifstream{filename};
    //
    //if (!ifs.is_open())
    //{
    //    return 1;
    //}
    //
    //const auto parsed_data = nlohmann::json::parse(ifs);
    //
    //if (verbose)
    //{
    //    const auto name = parsed_data["name"];
    //    fmt::print("Name: {}\n", name);
    //}


    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return 1;
    }

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    // Create window with graphics context
    auto *window = glfwCreateWindow(static_cast<std::int32_t>(WINDOW_WIDTH),
                                    static_cast<std::int32_t>(WINDOW_HEIGHT),
                                    "Gui",
                                    nullptr,
                                    nullptr);
    if (window == nullptr)
    {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    auto &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(1.0, 1.0, 1.0, 1.0);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(1.0, 1.0, 1.0, 1.0);

    cycle_function(window);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
