#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "ImageProcessing.h"
#include "Sobel_Filter.h"

using namespace cv;

int main()
{
    cv::Mat img = cv::imread("image-1.png");
    cv::imshow("RGB output", img);

    const unsigned char* bgr_input = (unsigned char*)img.data;
    unsigned char* gray_output = new unsigned char[img.rows * img.cols];
    ImageProcessing::to_gray(bgr_input, img.cols, img.rows, img.channels(), gray_output);
    cv::Mat output_gray(img.rows, img.cols, CV_8UC1, gray_output);

    cv::Mat output_sobel_x(img.rows, img.cols, CV_8UC1);
    cv::Mat output_sobel_y(img.rows, img.cols, CV_8UC1);
    cv::Mat output_sobel(img.rows, img.cols, CV_8UC1);


    Sobel_Filter::sobel_x(output_gray, output_sobel_x);
    Sobel_Filter::sobel_y(output_gray, output_sobel_y);
    Sobel_Filter::sobel(output_gray, output_sobel);


    cv::imshow("gray scale output", output_gray);
    cv::imshow("sobel_x", output_sobel_x);
    cv::imshow("sobel_y", output_sobel_y);
    cv::imshow("sobel", output_sobel);


    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}



