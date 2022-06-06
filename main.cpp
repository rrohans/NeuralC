#include <iostream>
#include <sstream>

#include "Matrix/Matrix.h"
#include "Matrix/MatrixOps.h"
#include "Image/Image.h"
#include "NeuralNetwork/NeuralNetwork.h"

#include "Utils/ProgressBar/ProgressBar.h"

Matrix stringToMatrix(const std::string& data, int rows, int cols);

int main(int argc, char** argv)
{
    srand(time(0)); // seed rand

    // Number of images
    int numTrainImages = 60000 - 1;
    int numTestImages = 500;

    // Load datasets
    printf("Loading images...\n");
    auto images = Image::readDataset("mnist_train.csv", numTrainImages);
    auto testImages = Image::readDataset("mnist_test.csv", numTestImages);

    // Create/Load NN
    NeuralNetwork nn(784, 300, 10, 0.2);
//    NeuralNetwork nn("fullData");

    // Train and then save model
    nn.batchTrainImages(images, numTrainImages, 1);
    nn.save("model");

    printf("Train - Percent correct: %.3f %%\n", nn.predict(images, numTrainImages) * 100);
    printf("Test - Percent correct: %.3f %%\n", nn.predict(testImages, numTestImages) * 100);

    delete[] images;
    delete[] testImages;

    return 0;
}

Matrix stringToMatrix(const std::string& data, int rows, int cols)
{
    Matrix m(rows, cols);
    std::vector<std::vector<float>> t(rows);

    for (auto & i : t)
        i = std::vector<float>(cols);

    std::stringstream test(data);
    std::string segment;
    std::vector<std::string> seglist;
    while(std::getline(test, segment, ','))
    {
        seglist.push_back(segment);
    }

    for (int i = 0; i < t.size(); i++)
        for (int j = 0; j < t[0].size(); j++)
            t[i][j] = atoi(seglist[i*t.size()+j].c_str()) / 255.0;

    m.data = t;

    return m;
}