#pragma once
#ifndef __ogOgreApp_h_
#define __ogOgreApp_h_


#include <ExampleApplication.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//#include "../res/resource.h"
#endif
#include <CEGUI/CEGUI.h>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OgreCEGUIRenderer.h>

namespace OgreGUI {
	class ogFrameListener;
	class ogOgreApp : public ExampleApplication
	{
	private:
		CEGUI::OgreCEGUIRenderer* mGUIRenderer;
		CEGUI::System* mGUISystem;
	public:
		ogOgreApp(int Handle);
		~ogOgreApp();

		void destroyScene();
		void Resize(int width, int height);
		
		ogFrameListener *GetFrameListener(){return _framelistener;}
		void go();
		void update();


	protected:

		virtual void createCamera(void);

		virtual bool configure(void);

		// Just override the mandatory create scene method
		virtual void createScene(void);
		virtual void createLight(const Ogre::String name, Ogre::Vector3 pos,Ogre::Vector3 dir);
		
		void MoveCamera();
		
		// Create new frame listener
		void createFrameListener(void);
		void setupEventHandlers(void);

		bool handleQuit(const CEGUI::EventArgs& e);

		Ogre::Camera *GetCamera(){return mCamera;}
		Ogre::SceneManager *GetSceneManager(){return mSceneMgr;}
		Ogre::RenderWindow *GetWindow(){return mWindow;}
		
		ogFrameListener *_framelistener;
		int mlHandle;
	};
};
#endif