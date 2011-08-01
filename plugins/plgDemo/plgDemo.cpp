// This is the main DLL file.

#include "stdafx.h"
#include "plgDemo.h"
#include <stdio.h>
#include <Ogre.h>
using namespace plgDemo;
void ogBaseClass::AttachParams(OgreGUI::ogPluginParams^ params){
	printf("[Attaching Parameters to Demo plugin]\n");
	try {
		_mainMenu = params->mainMenu;
		_mainPanel = params->mainPanel;
	}catch(System::Exception ^ex){
		printf("Error in plugin Demo: %s\n",ex->Message);
	}
}

void ogBaseClass::BuildControls(){
	printf("[Building Controls to Demo plugin.]\n");
	System::Windows::Forms::ToolStripMenuItem ^openItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	openItem->Name = L"Open(Demo)";
	openItem->Size = System::Drawing::Size(111, 22);
	openItem->Text = "Open(Demo)";
	openItem->Click += gcnew System::EventHandler(this, &ogBaseClass::openToolStripMenuItem_Click);
	
	for(int i = 0; i < _mainMenu->Items->Count; i++){
		if(_mainMenu->Items[i]->Text->ToLower() == "file"){
			if(i>0)((System::Windows::Forms::ToolStripMenuItem^)_mainMenu->Items[i-1])->DropDownItems->Insert(0,openItem);
			else ((System::Windows::Forms::ToolStripMenuItem^)_mainMenu->Items[0])->DropDownItems->Insert(0,openItem);
		}
	}
	printf("[/Building Controls]\n");
}
System::Void ogBaseClass::openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Ogre::SceneManager *sceneMgr = NULL;
	Ogre::Camera *camera = NULL;
	Ogre::Entity *ent = NULL;
	Ogre::SceneNode *node = NULL;

	try {
		sceneMgr = Ogre::Root::getSingleton ().getSceneManager ("ExampleSMInstance");
		camera = sceneMgr->getCamera("PlayerCam");
	} catch (Ogre::Exception &ex) {
		printf("Error in Open(Demo): %s\n",ex.getFullDescription().c_str());
		return;
	}
	try {
		ent = sceneMgr->getEntity("OgreHead");
		node = sceneMgr->getSceneNode("OgreHeadNode");
		
		node->removeAllChildren();
		sceneMgr->destroyEntity(ent);
	} catch (...) {
		///do nothing
	}

	try {
		ent = sceneMgr->createEntity("Robot","robot.mesh");
		node->attachObject(ent);
	} catch (Ogre::Exception &ex) {
		printf("Error in Open(Demo): %s\n",ex.getFullDescription().c_str());

	}
}