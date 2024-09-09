#include "process_manager.h" 

void process_manager::runapp()
{
	std::string filename = "../images/original_image.jpg";
	lce = new LocalContrastEnhancement{ filename };
	lce->run_algorithm();

	mor = new MultiscaleMorphology{ filename };
	mor->run_algorithm();

	MainFrame* mainFrame = new MainFrame("Image App", lce->get_enhanced_image(), mor->get_result());
	mainFrame->SetClientSize(960,768);
	mainFrame->Center();
	mainFrame->Show();
}
