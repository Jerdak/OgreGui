#pragma once
#include <Ogre.h>
#include <vector>
#include <string>
namespace OgreGUI {
	ref class ogUtilities
	{
	public:
		ogUtilities(void);
	};

	class ogUtilitiesUM
	{
	public:
		ogUtilitiesUM(void);
		static void createConsole();
		static Ogre::SceneNode *loadObj(Ogre::SceneManager *mgr,Ogre::String fileName,Ogre::String meshName);
		static std::vector<std::string> ogUtilitiesUM::tokenize(const std::string& str,const std::string& delimiters);
	};
};