#pragma once

#ifdef _USE_MODULE_LOADER
	#include "ogModuleLoader.h"
#endif

#include "ogOgreWrapper.h"
#include "ogUtilities.h"
#include <stdio.h>

namespace OgreGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//Find all plugins, make sure to attach debugging console form
			{			
				#ifdef _USE_MODULE_LOADER
					try {
						_moduleLoader = gcnew ogModuleLoader();
						_moduleLoader->SetPluginFolder("./Plugins"); //NOTE:  MUST DO THIS BEFORE OPENING A FILE, otherwise the fileopen dialog will change the root directory.  or just hardcode the destination.  TODO: Use environment variables
						_moduleLoader->FindPlugins();
					} catch (System::Exception ^ex){
						printf("ERROR in OgreGUI::Constructor: %s\n",ex->Message);
					}
					loadPlugins();
				#endif
				pOgre = new ogOgreWrapper(pnlOgre->Handle.ToInt32());
				pOgre->Resize(pnlOgre->Width,pnlOgre->Height);
				
				timer1->Enabled = true;
			}
		}
		#ifdef _USE_MODULE_LOADER
			void loadPlugins(){
				int ct = 0;
				try {
					_moduleLoader->LoadPlugins(this->pnlOgre,this->menuMain);
				
					/*
					this->tsFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					this->openToolStripMenuItem, 
					this->quitToolStripMenuItem});
					*/
					for each(ogPlugin ^plug in _moduleLoader->GetPluginList()){
						System::Windows::Forms::ToolStripMenuItem^ tmp = gcnew System::Windows::Forms::ToolStripMenuItem();
						tmp->Name = L"pluginMenuItem_" + plug->_name;
						tmp->Size = System::Drawing::Size(152, 22);
						tmp->Text = plug->_name;
						_pluginMenuItems.Add(tmp);
						this->tsPlugin->DropDownItems->Add(tmp);
					}
					if(_pluginMenuItems.Count <= 0) {
						System::Windows::Forms::ToolStripMenuItem^ tmp = gcnew System::Windows::Forms::ToolStripMenuItem();
						tmp->Name = L"pluginMenuItem_NONE";
						tmp->Size = System::Drawing::Size(152, 22);
						tmp->Text = L"No Plugins Found";
						_pluginMenuItems.Add(tmp);
						this->tsPlugin->DropDownItems->Add(tmp);
					}
				} catch (System::Exception ^ex){
					printf("ERROR in OgreGUI::loadPlugins: %s\n",ex->Message);
				}
			}
		#endif
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
		///Ogre wrapper
	private: ogOgreWrapper *pOgre;	

	#ifdef _USE_MODULE_LOADER
		private: ogModuleLoader ^_moduleLoader;
	#endif

	private: System::Windows::Forms::MenuStrip^  menuMain;

	protected: 
	private: System::Collections::Generic::List<System::Windows::Forms::ToolStripMenuItem^> _pluginMenuItems;
	private: System::Windows::Forms::ToolStripMenuItem^  tsFile;

	private: System::Windows::Forms::ToolStripMenuItem^  quitToolStripMenuItem;
	private: System::Windows::Forms::Panel^  pnlOgre;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
	private: System::Windows::Forms::ToolStripMenuItem^  tsPlugin;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
			this->tsFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->quitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsPlugin = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pnlOgre = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuMain->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuMain
			// 
			this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tsFile, this->tsPlugin});
			this->menuMain->Location = System::Drawing::Point(0, 0);
			this->menuMain->Name = L"menuMain";
			this->menuMain->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuMain->Size = System::Drawing::Size(856, 24);
			this->menuMain->TabIndex = 0;
			this->menuMain->Text = L"menuStrip1";
			// 
			// tsFile
			// 
			this->tsFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->openToolStripMenuItem, 
				this->quitToolStripMenuItem});
			this->tsFile->Name = L"tsFile";
			this->tsFile->Size = System::Drawing::Size(39, 20);
			this->tsFile->Text = L"File";
			// 
			// quitToolStripMenuItem
			// 
			this->quitToolStripMenuItem->Name = L"quitToolStripMenuItem";
			this->quitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->quitToolStripMenuItem->Text = L"Quit";
			this->quitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::quitToolStripMenuItem_Click);
			// 
			// tsPlugin
			// 
			this->tsPlugin->Name = L"tsPlugin";
			this->tsPlugin->Size = System::Drawing::Size(61, 20);
			this->tsPlugin->Text = L"Plugins";
			// 
			// pnlOgre
			// 
			this->pnlOgre->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pnlOgre->Location = System::Drawing::Point(0, 64);
			this->pnlOgre->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pnlOgre->Name = L"pnlOgre";
			this->pnlOgre->Size = System::Drawing::Size(855, 582);
			this->pnlOgre->TabIndex = 1;
			this->pnlOgre->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pnlOgre_MouseMove);
			this->pnlOgre->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pnlOgre_MouseClick);
			this->pnlOgre->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pnlOgre_MouseDown);
			this->pnlOgre->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pnlOgre_MouseUp);
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripLabel1});
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(856, 25);
			this->toolStrip1->TabIndex = 2;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(28, 22);
			this->toolStripLabel1->Text = L"Foo";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(856, 646);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->pnlOgre);
			this->Controls->Add(this->menuMain);
			this->MainMenuStrip = this->menuMain;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Form1";
			this->Text = L"OgreGui";
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pnlOgre_MouseWheel);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->menuMain->ResumeLayout(false);
			this->menuMain->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void quitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		pOgre->update( timer1->Interval);
	}
	private: System::Void pnlOgre_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	}
	private: System::Void pnlOgre_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		pOgre->MouseMove(e);	
	}
	private: System::Void pnlOgre_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		pOgre->MouseDown(e);
	}
	private: System::Void pnlOgre_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		pOgre->MouseUp(e);
	}
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		pOgre->KeyDown(e);
	}
	private: System::Void pnlOgre_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		pOgre->MouseWheel(e);
	}
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 OgreGUI::ogUtilitiesUM::loadObj(Ogre::Root::getSingleton ().getSceneManager ("ExampleSMInstance"),"test.obj","Test");
		 }
};
}

