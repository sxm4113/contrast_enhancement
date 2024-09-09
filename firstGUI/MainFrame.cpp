#include "MainFrame.h"  
#include <wx/wx.h>   

MainFrame::MainFrame(const wxString& title, const cv::Mat& image_pyramid, const cv::Mat& image_morphology)
	:wxFrame(nullptr,wxID_ANY, title){
	
	wxInitAllImageHandlers();
	CreateControls(image_pyramid, image_morphology);
	SetupSizers();
	BindEventHandlers();

	wxStatusBar* statusBar = CreateStatusBar();
	statusBar->SetDoubleBuffered(true);
}

void MainFrame::CreateControls(const cv::Mat& image_pyramid, const cv::Mat& image_morphology)
{
	drawPanel = new wxImagePanel(this, wxT("../images/original_image.jpg"), image_pyramid, image_morphology, wxBITMAP_TYPE_JPEG);

	buttonPanel = new wxPanel(this, wxID_ANY);

	original_image_button = new wxButton(buttonPanel, wxID_ANY, "Original Image", wxDefaultPosition, wxSize(100, 50));
	button1 = new wxButton(buttonPanel, wxID_ANY, "Image Pyramid", wxDefaultPosition, wxSize(100, 50));
	button2 = new wxButton(buttonPanel, wxID_ANY, "Image Multiscale Morphology" , wxDefaultPosition, wxSize(100, 50));
}

void MainFrame::SetupSizers()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(drawPanel, 1, wxEXPAND);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);

	buttonSizer->Add(original_image_button, wxSizerFlags().Border(wxALL, 10));
	buttonSizer->Add(button1, wxSizerFlags().Border(wxALL, 10));
	buttonSizer->Add(button2, wxSizerFlags().Border(wxALL, 10));

	buttonPanel->SetSizer(buttonSizer);

	mainSizer->Add(buttonPanel, wxSizerFlags().Border(wxLEFT, 10));

	wxGridSizer* outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 25).Expand());

	this->SetSizerAndFit(outerSizer);
}

void MainFrame::BindEventHandlers()
{
	button1->Bind(wxEVT_BUTTON, &MainFrame::OnButton1Clicked, this);
	button2->Bind(wxEVT_BUTTON, &MainFrame::OnButton2Clicked, this);
	original_image_button->Bind(wxEVT_BUTTON, &MainFrame::OnButton0Clicked, this);
}

void MainFrame::OnButton0Clicked(wxCommandEvent& evt)
{
	wxLogStatus("Original Image");
	drawPanel->button0();
}

void MainFrame::OnButton1Clicked(wxCommandEvent& evt)
{
	wxLogStatus("Image Pyramid");
	drawPanel->button1(); 
}

void MainFrame::OnButton2Clicked(wxCommandEvent& evt)
{
	wxLogStatus("button2 clicked");
	drawPanel->button2();
}
 