#include "stdafx.h"
#include "ogOgreApp.h"
#include "ogFrameListener.h"

using namespace OgreGUI;

ogOgreApp::ogOgreApp(int handle): 
		mGUIRenderer(0),
        mGUISystem(0),
		mlHandle(handle)
{

}

ogOgreApp::~ogOgreApp()
{
	if(mGUISystem)
	{
		delete mGUISystem;
		mGUISystem = 0;
	}
	if(mGUIRenderer)
	{
		delete mGUIRenderer;
		mGUIRenderer = 0;
	}
}
void ogOgreApp::createCamera(void)
{
	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Vector3(0,0,-300));
	mCamera->setNearClipDistance(1);
	mCamera->setFOVy(Ogre::Radian(Ogre::Degree(45)));
	mCamera->setAutoAspectRatio(true);
}


bool ogOgreApp::configure(void)
{
 /*   // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
	if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true);
		// Let's add a nice window icon
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//		HWND hwnd;
//		mWindow->getCustomAttribute("WINDOW", (void*)&hwnd);
//		LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
//		SetClassLong( hwnd, GCL_HICON, iconID );
#endif
        return true;
    }
    else
    {
        return false;
    }*/
	if(!mRoot->restoreConfig()){
		if(mRoot->showConfigDialog()){
			NameValuePairList miscParams;
			miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)mlHandle);
			mRoot->initialise(false);
			mWindow = mRoot->createRenderWindow("test",640,480,false,&miscParams);
		}
	} else{
		NameValuePairList miscParams;
		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)mlHandle);
		mRoot->initialise(false);
		mWindow = mRoot->createRenderWindow("test",640,480,false,&miscParams);
	}
	return true;
}


// Just override the mandatory create scene method
void ogOgreApp::createScene(void)
{
	// Set ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.25, 0.25, 0.25));
	//mSceneMgr->setSkyBox(true,"Examples/StormySkyBox");

	// Create a light
	createLight("mainlight1",Vector3(20,80,-80),Vector3(0,0,0));
	createLight("mainlight2",Vector3(-20,80,80),Vector3(0,0,0));

	Ogre::Entity *ent = mSceneMgr->createEntity("OgreHead","ogrehead.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
	node->attachObject(ent);
}
void ogOgreApp::createLight(const Ogre::String name, Ogre::Vector3 pos,Ogre::Vector3 dir){
	Light *l = mSceneMgr->createLight(name + "_light");
	l->setDiffuseColour(1,1,1);
	SceneNode *lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name + "_lightnode");
	lightNode->attachObject(l);
	lightNode->setPosition(pos);

	BillboardSet *flareSet = mSceneMgr->createBillboardSet(name + "_flare");
	flareSet->setMaterialName("Examples/Flare");

	Ogre::SceneNode *flareNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name + "_flarenode" );
	flareNode->attachObject(flareSet);
	flareNode->setPosition(pos.x, pos.y, pos.z);

	Billboard *flare = flareSet->createBillboard(0,0,0);
	flare->setColour(ColourValue(1,1,1));
	flare->setDimensions(10,10);
}
// Create new frame listener
void ogOgreApp::createFrameListener(void)
{
	_framelistener = new ogFrameListener(this,mCamera,mSceneMgr, mWindow);
	mRoot->addFrameListener(_framelistener);
}
void ogOgreApp::setupEventHandlers(void)
{
}

bool ogOgreApp::handleQuit(const CEGUI::EventArgs& e)
{
  return true;
}
void ogOgreApp::update(){
	mRoot->renderOneFrame();
	mWindow->update();
}

// Start the example
void ogOgreApp::go(void)
{
    if (!setup()) return;
	mWindow->update();
}
void ogOgreApp::Resize(int width, int height){
	mWindow->resize(width,height);
	mWindow->windowMovedOrResized();
}
void ogOgreApp::destroyScene(){

}