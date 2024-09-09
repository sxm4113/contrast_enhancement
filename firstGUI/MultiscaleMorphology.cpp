#include "MultiscaleMorphology.h"

MultiscaleMorphology::MultiscaleMorphology(std::string filename)
{
	input_image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
}

cv::Mat MultiscaleMorphology::black_hat(cv::Mat original_image, int morph_size)
{   
    cv::Mat output;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, 
        cv::Size(morph_size + 1, morph_size + 1) );
	cv::morphologyEx(original_image, output, cv::MORPH_BLACKHAT, element);
    return output;
}

cv::Mat MultiscaleMorphology::top_hat(cv::Mat original_image, int morph_size)
{
	cv::Mat output;
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(morph_size + 1, morph_size + 1) );
	cv::morphologyEx(original_image, output, cv::MORPH_TOPHAT, element );
	return output; 
}

void MultiscaleMorphology::run_algorithm()
{
	cv::Mat tophat3 = top_hat(input_image, 2); 
	cv::Mat tophat5 = top_hat(input_image, 4); 
	cv::Mat tophat7 = top_hat(input_image, 6); 

	cv::Mat blackhat3 = black_hat(input_image, 2); 
	cv::Mat blackhat5 = black_hat(input_image, 4); 
	cv::Mat blackhat7 = black_hat(input_image, 6); 

	cv::Mat sum_blackhat = 0.9 * blackhat3 + 0.5 * blackhat5 + 0.3 * blackhat7  ;
	cv::Mat sum_tophat = 0.9 * tophat3 + 0.5 * tophat5 + 0.3 * tophat7 ;

	morpology_result = sum_blackhat + sum_tophat + input_image; 
}

cv::Mat MultiscaleMorphology::get_result()
{
	return morpology_result;
}
