#pragma once

#include <vector>

#include "imguifilebrowser.h"

#include "../Data/Data.h"

class Application
{
public:

    Application();

    void onRender();

private:
    // Application and UI State
    ImGuiIO &io = ImGui::GetIO();

    ImGui::FileBrowser fd;

    std::vector<Data> testData;
    std::vector<Data> trainData;

    // Window Functions
    void debugWindow() const;
    void trainDataWindow();
    void testDataWindow();
};