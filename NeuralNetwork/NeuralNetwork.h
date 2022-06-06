#pragma once

#include "../Matrix/Matrix.h"
#include "../Image/Image.h"

struct NeuralNetwork
{
    int inputLayer = 28 * 28, hiddenLayer = 0, outputLayer = 10;
    float learningRate = 0.0f;

    Matrix hiddenWeights, outputWeights;

    // Constructors
    NeuralNetwork(int input, int hidden, int output, float lRate);

    explicit NeuralNetwork(std::string filePath);

    // member methods
    void batchTrainImages(Image **images, int batchSize, int epochs);

    int predict(Image *image);

    float predict(Image **images, int number);

    void save(std::string filePath);

    void load(std::string filePath);

    void print() const;

    float calculateLoss(Image *image);

private:
    void train(Matrix &input, Matrix &output);

    Matrix feedForward(Matrix m);
};