#include <iostream>
#include <fstream>
#include <sstream>

#include "Data.h"

void Data::print() const
{
    // print image to console
    printf("Data label: %d\n", label);
    imageData.print();
}

std::vector<Data> Data::readDataset(const std::string &fileName, int rows, int cols)
{
    // load images from a csv file and return an array to them
    std::ifstream file(fileName, std::ios::in);

    int numOfEntries = (int) std::count(std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>(), '\n') - 2;

    file.clear();
    file.seekg(0);

    if (!file)
    {
        printf("Error opening file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }

    std::vector<Data> images;
    images.reserve(numOfEntries);

    int image = 0;
    std::string line, value;

    std::getline(file, line); // skip first line
    while (std::getline(file, line) && image < numOfEntries)
    {
        images[image] = Data(rows, cols);

        int character = 0;
        std::stringstream str(line);

        while (std::getline(str, value, ','))
        {
            if (character == 0)
                images[image].label = std::stoi(value);
            else
                images[image].imageData.data[character - 1] = (float) std::stoi(value) / 255.0f;

            character++;
        }
        image++;
    }

    file.close();

    if (!file.good())
    {
        printf("Error reading from file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }

    return images;
}

Data::Data(int rows, int cols)
{
    imageData = Matrix(rows, cols);
}
