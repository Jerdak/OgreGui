// plgDemo.h

#pragma once
using namespace System;

namespace plgDemo {

	public ref class ogBaseClass
	{
	public:

		void AttachParams(OgreGUI::ogPluginParams ^params);
		void BuildControls();
	
	private:
		System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Windows::Forms::Panel ^_mainPanel;
		System::Windows::Forms::MenuStrip ^_mainMenu;
	};
}
