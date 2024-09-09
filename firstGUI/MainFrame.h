#pragma once
#include <wx/wx.h>
#include "ImagePanel.h"
#include "Local_contrast_enhancement.h"
#include <opencv2/opencv.hpp>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const cv::Mat& image_pyramid, const cv::Mat& image_morphology);
private:
	void CreateControls(const cv::Mat& image_pyramid, const cv::Mat& image_morphology);
	void SetupSizers();
	void BindEventHandlers();

	void OnButton0Clicked(wxCommandEvent& evt);
	void OnButton1Clicked(wxCommandEvent& evt);
	void OnButton2Clicked(wxCommandEvent& evt);

	LocalContrastEnhancement* lce;
	wxImagePanel* drawPanel;
	wxPanel* buttonPanel;
	wxButton* button1;
	wxButton* button2;
	wxButton* original_image_button;
};

