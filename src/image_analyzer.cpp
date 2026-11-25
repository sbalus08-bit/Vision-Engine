
#include "image_analyzer.h"

#include <opencv2/imgproc.hpp>
#include <stdexcept>

ImageMetrics ImageAnalyzer::analyze(const cv::Mat& image) const
{
    if (image.empty())
    {
        throw std::invalid_argument("Cannot analyse an empty image.");
    }

    ImageMetrics metrics{};

    metrics.width = image.cols;
    metrics.height = image.rows;

    cv::Mat grayscaleImage;
    cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

    cv::Scalar averageBrightness = cv::mean(grayscaleImage);
    metrics.brightness = averageBrightness[0];

    cv::Scalar mean;
    cv::Scalar standardDeviation;

    cv::meanStdDev(grayscaleImage, mean, standardDeviation);
    metrics.contrast = standardDeviation[0];

    cv::Mat laplacian;
    cv::Laplacian(grayscaleImage, laplacian, CV_64F);

    cv::Scalar laplacianMean;
    cv::Scalar laplacianStdDev;

    cv::meanStdDev(laplacian, laplacianMean, laplacianStdDev);

    metrics.sharpness =
        laplacianStdDev[0] * laplacianStdDev[0];

    return metrics;
}
