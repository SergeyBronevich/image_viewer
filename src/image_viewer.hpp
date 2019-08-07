#include <vector>
#include <vector>
#include "opencv2/core.hpp"

namespace image_viewer
{
	// Returns list of image paths in the directory
    std::vector<cv::String> list_images(const char* directoryPath);

    static const int DEFAULT_HISTOGRAM_WIDTH = 256;
    static const int DEFAULT_HISTOGRAM_HEIGHT = 256;

	// Makes histogram image
    cv::Mat make_histogram_image(
        const cv::Mat& image, int histogramWidth = DEFAULT_HISTOGRAM_WIDTH,
        int histogramHeight = DEFAULT_HISTOGRAM_HEIGHT);
} // namespace image_viewer
