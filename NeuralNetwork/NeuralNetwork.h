#pragma once

#include "../Matrix/Matrix.h"
#include "../Data/Data.h"

struct NeuralNetwork
{
    int inputLayer = 28 * 28, hiddenLayer = 0, outputLayer = 10;
    float learningRate = 0.0f;

    Matrix hiddenWeights, outputWeights;

    // Constructors
    NeuralNetwork(int input, int hidden, int output, float lRate);

    explicit NeuralNetwork(std::string filePath);

    // member methods
    void batchTrainImages(std::vector<Data> &images, int batchSize, int epochs);

    int predict(Data &image);

    float predict(std::vector<Data> &images, int number);

    void save(std::string filePath);

    void load(std::string filePath);

    void print() const;

    float calculateLoss(Data &image);

private:
    void train(Matrix &input, Matrix &output);

    Matrix feedForward(Matrix m);
};