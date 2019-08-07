#include "image_viewer.hpp"
#include "opencv2/imgproc.hpp"

namespace image_viewer
{
    static const std::vector<cv::String> ALLOWED_EXTENSIONS = {"jpg", "jpeg",
                                                               "png"};

    std::vector<cv::String> list_images(const char* directoryPath)
    {
        std::vector<cv::String> imagesPaths;

        for (size_t i = 0; i < ALLOWED_EXTENSIONS.size(); i++)
        {
            std::vector<cv::String> imagesPathsWithExtension;

            cv::String pattern(cv::String(directoryPath) + "*." +
                               ALLOWED_EXTENSIONS[i]);

            cv::glob(pattern, imagesPathsWithExtension, true);

            imagesPaths.insert(imagesPaths.end(),
                               imagesPathsWithExtension.begin(),
                               imagesPathsWithExtension.end());
        }

        return imagesPaths;
    }

    cv::Mat make_histogram_image(const cv::Mat& image, int histogramWidth,
                                 int histogramHeight)
    {
        std::vector<cv::Mat> bgrPlanes;

        cv::split(image, bgrPlanes);

        const int HISTOGRAM_SIZE = 256;
        const float range[] = {0, 256};
        const float* histogramRange = {range};
        bool uniform = true;
        bool accumulate = false;

        cv::Mat blueHistogram, greenHistogram, redHistogram;

        cv::calcHist(&bgrPlanes[0], 1, 0, cv::Mat(), blueHistogram, 1,
                     &HISTOGRAM_SIZE, &histogramRange, uniform, accumulate);
        cv::calcHist(&bgrPlanes[1], 1, 0, cv::Mat(), greenHistogram, 1,
                     &HISTOGRAM_SIZE, &histogramRange, uniform, accumulate);
        cv::calcHist(&bgrPlanes[2], 1, 0, cv::Mat(), redHistogram, 1,
                     &HISTOGRAM_SIZE, &histogramRange, uniform, accumulate);

        cv::Mat histogramImage(histogramHeight, histogramWidth, CV_8UC3,
                               cv::Scalar(0, 0, 0));

        const int binWidth = cvRound((double)histogramWidth / HISTOGRAM_SIZE);

        cv::normalize(blueHistogram, blueHistogram, 0, histogramImage.rows,
                      cv::NORM_MINMAX, -1, cv::Mat());
        cv::normalize(greenHistogram, greenHistogram, 0, histogramImage.rows,
                      cv::NORM_MINMAX, -1, cv::Mat());
        cv::normalize(redHistogram, redHistogram, 0, histogramImage.rows,
                      cv::NORM_MINMAX, -1, cv::Mat());

        for (int i = 1; i < HISTOGRAM_SIZE; i++)
        {
            cv::line(histogramImage,
                     cv::Point(binWidth * (i - 1),
                               histogramHeight -
                                   cvRound(blueHistogram.at<float>(i - 1))),
                     cv::Point(
                         binWidth * (i),
                         histogramHeight - cvRound(blueHistogram.at<float>(i))),
                     cv::Scalar(255, 0, 0), 2, 8, 0);
            cv::line(histogramImage,
                     cv::Point(binWidth * (i - 1),
                               histogramHeight -
                                   cvRound(greenHistogram.at<float>(i - 1))),
                     cv::Point(binWidth * (i),
                               histogramHeight -
                                   cvRound(greenHistogram.at<float>(i))),
                     cv::Scalar(0, 255, 0), 2, 8, 0);
            cv::line(
                histogramImage,
                cv::Point(
                    binWidth * (i - 1),
                    histogramHeight - cvRound(redHistogram.at<float>(i - 1))),
                cv::Point(binWidth * (i),
                          histogramHeight - cvRound(redHistogram.at<float>(i))),
                cv::Scalar(0, 0, 255), 2, 8, 0);
        }

        return histogramImage;
    }
} // namespace image_viewer
