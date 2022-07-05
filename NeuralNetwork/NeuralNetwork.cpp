
#include <cmath>
#include <filesystem>
#include <fstream>


#include "NeuralNetwork.h"
#include "../Matrix/MatrixOps.h"
#include "../Activations/Activations.h"

#include "../Utils/ProgressBar/ProgressBar.h"
#include "../Utils/ScopedTimer/ScopedTimer.h"


using namespace MatrixOps;
using namespace Activations;

NeuralNetwork::NeuralNetwork(int input, int hidden, int output, float lRate)
{
    inputLayer = input;
    hiddenLayer = hidden;
    outputLayer = output;
    learningRate = lRate;

    hiddenWeights = Matrix(hiddenLayer, inputLayer);
    outputWeights = Matrix(outputLayer, hiddenLayer);

    hiddenWeights.randomize(1);
    outputWeights.randomize(1);
}

void NeuralNetwork::train(Matrix &input, Matrix &output)
{
    // perform feed forward
    auto hiddenInputs = multiply(hiddenWeights, input);
    auto hiddenOutputs = map(sigmoid, hiddenInputs);
    auto finalInputs = multiply(outputWeights, hiddenOutputs);
    auto finalOutputs = map(sigmoid, finalInputs);

    // calculate errors
    auto outputErrors = subtract(output, finalOutputs);
    auto transposedOutputWeights = transpose(outputWeights);
    auto hiddenErrors = multiply(transposedOutputWeights, outputErrors);

    // backpropagation (final outputs)
    auto sigmoidPrimed = sigmoidPrimeValues(finalOutputs);
    auto multiplySPV = elementwiseMultiply(outputErrors, sigmoidPrimed);
    auto transposedHiddenOutputs = transpose(hiddenOutputs);
    auto dMatrix = multiply(multiplySPV, transposedHiddenOutputs);
    auto sMatrix = scale(dMatrix, learningRate);
    auto aMatrix = add(outputWeights, sMatrix);
    outputWeights.copy(aMatrix);

//     backpropagation (hidden outputs)
    auto sigmoidPrimed2 = sigmoidPrimeValues(hiddenOutputs);
    auto multiplySPV2 = elementwiseMultiply(hiddenErrors, sigmoidPrimed2);
    auto transposedInputs = transpose(input);
    auto dMatrix2 = multiply(multiplySPV2, transposedInputs);
    auto sMatrix2 = scale(dMatrix2, learningRate);
    auto aMatrix2 = add(hiddenWeights, sMatrix2);
    hiddenWeights.copy(aMatrix2);
}

void NeuralNetwork::batchTrainImages(Image **images, int batchSize, int epochs)
{
    ProgressBar p(0, epochs);
    ScopedTimer t("Batch Train");

    float loss = 0.0f;

    p.print();

    // Train NN using a batch of images
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        for (int i = 0; i < batchSize; i++)
        {
            auto currentImage = images[i];
            currentImage->imageData.flatten(0);
            Matrix output(this->outputLayer, 1);
            output.data[currentImage->label][0] = 1;
            train(currentImage->imageData, output);

            loss += calculateLoss(currentImage);

            if (i > 0 && i % 100 == 0)
                printf("Images complete: %d\n", i);
        }
        p.update(epoch + 1);
        p.print("Loss - " + std::to_string(loss / (float) batchSize));

        loss = 0.0f;
    }
}

int NeuralNetwork::predict(Image *image)
{
    // predict label given image
    image->imageData.flatten(0);

    auto result = feedForward(image->imageData);
    result.flatten(0);

    return result.argMax();
}

float NeuralNetwork::predict(Image **images, int n)
{
    // predicts the first n images and returns percentage correct
    int numberCorrect = 0;
    for (int i = 0; i < n; i++)
    {
        auto prediction = predict(images[i]);
        if (prediction == images[i]->label)
            numberCorrect++;
    }

    return (float) numberCorrect / (float) n;
}

void NeuralNetwork::save(std::string filePath)
{
    // Save model to disk
    std::filesystem::create_directory(filePath);
    std::ofstream file(filePath + "/descriptor", std::ios::out | std::ios::binary);

    if (!file)
    {
        printf("Error creating descriptor under: %s\n", filePath.c_str());
        exit(EXIT_FAILURE);
    }
    file.write((char *) &inputLayer, sizeof(int));
    file.write((char *) &hiddenLayer, sizeof(int));
    file.write((char *) &outputLayer, sizeof(int));
    file.write((char *) &learningRate, sizeof(float));

    file.close();

    if (!file.good())
    {
        printf("Error saving descriptor under: %s\n", filePath.c_str());
        exit(EXIT_FAILURE);
    }

    hiddenWeights.save(filePath + "/hidden");
    outputWeights.save(filePath + "/output");
}

void NeuralNetwork::load(std::string filePath)
{
    // Load a model from disk
    std::ifstream file(filePath + "/descriptor", std::ios::binary);

    if (!file)
    {
        printf("Error opening descriptor under: %s\n", filePath.c_str());
        exit(EXIT_FAILURE);
    }
    file.read((char *) &inputLayer, sizeof(int));
    file.read((char *) &hiddenLayer, sizeof(int));
    file.read((char *) &outputLayer, sizeof(int));
    file.read((char *) &learningRate, sizeof(float));

    file.close();

    if (!file.good())
    {
        printf("Error saving descriptor under: %s\n", filePath.c_str());
        exit(EXIT_FAILURE);
    }

    hiddenWeights.load(filePath + "/hidden");
    outputWeights.load(filePath + "/output");
}

NeuralNetwork::NeuralNetwork(std::string filePath)
{
    load(filePath);
}

void NeuralNetwork::print() const
{
    // print details of the model
    printf("Number of inputs: %d\n", inputLayer);
    printf("Number of hidden: %d\n", hiddenLayer);
    printf("Number of outputs: %d\n", outputLayer);
    printf("Hidden Layer Weights\n");
    hiddenWeights.print();
    printf("Output Layer Weights\n");
    outputWeights.print();
}

float NeuralNetwork::calculateLoss(Image *image)
{
    // predict label given image
    image->imageData.flatten(0);

    auto result = feedForward(image->imageData);
    result.flatten(0);

    auto weight = result.data[result.argMax()][0];

    return (float) std::pow((weight - 1.0), 2);

}

Matrix NeuralNetwork::feedForward(Matrix m)
{
    auto hiddenInputs = multiply(hiddenWeights, m);
    auto hiddenOutputs = map(sigmoid, hiddenInputs);
    auto finalInputs = multiply(outputWeights, hiddenOutputs);
    auto finalOutputs = map(sigmoid, finalInputs);
    auto result = softmax(finalOutputs);

    return result;
}