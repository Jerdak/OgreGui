#include "StdAfx.h"

#ifdef _USE_MODULE_LOADER
	#include "ogModuleLoader.h"

	#include <Ogre.h>

	using namespace OgreGUI;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;


	ogModuleLoader::ogModuleLoader(void)
	{
		_sPluginFld = gcnew System::String(".");
		}

		void ogModuleLoader::FindPlugins(){
		System::IO::DirectoryInfo ^dir = gcnew System::IO::DirectoryInfo(_sPluginFld);
		printf("[Plugin Finder]");

		int size = 0;
		for each(System::IO::FileInfo ^file in dir->GetFiles()){
			//File is of type DLL
			if(file->Extension->Contains(".dll")){
				printf("Found plugin candidate: %s\n",file->Name);
				size++;

				try {
					Assembly ^a = Assembly::LoadFile(file->FullName);		//Not sure if we need to do this, might be redundant since we load the files in the call method function
					AssemblyName ^an = gcnew AssemblyName(a->FullName);	
						
					//Search each dll for a specific class, in this case ncgBaseClass
					for each(Type ^t in a->GetExportedTypes()){
						printf("       - Type: %s ",t->Name);
						if(t->Name == "ogBaseClass"){
							ogPlugin ^tmp = gcnew ogPlugin();
							tmp->_name = gcnew String(an->Name);
							tmp->_nameSpace = gcnew String(t->Namespace);
							tmp->_baseClass = gcnew String("ogBaseClass");
							tmp->_file = file;
							
							printf("is a plugin\n");
							_pluginList.Add(tmp);
							break;
						} else {
							printf("is NOT a plugin.\n");
						}
					}
					
					//_console->WriteLine("   - Found the following modules:");
					//for each(Module ^m in a->GetModules()){
					//	_console->WriteLine("     - Module: " + m->Name);
					//}
				} catch(...){}
			} else {
				//_console->WriteLine(" is not a dll.");
			}
		}
	}
	//TODO:  Delete this test function
	void ogModuleLoader::LoadPlugins(System::Windows::Forms::Panel ^ptrPanel,System::Windows::Forms::MenuStrip ^ptrMenu){
		printf("[ogModuleLoader::LoadPlugins]\n");

		if(GetPluginList()->Count <= 0) {
			printf("No plugins found for loading, returning.\n");
			return;
		}

		printf("  - Trying to find scene manager\n");
		//Get main scene manager
		Ogre::SceneManager *sceneMgr = NULL;
		/*try {
			sceneMgr = Ogre::Root::getSingleton ().getSceneManager ("ExampleSMInstance"); 
			printf("  - Scene manager found.\n");
		} catch (...){
			printf("  - Scene manager NOT found\n");
		}*/

		//_console->WriteLine("");
		//_console->WriteLine("[Plugin Loading]");
		//_console->WriteLine("  - Size: " + GetPluginList()->Count.ToString());

		//Loop through all plugins and instantiate their base class.
		try {
			printf("  - Parsing plugin list\n");
			for each(ogPlugin^ p in GetPluginList()){
				printf("  - Loading DLL: %s\n",p->_file->Name);

				Assembly ^a = Assembly::LoadFile(p->_file->FullName);					//Load assembly(dll)
				String ^dllclass = gcnew String(p->_nameSpace + "." + p->_baseClass);	//
				printf("  - Dll class: %s\n",dllclass);
				Type ^t = a->GetType(dllclass);											//Get assembly type
				if(t == nullptr){
					printf("  - Error, couldn't get type of dll class.\n");
				}
				printf("    - Trying to run: %s\n",dllclass);
				
				MethodInfo ^mi = t->GetMethod("AttachParams");							//Find the attachparams method
				if(mi == nullptr){
					printf("  - Error, couldn't get 'AttachParams' method.\n");
				}
				for each(System::Reflection::MethodInfo ^nfo in t->GetMethods()){
					printf("Method: %s\n",nfo->Name);
				}
				printf("  - Full Type: %s\n",t->FullName);
				printf("  - Assembly: %s\n",t->Assembly->FullName);
				
				p->_instance = Activator::CreateInstance(t);							//Create an instance of our assembly type and store it in the plugin list
				
				if(p == nullptr){
					printf("  - Error, couldn't create activator instance.\n");
				}
				printf("    - Invoking method 'AttachParams'...");
				//Assign plugin parameters to .dll
				{
					printf("a.");
					ogPluginParams params;
					printf("b.");
					params.mainPanel = ptrPanel;
					printf("c.");
					params.mainMenu = ptrMenu;
					printf("d.");
					array<ogPluginParams ^> ^ar = gcnew array<ogPluginParams^>(1);
					printf("f.");
					ar[0] = %params;
					printf("g.");
					mi->Invoke(p->_instance,ar);
					printf("h.");
				}
				printf("Complete, parameters passed to .dll\n");

				
				{
					printf("    - Invoking method 'BuildControls'...");
					MethodInfo ^mit = t->GetMethod("BuildControls");
					mit->Invoke(p->_instance,nullptr);
					printf("Complete, parameters passed to .dll\n");
				}
			}
		}catch (System::Exception ^ex){
			printf("[ogModuleLoader::LoadPlugins] ERROR: %s\n",ex->Message);
		}
	}
#endif