
#include <iostream>
#include <exception>
#include <opencv2/opencv.hpp>

#include "image_analyzer.h"
#include "image_validator.h"

int main()
{
    std::cout << "================================\n";
    std::cout << "          VISION ENGINE\n";
    std::cout << "================================\n\n";

    const std::string imagePath =
        "assets/sample_images/sample_document.png";

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
