#include "../ImGui/imgui.h"

#include "Application.h"


void Application::onRender()
{
    debugWindow();
    trainDataWindow();
    testDataWindow();
}

void Application::debugWindow() const
{
    ImGui::Begin("NeuralC Debug Window");

    ImGui::Text("Current Framerate: %.0f", io.Framerate);

    ImGui::End();
}

void Application::trainDataWindow()
{
    ImGui::Begin("Train Data");

    ImGui::Text("Train Data Size: %lu", trainData.size());

    if (ImGui::Button("Load Test Dataset"))
        fd.Open();

    if (ImGui::Button("Clear Dataset"))
    {
        trainData.clear();
        trainData.shrink_to_fit();
    }

    fd.Display();

    if (fd.HasSelected())
    {
        Data::readDataset(fd.GetSelected().string(), trainData);
        fd.ClearSelected();
    }

    ImGui::End();
}

void Application::testDataWindow()
{
    ImGui::Begin("Test Data");

    ImGui::Text("Test Data Size: %lu", testData.size());

    if (ImGui::Button("Load Test Dataset"))
        fd.Open();

    if (ImGui::Button("Clear Dataset"))
    {
        testData.clear();
        testData.shrink_to_fit();
    }

    fd.Display();

    if (fd.HasSelected())
    {
        Data::readDataset(fd.GetSelected().string(), testData);
        fd.ClearSelected();
    }

    ImGui::End();
}

Application::Application() = default;
