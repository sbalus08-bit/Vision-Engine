
#include <iostream>
#include <opencv2/opencv.hpp>
#include "image_analyzer.h"

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

    ImageAnalyzer analyzer;
    ImageMetrics metrics = analyzer.analyze(image);

    const int MIN_WIDTH = 800;
    const int MIN_HEIGHT = 600;
    const double MIN_BRIGHTNESS = 50.0;
    const double MAX_BRIGHTNESS = 220.0;
    const double MIN_CONTRAST = 20.0;
    const double MIN_SHARPNESS = 1000.0;

    bool resolutionValid =
        metrics.width >= MIN_WIDTH &&
        metrics.height >= MIN_HEIGHT;

    bool brightnessValid =
        metrics.brightness >= MIN_BRIGHTNESS &&
        metrics.brightness <= MAX_BRIGHTNESS;

    bool contrastValid =
        metrics.contrast >= MIN_CONTRAST;

    bool sharpnessValid =
        metrics.sharpness >= MIN_SHARPNESS;

    bool imageValid =
        resolutionValid &&
        brightnessValid &&
        contrastValid &&
        sharpnessValid;

    std::cout << "Image Analysis Results\n";
    std::cout << "------------------------------\n";

    std::cout << "Width: " << metrics.width << "\n";
    std::cout << "Height: " << metrics.height << "\n";
    std::cout << "Brightness: " << metrics.brightness << "\n";
    std::cout << "Contrast: " << metrics.contrast << "\n";
    std::cout << "Sharpness: " << metrics.sharpness << "\n\n";

    std::cout << "Validation Results\n";
    std::cout << "------------------------------\n";

    std::cout << "Resolution: "
              << (resolutionValid ? "PASS" : "FAIL") << "\n";

    std::cout << "Brightness: "
              << (brightnessValid ? "PASS" : "FAIL") << "\n";

    std::cout << "Contrast: "
              << (contrastValid ? "PASS" : "FAIL") << "\n";

    std::cout << "Sharpness: "
              << (sharpnessValid ? "PASS" : "FAIL") << "\n";

    std::cout << "------------------------------\n";

    std::cout << "OVERALL RESULT: "
              << (imageValid ? "PASSED" : "FAILED") << "\n";

    return imageValid ? 0 : 1;
}
