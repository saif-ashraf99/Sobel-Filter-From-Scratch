#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

class Sobel_Filter {
public:

    static void sobel_x(const cv::Mat& input, cv::Mat& output) {
        // Check GrayScale images     
        CV_Assert(input.channels() == 1 && output.channels() == 1);

        // Define Kernel     
        std::vector<int> kernel({ 1,0,-1,2,0,-2,1,0,-1 });
        int kernel_size = 3;

        unsigned char* data_in = (unsigned char*)(input.data);
        unsigned char* data_out = (unsigned char*)(output.data);
        for (int row = 0; row < input.rows; row++) {
            for (int col = 0; col < input.cols; col += 1) {

                if (row <= kernel_size / 2 || row >= input.rows - kernel_size / 2 ||
                    col <= kernel_size / 2 || col >= input.cols - kernel_size / 2) {
                    data_out[output.step * row + col] = 0;
                    continue;
                }
                int sum = 0;
                int k_ind = 0;
                for (int k_row = -kernel_size / 2; k_row <= kernel_size / 2; ++k_row) {
                    for (int k_col = -kernel_size / 2; k_col <= kernel_size / 2; ++k_col) {
                        sum += kernel[k_ind] * data_in[input.step * (row + k_row) + col + k_col];
                        k_ind++;
                    }
                }
                data_out[output.step * row + col] = std::max(std::min(sum, 255), 0);
            }
        }
    }

    static void sobel_y(const cv::Mat& input, cv::Mat& output) {
        // Check GrayScale images     
        CV_Assert(input.channels() == 1 && output.channels() == 1);

        // Define Kernel     
        std::vector<int> kernel({ 1,2,1,0,0,0,-1,-2,-1 });
        int kernel_size = 3;

        unsigned char* data_in = (unsigned char*)(input.data);
        unsigned char* data_out = (unsigned char*)(output.data);
        for (int row = 0; row < input.rows; row++) {
            for (int col = 0; col < input.cols; col += 1) {

                if (row <= kernel_size / 2 || row >= input.rows - kernel_size / 2 ||
                    col <= kernel_size / 2 || col >= input.cols - kernel_size / 2) {
                    data_out[output.step * row + col] = 0;
                    continue;
                }
                int sum = 0;
                int k_ind = 0;
                for (int k_row = -kernel_size / 2; k_row <= kernel_size / 2; ++k_row) {
                    for (int k_col = -kernel_size / 2; k_col <= kernel_size / 2; ++k_col) {
                        sum += kernel[k_ind] * data_in[input.step * (row + k_row) + col + k_col];
                        k_ind++;
                    }
                }
                data_out[output.step * row + col] = std::max(std::min(sum, 255), 0);
            }
        }
    }

    static void sobel(const cv::Mat& input, cv::Mat& output) {
        std::vector<int> kernel_x({ 1,2,1,0,0,0,-1,-2,-1 });
        std::vector<int> kernel_y({ 1,0,-1,2,0,-2,1,0,-1 });
        int kernel_size = 3;


        unsigned char* data_in = (unsigned char*)(input.data);
        unsigned char* data_out = (unsigned char*)(output.data);

        for (int row = 0; row < input.rows; ++row) {
            for (int col = 0; col < input.cols; col += 1) {

                if (row <= kernel_size / 2 || row >= input.rows - kernel_size / 2 ||
                    col <= kernel_size / 2 || col >= input.cols - kernel_size / 2) {
                    data_out[output.step * row + col] = 0;
                    continue;
                }

                int sum_x = 0, sum_y = 0;
                int k_ind = 0;
                for (int k_row = -kernel_size / 2; k_row <= kernel_size / 2; ++k_row) {
                    for (int k_col = -kernel_size / 2; k_col <= kernel_size / 2; ++k_col) {
                        sum_x += kernel_x[k_ind] * data_in[input.step * (row + k_row) + col + k_col];
                        sum_y += kernel_y[k_ind] * data_in[input.step * (row + k_row) + col + k_col];
                        k_ind++;
                    }
                }
                int G = unsigned(std::sqrt(sum_x * sum_x + sum_y * sum_y));
                data_out[output.step * row + col] = std::min(G, 255);
            }
        }
    }
};