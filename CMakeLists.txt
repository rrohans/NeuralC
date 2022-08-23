cmake_minimum_required(VERSION 3.20)
project(NeuralNetwork)

set(CMAKE_OSX_ARCHITECTURES x86_64)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(NeuralNetwork
#        old_main.cpp
        Matrix/Matrix.cpp
        Matrix/MatrixOps.cpp
        Activations/Activations.cpp
        Activations/Activations.h
        Data/Data.cpp
        Data/Data.h
        NeuralNetwork/NeuralNetwork.cpp
        NeuralNetwork/NeuralNetwork.h
        Utils/ProgressBar/ProgressBar.cpp
        Utils/ProgressBar/ProgressBar.h
        Utils/ScopedTimer/ScopedTimer.cpp
        Utils/ScopedTimer/ScopedTimer.h
        ImGui/imgui_widgets.cpp
        ImGui/imgui_tables.cpp
        ImGui/imgui_impl_opengl3.cpp
        ImGui/imgui_impl_glfw.cpp
        ImGui/imgui_draw.cpp
        ImGui/imgui.cpp
        ImGui/imgui_demo.cpp
        Application/Application.cpp
        Application/imguifilebrowser.h
        main.cpp
        )

target_link_libraries(NeuralNetwork glfw "-framework OpenGL")
