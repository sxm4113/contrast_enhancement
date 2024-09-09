#pragma once
#include <opencv2/opencv.hpp>

class MultiscaleMorphology
{
private:
	cv::Mat input_image;
	cv::Mat morpology_result;

public:
	MultiscaleMorphology(std::string filename);
	cv::Mat black_hat(cv::Mat original_image, int morph_size);
	cv::Mat top_hat(cv::Mat original_image, int morph_size);
	void run_algorithm();
	cv::Mat get_result();

};

