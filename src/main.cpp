
#include <iostream>
#include <exception>
#include <opencv2/opencv.hpp>

#include "image_analyzer.h"
#include "image_validator.h"

int main(int argc, char* argv[])
{
    std::cout << "================================\n";
    std::cout << "          VISION ENGINE\n";
    std::cout << "================================\n\n";

    if (argc < 2)
{
    std::cerr << "ERROR: No image path supplied.\n\n";
    std::cerr << "Usage:\n";
    std::cerr << "vision-engine.exe <image_path>\n\n";
    std::cerr << "Example:\n";
    std::cerr << "vision-engine.exe \"assets/sample_images/sample_document.png\"\n";

    return 1;
}

    const std::string imagePath = argv[1];

    cv::Mat image = cv::imread(imagePath);

    if (image.empty())
    {
        std::cerr << "ERROR: Unable to load image: "
                  << imagePath << "\n";
        return 1;
    }

    try
    {
        // Analyse the image
        ImageAnalyzer analyzer;
        ImageMetrics metrics = analyzer.analyze(image);

        // Validate the measurements
        ImageValidator validator;
        ValidationResult result = validator.validate(metrics);

        // Display analysis
        std::cout << "Image Analysis Results\n";
        std::cout << "------------------------------\n";

        std::cout << "Width: " << metrics.width << "\n";
        std::cout << "Height: " << metrics.height << "\n";
        std::cout << "Brightness: " << metrics.brightness << "\n";
        std::cout << "Contrast: " << metrics.contrast << "\n";
        std::cout << "Sharpness: " << metrics.sharpness << "\n\n";

        // Display validation
        std::cout << "Validation Results\n";
        std::cout << "------------------------------\n";

        std::cout << "Resolution: "
                  << (result.resolutionValid ? "PASS" : "FAIL") << "\n";

        std::cout << "Brightness: "
                  << (result.brightnessValid ? "PASS" : "FAIL") << "\n";

        std::cout << "Contrast: "
                  << (result.contrastValid ? "PASS" : "FAIL") << "\n";

        std::cout << "Sharpness: "
                  << (result.sharpnessValid ? "PASS" : "FAIL") << "\n";

        std::cout << "------------------------------\n";

        std::cout << "OVERALL RESULT: "
                  << (result.imageValid ? "PASSED" : "FAILED") << "\n";

        return result.imageValid ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "ERROR: " << error.what() << "\n";
        return 1;
    }
}
