#pragma once
#include "MainFrame.h" 
#include "Local_contrast_enhancement.h"
#include "MultiscaleMorphology.h"
#include "App.h"

class process_manager
{
public: 
	LocalContrastEnhancement* lce;
	MultiscaleMorphology* mor;
	void runapp();
};

