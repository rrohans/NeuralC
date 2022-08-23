# NeuralC

A custom Neural Network GUI Application written in C++ with a from-scratch Matrix Math Library and 
Dear ImGui.

The network is designed around MNIST and E-MNIST style data and has shown accuracy of over 90% and 80% on their
respective datasets.

## How to run:

### CLion or Visual Studio

Simply clone the repository and use the top-level CMakeLists.txt file to build the project.

### Example Program:

```c++
    srand(time(0)); // seed rand

    // Load datasets
    printf("Loading images...\n");
    auto images = Data::readDataset("mnist_train.csv");
    auto testImages = Data::readDataset("mnist_test.csv");
    
    // Create or Load NN
    NeuralNetwork nn(784, 300, 10, 0.2);
    // NeuralNetwork nn("fullData");

    // Train and then save model
    nn.batchTrainImages(images,  1);
    nn.save("model");

    printf("Train - Percent correct: %.3f %%\n", nn.predict(images) * 100);
    printf("Test - Percent correct: %.3f %%\n", nn.predict(testImages) * 100);
```

## File Structure:

```
NeuralNetwork
|
|---- Activations/
|       - Activation functions for the network
|
|---- Data/
|       - Data class for reading in and normalizing data
|
|---- Matrix/
|       - Complete Matrix class with associated math functionality
|
|---- NeuralNetwork/ 
|       - Neural Network class that contains functionality for training, testing, and prediction 
|
|---- Utils/
|       ---- ProgressBar/
|               - Simple ASCII progress bar
|       ---- ScopedTimer/
|               - Timing class that beings and ends when an instance enters and leaves 
|                 its current scope 
```
