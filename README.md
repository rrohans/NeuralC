# NeuralC

A custom Neural Network framework written in C++ with a from-scratch Matrix Math Library without any external
dependencies.

The network is designed around MNIST and E-MNIST style data and has shown accuracy of over 90% and 80% on their
respective datasets.

## How to run:

### CLion or Visual Studio

Simply clone the repository and use the top-level CMakeLists.txt file to build the project.

## File Structure:

```
NeuralNetwork
|
|---- Activations/
|       - Activation functions for the network
|
|---- Image/
|       - Image class for reading in and normalizing data
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
