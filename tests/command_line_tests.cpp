
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif

// Helper function to execute Vision Engine
std::string runApplication(const std::string& arguments)
{
    const std::string command =
        ".\\build\\vision-engine.exe " + arguments + " 2>&1";

    FILE* pipe = POPEN(command.c_str(), "r");

    if (!pipe)
    {
        throw std::runtime_error("Failed to launch Vision Engine.");
    }

    char buffer[256];
    std::string output;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        output += buffer;
    }

    PCLOSE(pipe);

    return output;
}

// Test 1: No image path supplied
TEST(CommandLineTests, RejectsMissingImagePath)
{
    std::string output = runApplication("");

    EXPECT_NE(
        output.find("No image path supplied"),
        std::string::npos
    );

    EXPECT_NE(
        output.find("Usage:"),
        std::string::npos
    );
}

// Test 2: Non-existent image path
TEST(CommandLineTests, RejectsMissingImageFile)
{
    std::string output = runApplication(
        "\"assets/sample_images/does_not_exist.png\""
    );

    EXPECT_NE(
        output.find("Unable to load image"),
        std::string::npos
    );
}

// Test 3: Valid image supplied
TEST(CommandLineTests, AcceptsValidImagePath)
{
    std::string output = runApplication(
        "\"assets/sample_images/sample_document.png\""
    );

    EXPECT_NE(
        output.find("OVERALL RESULT: PASSED"),
        std::string::npos
    );
}

// Test 4: Unsupported image file
TEST(CommandLineTests, RejectsUnsupportedImageFile)
{
    const std::string testFile =
        "assets/sample_images/invalid_image.txt";

    {
        std::ofstream file(testFile);
        file << "This is not an image.";
    }

    std::string output = runApplication(
        "\"assets/sample_images/invalid_image.txt\""
    );

    EXPECT_NE(
        output.find("Unable to load image"),
        std::string::npos
    );

    std::remove(testFile.c_str());
}
