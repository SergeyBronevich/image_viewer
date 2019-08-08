#include <iostream>
#include <vector>
#include <cassert>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "image_viewer.hpp"

namespace image_viewer
{
    static const char* ABOUT_APP = "image_viewer v1.0.0";
    static const char* KEYS = {
        "{help h||print this message} \
		 {directory_path d|<none>|path to directory with (.jpg or .jpeg or .png) images}"};

    static const char* IMAGE_WINDOW_NAME = "image";
    static const int IMAGE_WINDOW_WIDTH = 800;
    static const int IMAGE_WINDOW_HEIGHT = 600;
    static const char* TRACKBAR_NAME = "images";
    static const char* HISTOGRAM_WINDOW_NAME = "histogram";
    static const int HISTOGRAM_WIDTH = 256;
    static const int HISTOGRAM_HEIGHT = 256;
    static const int ESC_KEY_CODE = 27;

    void load_image(int arg, void* userdata)
    {
        assert(userdata);

        std::vector<cv::String>* imagesPaths =
            static_cast<std::vector<cv::String>*>(userdata);

        assert(arg < (*imagesPaths).size());

        cv::String imagePath = (*imagesPaths)[arg];

        cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

        if (image.empty())
        {
            cv::String error("Cannot read image file: " + imagePath);

            cv::Mat errorImage(IMAGE_WINDOW_HEIGHT, IMAGE_WINDOW_WIDTH, CV_8UC3,
                               cv::Scalar(255, 255, 255));

            cv::putText(errorImage, error,
                        cv::Point(0, IMAGE_WINDOW_HEIGHT / 2),
                        cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 0, 255), 1,
                        cv::FILLED);

            cv::imshow(IMAGE_WINDOW_NAME, errorImage);
            cv::setWindowTitle(IMAGE_WINDOW_NAME, error);

            cv::Mat histogramImage(HISTOGRAM_WIDTH, HISTOGRAM_HEIGHT, CV_8UC3,
                                   cv::Scalar(0, 0, 0));
            cv::imshow(HISTOGRAM_WINDOW_NAME, histogramImage);

            std::cerr << error << std::endl;

            return;
        }

        cv::Mat histogramImage(
            make_histogram_image(image, HISTOGRAM_WIDTH, HISTOGRAM_HEIGHT));

        cv::imshow(IMAGE_WINDOW_NAME, image);
        cv::setWindowTitle(IMAGE_WINDOW_NAME, imagePath);

        cv::imshow(HISTOGRAM_WINDOW_NAME, histogramImage);
    }

    int main(int argc, char** argv)
    {
        cv::CommandLineParser commandLineParser(argc, argv, KEYS);

        commandLineParser.about(ABOUT_APP);

        if (commandLineParser.has("help"))
        {
            commandLineParser.printMessage();

            return 0;
        }

        if (!commandLineParser.check())
        {
            commandLineParser.printErrors();

            return -1;
        }

        cv::String directoryPath(
            commandLineParser.get<cv::String>("directory_path"));

        std::vector<cv::String> imagesPaths;

        try
        {
            imagesPaths = image_viewer::list_images(directoryPath.c_str());
        }
        catch (const cv::Exception& e)
        {
            const cv::String error("Cannot read image list from directory: " +
                                   directoryPath + "(" + e.what() + ")");

            std::cerr << error << std::endl;

            return -1;
        }

        if (!imagesPaths.size())
        {
            const cv::String error("No image files in directory: " +
                                   directoryPath);

            std::cerr << error << std::endl;

            return -1;
        }

        cv::namedWindow(IMAGE_WINDOW_NAME, cv::WINDOW_NORMAL);
        cv::resizeWindow(IMAGE_WINDOW_NAME, IMAGE_WINDOW_WIDTH,
                         IMAGE_WINDOW_HEIGHT);

        int trackBarPos = 0;

        cv::createTrackbar(TRACKBAR_NAME, IMAGE_WINDOW_NAME, &trackBarPos,
                           static_cast<int>(imagesPaths.size() - 1), load_image,
                           &imagesPaths);

        cv::namedWindow(HISTOGRAM_WINDOW_NAME, cv::WINDOW_NORMAL);

        load_image(0, &imagesPaths);

        if (cv::waitKey() == ESC_KEY_CODE)
        {
            std::cout << "<Esc> key is pressed by user" << std::endl;

            return 0;
        }

        return 0;
    }

} // namespace image_viewer

int main(int argc, char** argv)
{
    return image_viewer::main(argc, argv);
}
