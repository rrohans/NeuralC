#include <iostream>
#include <sstream>

#include "cuda_runtime.h"

#include "Matrix/Matrix.h"
#include "Matrix/MatrixOps.h"
#include "Matrix/Cuda/MatrixKernel.h"
#include "Image/Image.h"
#include "NeuralNetwork/NeuralNetwork.h"

#include "Utils/ProgressBar/ProgressBar.h"

Matrix stringToMatrix(const std::string& data, int rows, int cols);

int main(int argc, char** argv)
{
//
//    srand(time(0)); // seed rand
//
//    // Number of images
//    int numTrainImages = 1;
//    int numTestImages = 0;
//
//    // Load datasets
//    printf("Loading images...\n");
//    auto images = Image::readDataset("C:/Users/marco/Downloads/archive/mnist_train.csv", numTrainImages);
//    auto testImages = Image::readDataset("C:/Users/marco/Downloads/archive/mnist_test.csv", numTestImages);
//
//
//    // Create/Load NN
//    NeuralNetwork nn(784, 300, 10, 0.2);
////    NeuralNetwork nn("fullData");
//
//    // Train and then save model
//    nn.batchTrainImages(images, numTrainImages, 1);
//    nn.save("model");
//
//    printf("Train - Percent correct: %.3f %%\n", nn.predict(images, numTrainImages) * 100);
//    printf("Test - Percent correct: %.3f %%\n", nn.predict(testImages, numTestImages) * 100);
//
//    delete[] images;
//    delete[] testImages;

    int DIMX = 12, DIMZ = 5, DIMY = 2;

    int CCols = DIMZ, CRows = DIMX, ACols = DIMY, ARows = DIMX, BCols = DIMZ, BRows = DIMY;


    float* deviceA, * deviceB, * deviceC;

    float* hostA = (float*)malloc(DIMX * DIMY * sizeof(float));
    float* hostB = (float*)malloc(DIMY * DIMZ * sizeof(float));
    float* hostC = (float*)malloc(DIMX * DIMZ * sizeof(float));



    for (int x = 0; x < DIMX; x++)
        for (int y = 0; y < DIMY; y++) {
            hostA[x * DIMY + y] = rand() / (float)RAND_MAX;
            hostB[x * DIMY + y] = rand() / (float)RAND_MAX;
        }

    cudaMalloc((void**)&deviceA, DIMX * DIMY * sizeof(float));

    cudaMalloc((void**)&deviceB, DIMY * DIMZ * sizeof(float));

    cudaMalloc((void**)&deviceC, DIMX * DIMZ * sizeof(float));


    cudaMemcpy(deviceA, hostA, DIMX * DIMY * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, DIMY * DIMZ * sizeof(float), cudaMemcpyHostToDevice);

    cudaMatrixMultiply(deviceA, deviceB, deviceC, ARows, ACols, BRows, BCols, CRows, CCols);

    cudaMemcpy(hostC, deviceC, DIMX * DIMZ * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < DIMX * DIMZ; i++)
        printf("%lf ", hostC[i]);

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