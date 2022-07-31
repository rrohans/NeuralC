cmake_minimum_required(VERSION 3.20)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 20)

add_executable(NeuralNetwork main.cpp Matrix/Matrix.cpp Matrix/MatrixOps.cpp Activations/Activations.cpp Activations/Activations.h Data/Data.cpp Data/Data.h NeuralNetwork/NeuralNetwork.cpp NeuralNetwork/NeuralNetwork.h Utils/ProgressBar/ProgressBar.cpp Utils/ProgressBar/ProgressBar.h Utils/ScopedTimer/ScopedTimer.cpp Utils/ScopedTimer/ScopedTimer.h)
