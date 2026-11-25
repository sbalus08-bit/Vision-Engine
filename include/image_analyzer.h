
#pragma once

#include <opencv2/core.hpp>

struct ImageMetrics
{
    int width;
    int height;
    double brightness;
    double contrast;
    double sharpness;
};

class ImageAnalyzer
{
public:
    ImageMetrics analyze(const cv::Mat& image) const;
};
