#include <iostream>
#include <fstream>
#include <stdexcept>

const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

class Image
{

private:
    int width, height;
    int pixels[MAX_HEIGHT][MAX_WIDTH];

    void checkCoordinates(int x, int y) const
    {
        if (x < 0 || x >= width || y < 0 || y >= height)        
            throw std::out_of_range("Pixel coordinates out of range");
        
    }
public:
    Image(int width, int height) : width(width), height(height)
    {
        if (width <= 0 || width > MAX_WIDTH || height <= 0 || height > MAX_HEIGHT)
            throw std::invalid_argument("Invalid image dimensions");

        // Инициализация массива нулями
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)            
                pixels[y][x] = 0;
            
        }
    }

    int getPixel(int x, int y) const
    {
        checkCoordinates(x, y);
        return pixels[y][x];
    }

    void setPixel(int x, int y, int value)
    {
        checkCoordinates(x, y);
        pixels[y][x] = value;
    }

    static Image loadFromFile(const std::string& filename)
    {
        std::ifstream inputFile(filename);
        if (!inputFile)        
            throw std::runtime_error("Unable to open file for reading");
        

        int width, height;
        inputFile >> width >> height;
        Image image(width, height);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
                inputFile >> image.pixels[y][x];
            
        }

        inputFile.close();
        return image;
    }

    void saveToFile(const std::string& filename)
    {
        std::ofstream outputFile(filename);
        if (!outputFile)        
            throw std::runtime_error("Unable to open file for writing");
        

        outputFile << width << " " << height << std::endl;

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)            
                outputFile << pixels[y][x] << " ";
            
            outputFile << std::endl;
        }
        outputFile.close();
    }

    void printAscii() const
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                std::cout << (pixels[y][x] == 1 ? '#' : ' ') << " ";
            }
            std::cout << std::endl;
        }
    }



};

int main()
{
    try
    {
        Image img = Image::loadFromFile("hi.txt");
        std::cout << "Loaded image in ASCII from file hi.txt:" << std::endl;
        img.printAscii();

        std::cout << std::endl;


        img.saveToFile("hi2.txt");
        std::cout << "Image saved to hi2.txt" << std::endl;

        Image img2 = Image::loadFromFile("hi2.txt");
        std::cout << "Loaded image in ASCII from file hi2.txt:" << std::endl;
        img.printAscii();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }



    return 0;
}
