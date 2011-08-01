#pragma once
#include <vcclr.h>

#include "ogOgreApp.h"
#include "ogFrameListener.h"

enum INTERACTION_MODE {POINT_PICK,TRANSFORM,PAN,INFORMATION};

namespace OgreGUI {
	class ogOgreMouseEvent {
	public:
		ogOgreMouseEvent(){
			bMouseLeftDown = bMouseRightDown = false;
			_iLastX = _iLastY = 0;
		};
		~ogOgreMouseEvent(){
		};

		bool bMouseLeftDown;
		bool bMouseRightDown;
		int _iLastX, _iLastY;
	};

	class ogOgreWrapper
	{
	public:
		ogOgreWrapper(int handle);
		~ogOgreWrapper();

		ogFrameListener* GetFrameListener(){return pFrameListener;}
		
		void Resize(int width, int height);
		void LoadMesh(const Ogre::String name);

		void Rotate(int x, int y, int z);

		void KeyDown(gcroot<System::Windows::Forms::KeyEventArgs^> e);
		void KeyUp(gcroot<System::Windows::Forms::KeyEventArgs^> e);

		void MouseDown(gcroot<System::Windows::Forms::MouseEventArgs^> e);
		void MouseUp(gcroot<System::Windows::Forms::MouseEventArgs^> e);
		void MouseMove(gcroot<System::Windows::Forms::MouseEventArgs^> e);
		void MouseWheel(gcroot<System::Windows::Forms::MouseEventArgs^> e);

		void update(double tm);

	private:
		ogOgreApp *pApp;
		ogFrameListener *pFrameListener;
		ogOgreMouseEvent _evMouse;
	};
};