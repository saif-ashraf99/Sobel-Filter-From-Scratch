#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

class ImageProcessing
{
public:

    // Here I use weighed method to convert RGB image to gray scale
    static void to_gray(const unsigned char* bgr_input,
        const int width,
        const int height,
        const int channel,
        unsigned char* gray_output) {
        int index = 0;
        int step = channel * width;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width * channel; col += channel) {
                gray_output[index] = 0.11 * bgr_input[row * step + col] +
                    0.59 * bgr_input[row * step + col + 1] +
                    0.3 * bgr_input[row * step + col + 2];
                index++;
            }
        }
    }
};

