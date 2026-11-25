
#include <gtest/gtest.h>
#include "image_validator.h"
#include <opencv2/core.hpp>
#include "image_analyzer.h"
#include <stdexcept>

// Create a set of valid image measurements
ImageMetrics validMetrics()
{
    return {
        1400,       // Width
        995,        // Height
        194.658,    // Brightness
        44.3862,    // Contrast
        12231.8     // Sharpness
    };
}

// Test 1: All metrics should pass
TEST(ImageValidatorTests, AcceptsValidImage)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();

    ValidationResult result = validator.validate(metrics);

    EXPECT_TRUE(result.imageValid);
}

// Test 2: Resolution too small
TEST(ImageValidatorTests, RejectsLowResolution)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.width = 600;

    ValidationResult result = validator.validate(metrics);

    EXPECT_FALSE(result.resolutionValid);
    EXPECT_FALSE(result.imageValid);
}

// Test 3: Brightness too low
TEST(ImageValidatorTests, RejectsLowBrightness)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.brightness = 30.0;

    ValidationResult result = validator.validate(metrics);

    EXPECT_FALSE(result.brightnessValid);
    EXPECT_FALSE(result.imageValid);
}

// Test 4: Contrast too low
TEST(ImageValidatorTests, RejectsLowContrast)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.contrast = 10.0;

    ValidationResult result = validator.validate(metrics);

    EXPECT_FALSE(result.contrastValid);
    EXPECT_FALSE(result.imageValid);
}

// Test 5: Sharpness too low
TEST(ImageValidatorTests, RejectsLowSharpness)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.sharpness = 500.0;

    ValidationResult result = validator.validate(metrics);

    EXPECT_FALSE(result.sharpnessValid);
    EXPECT_FALSE(result.imageValid);
}


// Test 6: Minimum brightness boundary
TEST(ImageValidatorTests, AcceptsMinimumBrightness)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.brightness = 50.0;

    ValidationResult result = validator.validate(metrics);

    EXPECT_TRUE(result.brightnessValid);
    EXPECT_TRUE(result.imageValid);
}

// Test 7: Maximum brightness boundary
TEST(ImageValidatorTests, AcceptsMaximumBrightness)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.brightness = 220.0;

    ValidationResult result = validator.validate(metrics);

    EXPECT_TRUE(result.brightnessValid);
    EXPECT_TRUE(result.imageValid);
}

// Test 8: Minimum resolution boundary
TEST(ImageValidatorTests, AcceptsMinimumResolution)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.width = 800;
    metrics.height = 600;

    ValidationResult result = validator.validate(metrics);

    EXPECT_TRUE(result.resolutionValid);
    EXPECT_TRUE(result.imageValid);
}

// Test 9: Minimum sharpness boundary
TEST(ImageValidatorTests, AcceptsMinimumSharpness)
{
    ImageValidator validator;

    ImageMetrics metrics = validMetrics();
    metrics.sharpness = 1000.0;

    ValidationResult result = validator.validate(metrics);

    EXPECT_TRUE(result.sharpnessValid);
    EXPECT_TRUE(result.imageValid);
}

TEST(ImageAnalyzerTests, RejectsEmptyImage)
{
    ImageAnalyzer analyzer;

    cv::Mat emptyImage;

    EXPECT_THROW(
        analyzer.analyze(emptyImage),
        std::invalid_argument
    );
}