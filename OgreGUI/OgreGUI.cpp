// OgreGUI.cpp : main project file.

#include "stdafx.h"
#include "OgreGui.h"
#include "ogUtilities.h"
using namespace OgreGUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Initialize Console
	OgreGUI::ogUtilitiesUM::createConsole();

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
