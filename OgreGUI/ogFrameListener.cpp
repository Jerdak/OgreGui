#include "StdAfx.h"
#include "ogFrameListener.h"
#include "ogOgreApp.h"

using namespace OgreGUI;
ogFrameListener::ogFrameListener(ogOgreApp *p, Ogre::Camera *cam, Ogre::SceneManager *scene, Ogre::RenderWindow *window)
{
	_moveSpeed = 75.0f;
	_nmApp = p;
	_window = window;
	_sceneMgr = scene;
	_camera = cam;
	_vTranslate = Ogre::Vector3::ZERO;
}
// Override frameStarted event to process that (don't care about frameEnded)
bool ogFrameListener::frameStarted(const FrameEvent& evt)
{
	moveCamera();

	// Move about 100 units per second
	_moveScale = _moveSpeed * evt.timeSinceLastFrame;
	
	// Take about 10 seconds for full rotation
	//mRotScale = mRotateSpeed * evt.timeSinceLastFrame;

	//mRotX = 0;
	//mRotY = 0;
	_vTranslate = Ogre::Vector3::ZERO;

	return true;
}

bool ogFrameListener::frameEnded(const FrameEvent& evt)
{
	return true;
}
void ogFrameListener::Update(double tm){
//	_moveScale = _moveSpeed * tm;
//	MoveCamera();
}
void ogFrameListener::moveCamera()
{
	// Make all the changes to the camera
	// Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW
	//(e.g. airplane)
//	mCamera->yaw(mRotX);
//	mCamera->pitch(mRotY);
	_camera->moveRelative(_vTranslate);
}

void ogFrameListener::OnKeyEvent(KeyEvent ev, Keys key){
	switch(ev){
		case KEY_PRESS:
			switch (key){
				case KC_W:
					_vTranslate.z -= _moveScale;
					break;
				case KC_S:
					_vTranslate.z += _moveScale;
					break;
				case KC_A:
					_vTranslate.x -= _moveScale;
					break;
				case KC_D:
					_vTranslate.x += _moveScale;
					break;
				case KC_UP:
					_vTranslate.y += _moveScale;
					break;
				case KC_DOWN:
					_vTranslate.y -= _moveScale;
					break;

			};
			break;
		case KEY_RELEASE:
			break;
		default:
			break;
	};
}
void ogFrameListener::OnMouseEvent(MouseEvent ev){
	
	switch(ev){
		case MOUSE_LEFT_BUTTON_DOWN:
			break;
		case MOUSE_LEFT_BUTTON_UP:
			break;
	};
}