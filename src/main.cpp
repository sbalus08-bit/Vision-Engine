
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    std::cout << "================================\n";
    std::cout << "       NCR VISION ENGINE\n";
    std::cout << "================================\n\n";

    // Load the sample image
    std::string imagePath = "assets/sample_images/sample_document.png";

    cv::Mat image = cv::imread(imagePath);

    // Check whether the image loaded successfully
    if (image.empty())
    {
        std::cerr << "ERROR: Unable to load image: "
                  << imagePath << "\n";
        return 1;
    }

    // Extract image dimensions
    int width = image.cols;
    int height = image.rows;

    // Convert image to grayscale
    cv::Mat grayscaleImage;

    cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

    // Calculate average brightness
    cv::Scalar averageBrightness = cv::mean(grayscaleImage);


// Calculate image contrast
cv::Scalar mean;
cv::Scalar standardDeviation;

cv::meanStdDev(grayscaleImage, mean, standardDeviation);

double contrast = standardDeviation[0];

// Calculate image sharpness using Laplacian variance
cv::Mat laplacian;

cv::Laplacian(grayscaleImage, laplacian, CV_64F);

cv::Scalar laplacianMean;
cv::Scalar laplacianStdDev;

cv::meanStdDev(laplacian, laplacianMean, laplacianStdDev);

double sharpness = laplacianStdDev[0] * laplacianStdDev[0];


    // Display analysis results
    std::cout << "IMAGE ANALYSIS\n";
    std::cout << "--------------------------------\n";

    std::cout << "Image loaded successfully!\n";
    std::cout << "Width: " << width << " pixels\n";
    std::cout << "Height: " << height << " pixels\n";

    std::cout << "Average brightness: "
          << averageBrightness[0] << "\n";

    std::cout << "Contrast: "
          << contrast << "\n";

    std::cout << "Sharpness: "
          << sharpness << "\n";

    std::cout << "\nImage processing completed.\n";

    return 0;
}
