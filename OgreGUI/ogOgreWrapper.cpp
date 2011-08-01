#include "StdAfx.h"


#include "ogOgreWrapper.h"

#include <Ogre.h>
#include <map>
#include <vector>

using namespace OgreGUI;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace std;

#pragma managed

ogOgreWrapper::ogOgreWrapper(int handle)
{
	pApp = new ogOgreApp(handle);
	pApp->go();

	pFrameListener = pApp->GetFrameListener();
}
ogOgreWrapper::~ogOgreWrapper(){
	pApp->destroyScene();
}
void ogOgreWrapper::Resize(int width, int height){
	pApp->Resize(width,height);
	pApp->update();
}
void ogOgreWrapper::update(double tm) {
	pApp->update();
}
void ogOgreWrapper::LoadMesh(const Ogre::String name){
}

void  ogOgreWrapper::MouseDown(gcroot<System::Windows::Forms::MouseEventArgs^> e){
	if(e->Button == System::Windows::Forms::MouseButtons::Left){
		_evMouse.bMouseLeftDown = true;
		_evMouse._iLastX = e->X;
		_evMouse._iLastY = e->Y;
		//_console->WriteLine("Left Click at " + e->X.ToString() + "," + e->Y.ToString());
	} else if(e->Button == System::Windows::Forms::MouseButtons::Right){
		_evMouse.bMouseRightDown = true;
		_evMouse._iLastX = e->X;
		_evMouse._iLastY = e->Y;
	}
}
void  ogOgreWrapper::MouseUp(gcroot<System::Windows::Forms::MouseEventArgs^> e){
	if(e->Button == System::Windows::Forms::MouseButtons::Left){
		_evMouse.bMouseLeftDown = false;
		//_console->WriteLine("Left Released");
	} else if(e->Button == System::Windows::Forms::MouseButtons::Right){
		_evMouse.bMouseRightDown = false;
		//_console->WriteLine("Right Released");
	} 
}
void  ogOgreWrapper::MouseMove(gcroot<System::Windows::Forms::MouseEventArgs^> e){
	if(_evMouse.bMouseLeftDown){
		int diffX = e->X - _evMouse._iLastX;
		int diffY = e->Y - _evMouse._iLastY;
		_evMouse._iLastX = e->X;
		_evMouse._iLastY = e->Y;

		try {
			Ogre::SceneManager *sceneMgr = Ogre::Root::getSingleton ().getSceneManager ("ExampleSMInstance"); 
			Ogre::SceneNode *node = sceneMgr->getRootSceneNode();//->getSceneNode("OgreHeadNode");
			
			node->yaw(Ogre::Degree(diffX),Ogre::Node::TransformSpace::TS_PARENT);
			node->pitch(Ogre::Degree(diffY),Ogre::Node::TransformSpace::TS_PARENT);
		} catch (...){
			///do nothing
		}
		//Rotate(diffX,diffY,0);
	} else if(_evMouse.bMouseRightDown){
		int diffX = e->X - _evMouse._iLastX;
		int diffY = e->Y - _evMouse._iLastY;
		_evMouse._iLastX = e->X;
		_evMouse._iLastY = e->Y;

		if(diffY < 0)pFrameListener->OnKeyEvent(ogFrameListener::KEY_PRESS,ogFrameListener::KC_DOWN);
		else		 pFrameListener->OnKeyEvent(ogFrameListener::KEY_PRESS,ogFrameListener::KC_UP);
	}
}
void  ogOgreWrapper::MouseWheel(gcroot<System::Windows::Forms::MouseEventArgs^> e){
	if(e->Delta < 0){
		pFrameListener->OnKeyEvent(ogFrameListener::KEY_PRESS,ogFrameListener::KC_S);
	} else {
		pFrameListener->OnKeyEvent(ogFrameListener::KEY_PRESS,ogFrameListener::KC_W);
	}
}
void ogOgreWrapper::KeyDown(gcroot<System::Windows::Forms::KeyEventArgs^> e){
	ogFrameListener::Keys key;
	
	if(e->KeyCode == Keys::W)key = ogFrameListener::KC_W;
	if(e->KeyCode == Keys::S)key = ogFrameListener::KC_S;
	if(e->KeyCode == Keys::A)key = ogFrameListener::KC_A;
	if(e->KeyCode == Keys::D)key = ogFrameListener::KC_D;

	pFrameListener->OnKeyEvent(ogFrameListener::KEY_PRESS,key);
}

void ogOgreWrapper::KeyUp(gcroot<System::Windows::Forms::KeyEventArgs^> e){


}