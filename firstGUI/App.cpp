#include "App.h"
#include "MainFrame.h"
#include "process_manager.h"


wxIMPLEMENT_APP(App);

bool App::OnInit() {
	process_manager pm;
	pm.runapp();
	return true;
}