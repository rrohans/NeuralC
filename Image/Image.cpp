#include <iostream>
#include <fstream>
#include <sstream>

#include "Image.h"

void Image::print() const
{
    // print image to console
    printf("Image label: %d\n", label);
    imageData.print();
}

Image **Image::readDataset(const std::string &fileName, int numberOfImages)
{
    // load images from a csv file and return an array to them
    Image **images = new Image *[numberOfImages];

    std::ifstream file(fileName, std::ios::in);

    if (!file)
    {
        printf("Error opening file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }

    int image = 0;
    std::string line, value;

    std::getline(file, line); // skip first line
    while (std::getline(file, line) && image < numberOfImages)
    {
        images[image] = new Image;
        images[image]->imageData.numRows = 28;
        images[image]->imageData.numCols = 28;
        images[image]->imageData.create();

        int character = 0;
        std::stringstream str(line);

        while (std::getline(str, value, ','))
        {
            if (character == 0)
                images[image]->label = std::stoi(value);
            else
            {
                int cols = images[image]->imageData.numCols;
                images[image]->imageData.data[((character - 1) / 28) * cols + ((character - 1) % 28)] =
                        (float) std::stoi(value) / 255.0f;
            }

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

