
#include "image_validator.h"

ValidationResult ImageValidator::validate(
    const ImageMetrics& metrics) const
{
    const int MIN_WIDTH = 800;
    const int MIN_HEIGHT = 600;

    const double MIN_BRIGHTNESS = 50.0;
    const double MAX_BRIGHTNESS = 220.0;
    const double MIN_CONTRAST = 20.0;
    const double MIN_SHARPNESS = 1000.0;

    ValidationResult result{};

    result.resolutionValid =
        metrics.width >= MIN_WIDTH &&
        metrics.height >= MIN_HEIGHT;

    result.brightnessValid =
        metrics.brightness >= MIN_BRIGHTNESS &&
        metrics.brightness <= MAX_BRIGHTNESS;

    result.contrastValid =
        metrics.contrast >= MIN_CONTRAST;

    result.sharpnessValid =
        metrics.sharpness >= MIN_SHARPNESS;

    result.imageValid =
        result.resolutionValid &&
        result.brightnessValid &&
        result.contrastValid &&
        result.sharpnessValid;

    return result;
}
