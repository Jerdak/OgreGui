#pragma once

#include <Ogre.h>
#include <ExampleApplication.h>
namespace OgreGUI {
	class ogOgreApp;
	class ogFrameListener : public FrameListener
	{
	public:
		enum KeyEvent { KEY_PRESS,KEY_RELEASE };
		enum Keys { KC_W,KC_A,KC_S,KC_D,KC_ESC,KC_UP,KC_DOWN };
		enum MouseEvent { MOUSE_LEFT_BUTTON_UP,
						  MOUSE_LEFT_BUTTON_DOWN,
						  MOUSE_RIGHT_BUTTON_UP,
						  MOUSE_RIGHT_BUTTON_DOWN,
						  MOUSE_MOVE };

		ogFrameListener(ogOgreApp *p, Ogre::Camera *cam, Ogre::SceneManager *scene, Ogre::RenderWindow *window);
		
		Ogre::SceneManager *GetSceneMgr(){return _sceneMgr;}
		void moveCamera();
		void OnMouseEvent(MouseEvent ev);
		void OnKeyEvent(KeyEvent ev, Keys key);
		void Update(double tm);

		bool frameStarted(const FrameEvent& evt);
		bool frameEnded(const FrameEvent& evt);
	protected:
		Ogre::Vector3 _vTranslate;

	private:
		double _moveSpeed;
		double _moveScale;
		Ogre::SceneNode *_node;
		ogOgreApp *_nmApp;
		Ogre::Camera *_camera;
		Ogre::SceneManager *_sceneMgr;
		Ogre::RenderWindow *_window;
	};
};