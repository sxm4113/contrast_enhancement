#include "Local_contrast_enhancement.h" 

using namespace cv;

LocalContrastEnhancement::LocalContrastEnhancement(Mat &img)
    : original_image{img},
      enhanced_image{Mat(img.rows, img.cols, CV_8U)},
      HEIGHT{img.rows},
      WIDTH{img.cols} {}

LocalContrastEnhancement::LocalContrastEnhancement(std::string filename)
{
    original_image = imread(filename, IMREAD_GRAYSCALE);
    enhanced_image = Mat(original_image.rows, original_image.cols, CV_8U);
    HEIGHT = original_image.rows;
    WIDTH = original_image.cols;
}

void LocalContrastEnhancement::run_algorithm() {
    Mat outImg;
    resize(original_image, outImg, Size(), 0.5, 0.5);
     
    Mat down_conv_filtered = convolution_image(outImg); 
    Mat resize_up;
    resize(down_conv_filtered, resize_up, Size(WIDTH, HEIGHT), INTER_LINEAR); 
    
    Mat up_conv_filtered = convolution_image(resize_up); 
    Mat output = rolp(original_image, up_conv_filtered); 
    adjustment(original_image, output); 
};

Mat LocalContrastEnhancement::get_enhanced_image() { return enhanced_image; }

/*calculate convolution*/
// input : 5 by 5 image, filter
// output : pixel value of the center of 5 by 5 image.
Mat LocalContrastEnhancement::convolution_image(const Mat &image) 
{
    Mat output ; 
    float kernel[25] = {1.0 / 256, 4.0 / 256, 6.0 / 256, 4.0 / 256, 1.0 / 256,
        4.0 / 256, 16.0 / 256, 24.0 / 256, 16.0 / 256, 4.0 / 256,
        6.0 / 256, 24.0 / 256, 36.0 / 256, 24.0 / 256, 6.0 / 256,
        4.0 / 256, 16.0 / 256, 24.0 / 256, 16.0 / 256, 4.0 / 256,
        1.0 / 256, 4.0 / 256, 6.0 / 256, 4.0 / 256, 1.0 / 256};
    Mat kernel_mat = Mat(5, 5, CV_32F, kernel); 
    cv::filter2D(image,output,-1, kernel_mat, Point(-1, -1),0, BORDER_DEFAULT); 
  return output;
}

/*find ROLP (ratio of lowpass)*/
Mat LocalContrastEnhancement::rolp(const Mat &original_image,
                                   const Mat &expanded) 
{
  Mat output(original_image.rows, original_image.cols, CV_32FC1);
  Mat float_expanded;
  Mat float_original_image;

  expanded.convertTo(float_expanded, CV_32FC1);
  original_image.convertTo(float_original_image, CV_32FC1);

  for (int j = 0; j < original_image.rows; j++) {
    for (int i = 0; i < original_image.cols; i++) {
      output.at<float>(j, i) = float_original_image.at<float>(j, i) /
                               (4.0 * float_expanded.at<float>(j, i));
    }
  }
  return output;
}

void LocalContrastEnhancement::adjustment(Mat &original_image,
                                          const Mat &rolp_result) {
  int final_value{0};
  Mat CEG256(original_image.rows, original_image.cols, CV_8U);
  uchar CE_EXP;
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      if (i > 1 && i < WIDTH - 1 && j > 1 && j < HEIGHT) {
        if (rolp_result.at<float>(j, i) < 1) {
          uchar minimum = original_image.at<uchar>(j - 1, i - 1);
          for (int original_j = j - 1; original_j < j + 1; original_j++) {
            for (int original_i = i - 1; original_i < i + 1; original_i++) {
              if (original_image.at<uchar>(original_j, original_i) < minimum) {
                minimum = original_image.at<uchar>(original_j, original_i);
              }
            }
          }
          CE_EXP = minimum;
        } else if (rolp_result.at<float>(j, i) > 1) {
          uchar maximum = original_image.at<uchar>(j - 1, i - 1);

          for (int original_j = j - 1; original_j < j + 1; original_j++) {
            for (int original_i = i - 1; original_i < i + 1; original_i++) {
              if (original_image.at<uchar>(original_j, original_i) > maximum) {
                maximum = original_image.at<uchar>(original_j, original_i);
              }
            }
          }
          CE_EXP = maximum;
        } else
          CE_EXP = original_image.at<uchar>(j, i);
      } else
        CE_EXP = original_image.at<uchar>(j, i);

      final_value = trunc(rolp_result.at<float>(j, i) * 3.0 * CE_EXP);

      if (final_value > 255) final_value = 255;

      CEG256.at<uchar>(j, i) = final_value;
    }
  }
  enhanced_image = CEG256;
}
