#pragma once

#ifdef _USE_MODULE_LOADER

	namespace OgreGUI {
		ref class ogPlugin {
		public:
			ogPlugin(){}
			~ogPlugin(){}
		
			System::String ^_nameSpace;
			System::String ^_name;
			System::String ^_baseClass;
			System::IO::FileInfo ^_file;
			Object ^_instance;
		protected:

		private:

		};
		
		ref class ogModuleLoader
		{
		public:
			ogModuleLoader(void);
			
			void FindPlugins();
		
			System::Collections::Generic::List<ogPlugin^> ^GetPluginList(){return %_pluginList;}
			void SetPluginFolder(System::String ^s){_sPluginFld = s;}
			void LoadPlugins(System::Windows::Forms::Panel ^ptrPanel,System::Windows::Forms::MenuStrip ^ptrMenu);

		protected:

		private:
			System::String ^_sPluginFld;
			System::Collections::Generic::List<ogPlugin^> _pluginList;
		};
	};
#endif