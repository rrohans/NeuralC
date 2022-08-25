#include <thread>

#include "../ImGui/imgui.h"

#include "Application.h"


void Application::onRender()
{
    debugWindow();
    trainDataWindow();
    testDataWindow();
    modelWindow();
}

void Application::debugWindow() const
{
    ImGui::Begin("NeuralC Debug Window");

    ImGui::Text("Current Framerate: %.0f", io.Framerate);

    ImGui::End();
}

void Application::trainDataWindow()
{
    ImGui::Begin("Load Train Data");

    ImGui::Text("Train Data Size: %lu", trainData.size());

    if (ImGui::Button("Load Dataset"))
        fileBrowserFileOnly.Open();

    if (!trainData.empty() && ImGui::Button("Clear Dataset"))
    {
        trainData.clear();
        trainData.shrink_to_fit();
    }

    fileBrowserFileOnly.Display();

    if (fileBrowserFileOnly.HasSelected())
    {
        std::string filePath = fileBrowserFileOnly.GetSelected().string();
        fileBrowserFileOnly.ClearSelected();
        auto f = [filePath, this]()
        {
            Data::readDataset(filePath, trainData);
        };

        std::thread t(f);
        t.detach();
    }

    ImGui::End();
}

void Application::testDataWindow()
{
    ImGui::Begin("Load Test Data");

    ImGui::Text("Test Data Size: %lu", testData.size());

    if (ImGui::Button("Load Dataset"))
        fileBrowserFileOnly.Open();

    if (!testData.empty() && ImGui::Button("Clear Dataset"))
    {
        testData.clear();
        testData.shrink_to_fit();
    }

    fileBrowserFileOnly.Display();

    if (fileBrowserFileOnly.HasSelected())
    {
        std::string filePath = fileBrowserFileOnly.GetSelected().string();
        fileBrowserFileOnly.ClearSelected();
        auto f = [filePath, this]()
        {
            Data::readDataset(filePath, testData);
        };

        std::thread t(f);
        t.detach();
    }

    ImGui::End();
}

void Application::modelWindow()
{
    ImGui::Begin("Model View");

    if (load)
        loadModelWindow();
    else
        createModelWindow();


    if (nn.isLoadedFromFile)
    {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Number of Nodes in Input Layer: %d", nn.inputLayer);
        ImGui::Text("Number of Nodes in Hidden Layer: %d", nn.hiddenLayer);
        ImGui::Text("Number of Nodes in Output Layer: %d", nn.outputLayer);
        ImGui::Text("Learning Rate: %.2f", nn.learningRate);
    }

    ImGui::End();
}

void Application::loadModelWindow()
{
    if (ImGui::Button("Switch View"))
        load = !load;

    if (ImGui::Button("Load Model"))
        fileBrowserDirOnly.Open();


    fileBrowserDirOnly.Display();

    if (fileBrowserDirOnly.HasSelected())
    {
        nn.load(fileBrowserDirOnly.GetSelected().string());
        fileBrowserDirOnly.ClearSelected();
    }

}

void Application::createModelWindow()
{
    if (ImGui::Button("Switch View"))
        load = !load;
}

Application::Application()
{
    fileBrowserDirOnly = ImGui::FileBrowser(ImGuiFileBrowserFlags_SelectDirectory);
}
