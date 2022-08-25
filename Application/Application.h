#pragma once

#include <vector>

#include "imguifilebrowser.h"

#include "../Data/Data.h"
#include "../NeuralNetwork/NeuralNetwork.h"

class Application
{
public:

    Application();

    void onRender();

private:
    // Application and UI State
    ImGuiIO &io = ImGui::GetIO();

    ImGui::FileBrowser fileBrowserFileOnly;
    ImGui::FileBrowser fileBrowserDirOnly;

    std::vector<Data> testData;
    std::vector<Data> trainData;

    NeuralNetwork nn;

    bool load = true;

    // Window Functions
    void debugWindow() const;

    void trainDataWindow();

    void testDataWindow();

    void modelWindow();

    void loadModelWindow();

    void createModelWindow();
};