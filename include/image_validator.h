
#pragma once

#include "image_analyzer.h"

struct ValidationResult
{
    bool resolutionValid;
    bool brightnessValid;
    bool contrastValid;
    bool sharpnessValid;
    bool imageValid;
};

class ImageValidator
{
public:
    ValidationResult validate(const ImageMetrics& metrics) const;
};
