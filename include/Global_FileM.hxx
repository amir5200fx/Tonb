#pragma once
#define TNB_CHECK_LOADED							\
if (NOT loadTag)									\
{													\
	FatalErrorIn(FunctionSIG)						\
		<< "no file has been load." << endl			\
		<< abort(FatalError);						\
}

#define TNB_CHECK_LOADED_FILE(_file)			\
if (NOT _file)									\
{												\
	FatalErrorIn(FunctionSIG)					\
		<< "the loaded file is null!" << endl	\
		<< abort(FatalError);					\
}

#define TNB_DEFINE_VERBOSE_OBJ static unsigned short verbose = 0
#define TNB_DEFINE_LOADTAG_OBJ static bool loadTag = false
#define TNB_DEFINE_EXETAG_OBJ static bool exeTag = false
#define TNB_DEFINE_FILENAME_OBJ static std::string myFileName
#define TNB_DEFINE_MODEL_DIRECTORY_OBJ (_Model_Directory_Name) static const auto model_directory = _Model_Directory_Name

#define TNB_DEFINE_GLOBAL_PATH static auto global_path = boost::filesystem::current_path()
#define TNB_SETTO_GLOBAL_PATH boost::filesystem::current_path(global_path)

#define TNB_SET_VERBOSE_FUN										\
void setVerbose(unsigned int i)									\
{																\
	Info << endl;												\
	Info << " - the verbosity level is set to: " << i << endl;	\
	verbose = i;												\
}

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

#define TNB_CHECK_EXE_TAG								\
if (NOT exeTag)											\
{														\
	FatalErrorIn(FunctionSIG)							\
		<< "the application is not performed!" << endl	\
		<< abort(FatalError);							\
}

#define TNB_EXECUTE_TAG  exeTag = true;
#define TNB_PERFORMED_TAG											\
TNB_EXECUTE_TAG;													\
if (verbose)														\
{																	\
	Info << endl													\
		<< " - the application is successfully performed!" << endl;	\
}

#define TNB_SAVE_FILE(_Saving_File)																					\
void saveTo(const std::string & name)																				\
{																													\
	if (NOT exeTag)																									\
	{																												\
		FatalErrorIn(FunctionSIG)																					\
			<< "the application is not performed!" << endl															\
			<< abort(FatalError);																					\
	}																												\
																													\
	file::CheckExtension(name);																						\
	file::SaveTo(_Saving_File, name + std::remove_reference<decltype(*_Saving_File)>::type::extension, verbose);	\
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

#define TNB_SAVE_MULTI_FILES_FUN(_SubDirect, _Extension, _Files)	\
void saveTo(const std::string & name)								\
{																	\
	if (NOT exeTag)													\
	{																\
		FatalErrorIn(FunctionSIG)									\
			<< "the application has not been performed!" << endl	\
			<< abort(FatalError);									\
	}																\
																	\
	auto current = boost::filesystem::current_path().string();		\
	std::string address = current + "\\" + _SubDirect;				\
	boost::filesystem::path dir(address);							\
	if (NOT boost::filesystem::is_directory(dir))					\
	{																\
		boost::filesystem::create_directory(dir);					\
	}																\
	else															\
	{																\
		file::RemoveDirectory(dir);									\
		boost::filesystem::create_directory(dir);					\
	}																\
																	\
	boost::filesystem::current_path(dir);							\
																	\
	size_t i = 0;													\
	for (const auto& x : _Files)									\
	{																\
		std::string icurrent = address + "\\" + std::to_string(i);	\
																	\
		boost::filesystem::path idir(std::to_string(i));			\
		boost::filesystem::create_directory(idir);					\
																	\
		boost::filesystem::current_path(icurrent);					\
																	\
		file::SaveTo(x, name + _Extension, verbose);				\
																	\
		boost::filesystem::current_path(dir);						\
																	\
		++i;														\
	}																\
																	\
	boost::filesystem::current_path(current);						\
}

#define TNB_SAVE_MULTI_FILES(_SubDirect, _Extension, _Files)	\
if (NOT exeTag)													\
{																\
	FatalErrorIn(FunctionSIG)									\
		<< "the application has not been performed!" << endl	\
		<< abort(FatalError);									\
}																\
																\
auto current = boost::filesystem::current_path().string();		\
std::string address = current + "\\" + _SubDirect;				\
boost::filesystem::path dir(address);							\
if (NOT boost::filesystem::is_directory(dir))					\
{																\
	boost::filesystem::create_directory(dir);					\
}																\
else															\
{																\
	file::RemoveDirectory(dir);									\
	boost::filesystem::create_directory(dir);					\
}																\
																\
boost::filesystem::current_path(dir);							\
																\
size_t i = 0;													\
for (const auto& x : _Files)									\
{																\
	std::string icurrent = address + "\\" + std::to_string(i);	\
																\
	boost::filesystem::path idir(std::to_string(i));			\
	boost::filesystem::create_directory(idir);					\
																\
	boost::filesystem::current_path(icurrent);					\
																\
	file::SaveTo(x, name + _Extension, verbose);				\
																\
	boost::filesystem::current_path(dir);						\
																\
	++i;														\
}																\
																\
boost::filesystem::current_path(current);	