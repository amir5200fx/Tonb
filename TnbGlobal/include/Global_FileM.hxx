#pragma once
#define TNB_STANDARD_LOAD_SAVE_OBJECTS(_Model_Directory_Name)	\
	static unsigned short verbose = 0;							\
	static bool loadTag = false;								\
	static bool exeTag = false;									\
	static std::string myFileName;								\
	static const auto model_directory = _Model_Directory_Name;	\
																\
void setVerbose(unsigned int i)									\
{																\
	Info << endl;												\
	Info << " - the verbosity level is set to: " << i << endl;	\
	verbose = i;												\
}


#define TNB_CHECK_LOAD_TAG										\
if (NOT loadTag)												\
{																\
	FatalErrorIn(FunctionSIG)									\
		<< "no file has been loaded!" << endl					\
		<< abort(FatalError);									\
}

#define TNB_EXECUTE_TAG  exeTag = true;
#define TNB_PERFORMED_TAG											\
TNB_EXECUTE_TAG;													\
if (verbose)														\
{																	\
	Info << endl													\
		<< " - the application is successfully performed!" << endl;	\
}

#define TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(_Loading_File, _Model_Directory, _Saving_File)							\
void loadModel(const std::string& name)																					\
{																														\
	file::CheckExtension(name);																							\
	_Loading_File =																										\
		file::LoadFile<std::shared_ptr<std::remove_reference<decltype(*_Loading_File)>::type>>							\
		(name + std::remove_reference<decltype(*_Loading_File)>::type::extension, verbose);								\
	if (NOT _Loading_File)																								\
	{																													\
		FatalErrorIn(FunctionSIG)																						\
			<< "no object has been loaded." << endl																		\
			<< abort(FatalError);																						\
	}																													\
	loadTag = true;																										\
	myFileName = name;																									\
}																														\
																														\
void loadModel()																										\
{																														\
	_Loading_File = file::LoadSingleFile<std::shared_ptr<std::remove_reference<decltype(*_Loading_File)>::type>>		\
		(																												\
			_Model_Directory,																							\
			std::remove_reference<decltype(*_Loading_File)>::type::extension,											\
			verbose,																									\
			myFileName																									\
			);																											\
	loadTag = true;																										\
	if (NOT _Loading_File)																								\
	{																													\
		FatalErrorIn(FunctionSIG)																						\
			<< "no object has been loaded." << endl																		\
			<< abort(FatalError);																						\
	}																													\
}																														\
																														\
void loadFile()																											\
{																														\
	if (file::IsDirectory(_Model_Directory))																			\
	{																													\
		loadModel();																									\
	}																													\
	else																												\
	{																													\
		auto name =																										\
			file::GetSingleFile																							\
			(boost::filesystem::current_path(),																			\
				std::remove_reference<decltype(*_Loading_File)>::type::extension										\
			).string();																									\
		loadModel(name);																								\
	}																													\
}																														\
																														\
void saveTo(const std::string& name)																					\
{																														\
	if (NOT exeTag)																										\
	{																													\
		FatalErrorIn(FunctionSIG)																						\
			<< "the application is not performed!" << endl																\
			<< abort(FatalError);																						\
	}																													\
																														\
	file::CheckExtension(name);																							\
	file::SaveTo(_Saving_File, name + std::remove_reference<decltype(*_Saving_File)>::type::extension, verbose);		\
}																														\
																														\
void saveTo()																											\
{																														\
	saveTo(myFileName);																									\
}